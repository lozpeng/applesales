#include "stdafx.h"
#include "FuzzyKmeanClass.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"

namespace ImageProcess
{

#define SIZE_CHAR 1
#define SIZE_SHORT 2
#define SIZE_INTEGER 4

class  CSample
{
protected:
	// the sample dimension
	long m_lSize;

	// the sample data
	float *m_pData;

public:
	CSample() { m_lSize = 0; m_pData = NULL; };
	virtual ~CSample() { Release(); };

	void Create( long lSize );
	void Release();
	void Set( long lIndex, float fData ) { m_pData[ lIndex ] = fData; }
	float Distance( CSample &cOther );
	long GetSize() { return m_lSize; }
	float Get( long lIndex ) { return m_pData[ lIndex ]; }
};

// the maximum class count is 255
static CSample *FuzzyKmean(
	CSample *pSampleSet, 
	long lSampleCount, 
	long lCenterCount,
	long lMaxIterCount,
	float fMovementThreshold,
	char *pSeedFile,
	long data_length
	);

// read sample seed from the seed file.
static void ReadSeed(
	char *pName, 
	CSample *pSeed, 
	long lSeedCount,
	long data_length
	);

static long GetStringToken(char *source,
	char *destination,
	long start,
	char ch);

bool FuzzyKmeanClass(const char *pszInputFileName, const char *pszOutputFileName, double dblResampleRatio,
					 long lCenterCount, long lMaxIterCount, float fMovementThreshold,SYSTEM::IProgress *pProgress)
{

	using namespace Geodatabase;

	//建立进度条
	if(pProgress)
	{
		pProgress->Create("处理中",SYSTEM::IProgress::Percent,100);
		pProgress->UpdateProgress("",0.01);

	}

	GEOMETRY::geom::Envelope env;
	long     lWidth, lHeight,lChannelCount,lDataType;
	int i,j,k;

	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(pszInputFileName);
	if(!pSrcWp)
	{
		return false;
	}
	//打开输入影像
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(pszInputFileName);
	if(!pSrcRS)
	{
		return false;
	}

	pSrcRS->GetExtent(&env);
	pSrcRS->GetSize(&lWidth, &lHeight);
	lDataType =(long)pSrcRS->GetBandDataType(1);
	lChannelCount =pSrcRS->GetBandCount();

	pSrcRS->CreateBuffer();

	//获取目标文件文件夹路径
	std::string path =pszOutputFileName;

	path =path.substr(0,path.rfind('\\'));
	Geodatabase::IWorkspace *pdestWS =CRasterWSFactory::GetInstance()->OpenFolder(path.c_str());
	if(!pdestWS)
	{
		return false;
	}

	//输出影像建立
	RasFileInfo rasfileInfoDes;
	rasfileInfoDes.lWidth = lWidth;			
	rasfileInfoDes.lHeight = lHeight;			
	rasfileInfoDes.lChannelNum = 1;	
	rasfileInfoDes.lDataType = lDataType;

	if(!pdestWS->CreateRasterDataset(pszOutputFileName,&rasfileInfoDes))
	{
		return false;
	}
	IRasterDatasetPtr rasDestDS =pdestWS->OpenRasterDataset(pszOutputFileName,false);

	if(!rasDestDS)
	{
		return false;
	}
	rasDestDS->CreateBuffer();
	rasDestDS->SetCoordinateExtent(env);

	//采样点
	double minValue,maxValue;
	long lSampleCount;
	long lResampledHeight, lResampledWidth;

	lResampledHeight = long(lHeight * dblResampleRatio);
	lResampledWidth = long(lWidth * dblResampleRatio);
	if((lResampledHeight > 768)||(lResampledWidth > 768))
	{
		dblResampleRatio = (double)768 / lHeight;
		if(lHeight < lWidth)
		{
			dblResampleRatio = (double)768 / lWidth;
		}
	}
	lResampledHeight = lHeight * dblResampleRatio;
	lResampledWidth = lWidth * dblResampleRatio;

	lSampleCount = lResampledHeight * lResampledWidth;
	unsigned char **pOutData;
	pOutData = new unsigned char*[lChannelCount];
	for(int i = 0; i < lChannelCount; i ++)
		pOutData[i] = new unsigned char[lSampleCount];


	for(int k = 0; k < lChannelCount; k++)
	{
		if(!pSrcRS->DataReadBand(k+1, 1, 1, lWidth, lHeight, lResampledWidth, lResampledHeight, pOutData[k]))
		{
			return FALSE;
		}
	}

	CSample *pSampleSet = NULL;
	pSampleSet = new CSample[ lSampleCount ];
	for(i = 0; i < lSampleCount; i ++)
	{
		pSampleSet[i].Create(lChannelCount);
	}

	for(i = 0; i < lSampleCount; i ++)
	{
		for(k = 0; k < lChannelCount; k++)
		{
			pSampleSet[i].Set( k, pOutData[k][i]);
		}
	}

	for(i = 0; i < lChannelCount; i ++)
	{
		delete pOutData[i];
	}
	delete [] pOutData;

	//获取中心采样值
	CSample *pCenter;
	pCenter = FuzzyKmean(pSampleSet, lSampleCount, lCenterCount, lMaxIterCount, fMovementThreshold, NULL, 1);

	if(pProgress)
	{
		pProgress->UpdateProgress("",0.1);
	}

	//分类
	CSample cPixel;
	float mindis,dis;
	BYTE byValue;
	float *fValue;
	long c,optc;
	BYTE classify;

	cPixel.Create(lChannelCount);
	fValue = new float[lChannelCount];

	{
		for (int i = 0; i < lHeight; i++)
		{
			for (int j = 0; j < lWidth; j++)
			{	
				for (int k = 0; k < lChannelCount; k++)
				{
					switch (lDataType)
					{
					case BDT_BYTE:
						{
							pSrcRS->PixelIO(k+1,j+1,i+1,&byValue,true);
							fValue[k] = byValue;
						}
						break;
					default:
						break;
					}
					cPixel.Set( k, fValue[k] );
				}
				mindis = cPixel.Distance( pCenter[0] );
				optc = 0;
				for( c = 0; c < lCenterCount; c ++ )
				{
					dis = cPixel.Distance( pCenter[c] );
					if( mindis >= dis )
					{
						mindis = dis;
						optc = c;
					}
				}

				classify = optc + 1;

				rasDestDS->PixelIO(1, j+1, i+1, &classify, false);
			}

			if(pProgress)
			{
				pProgress->UpdateProgress("",0.1+0.9*i/lHeight);
			}
		}

	}

	pSrcRS->DeleteBuffer();
	rasDestDS->DeleteBuffer();

	for(i = 0; i < lSampleCount; i ++)
	{
		pSampleSet[i].Release();
	}
	cPixel.Release();

	delete []fValue;
	delete []pCenter;
	delete []pSampleSet;

	if(pProgress)
	{
		pProgress->UpdateProgress("",1.0);
		pProgress->Close();
	}

	return true;

}

void CSample::Create( long lSize )
{
	if( lSize <= 0 ) return;

	// first release memory.
	Release();

	// then allocate new block
	m_lSize = lSize;
	m_pData = new float[ m_lSize ];
}

void CSample::Release()
{
	if( m_pData )
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	m_lSize = 0;
}

float CSample::Distance( CSample &cOther )
{
	if( m_lSize != cOther.GetSize() ) 
		return (float)1.0e10;

	float sum = 0;
	for( long m = 0; m < m_lSize; m ++ )
	{
		float fValue = cOther.Get( m );
		sum += ( m_pData[m] - fValue ) * ( m_pData[m] - fValue );
	}
	return sum;
}

// read sample seed from the seed file.
void ReadSeed( char *pName, CSample *pSeed, long lSeedCount, long data_length )
{
	if ( !pName ) return;
	if ( !pSeed ) return;
	FILE	*file ;
	char pStr[ 1024 ];

	if( lSeedCount <= 0 ) return;
	file = fopen( pName, "r" );

	if ( file )
	{
		//read seed by line
		for ( long seed_num = 0; seed_num < lSeedCount; seed_num ++ )
		{
			//ReadLine( file, pStr ) ;				// get a line from the file
			fgets( pStr, 1024, file );
			char	token[ 20 ] ;
			long pos = 0;

			float fDiv = 255.0f;
			if ( data_length == SIZE_SHORT ) fDiv = 65535.0f;
			else if ( data_length == SIZE_INTEGER ) fDiv = pow( 2.0, 32 ) - 1.0f;
			while ( pStr[ pos++ ] == ' ');
			if ( pStr[ pos - 1 ] >= '0')
			{
				long  channel_num = 0;
				pos = 0 ;
				while ( pos < strlen(pStr) && channel_num < pSeed[0].GetSize())
				{
					for ( long nT = 0; nT < 20; nT ++ ) token[ nT ] = 0;
					pos = GetStringToken( pStr, token, pos, ' ' ) ;
					float fToken = atof( token )/255.0f;
					if ( ( fToken >= 0.0 ) && ( fToken <= 1.0 ))
						pSeed[ seed_num ].Set( channel_num ++, fToken ) ;
					else
						pSeed[ seed_num ].Set( channel_num ++, 80.0f ) ;				
				}
			}
			else    //init seed by computing 
			{
				float fValue = (float) seed_num / lSeedCount;

				for( long m = 0; m < pSeed[0].GetSize(); m ++ )
					pSeed[ seed_num ].Set( m, fValue );
			}
		}
	}
	fclose(file) ;
}

long GetStringToken(char *source, char *destination, long start, char ch)
{
	_ASSERT( start >= 0 );

	// at the end of the source string ?
	if ( start >= strlen( source ) )
	{
		destination = "" ;					// no token available
		return strlen( source ) ;			// return @ end of string
	}

	// skip past any termination characters at the start position
	while ( start < strlen( source ) )
	{
		if ( ch == source[start] )
			start++ ;
		else
			break ;
	}
	// find the next occurance of the terminating character
	// find termination character
	long pos = -1;
	for ( long n = start; n < strlen( source ); n++ ) 
	{
		if ( source[ n ] == ch ) 
		{
			pos = n; 
			break;
		}
	}

	if ( pos < 0 )
	{
		// terminator not found, just return the remainder of the string
		memcpy( destination, &source[ start ], strlen( source ) - start);
		return strlen( source ) ;
	}
	// found terminator, get sub string
	memcpy( destination, &source[ start ], pos - start ); 
	return pos ;
}


// use Fuzzy K-NN algorithm to cluster the sample set.
static CSample *FuzzyKmean(
						   CSample *pSampleSet, 
						   long lSampleCount, 
						   long lCenterCount,
						   long lMaxIterCount,
						   float fMovementThreshold,
						   char *pSeedFile,
						   long data_length
						   )
{
	//	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	// parameter check.
	if( !pSampleSet ) return NULL;
	if( lSampleCount == 0 ) return NULL;
	if( lCenterCount == 0 ) return NULL;
	if(	lMaxIterCount <= 0 ) return NULL;
	if ( fMovementThreshold <= 0.0 ) return NULL;

	// create class centers: old and new
	CSample *pC = new CSample[ lCenterCount ];
	if( !pC ) return NULL;

	CSample *pCp = new CSample[ lCenterCount ];
	if( !pCp ) return NULL;

	long nSize = pSampleSet[0].GetSize();
	for ( long n = 0; n < lCenterCount; n++)
	{
		pC[n].Create( nSize );
		pCp[n].Create( nSize );

	}

	// create membership matrix
	float *pM = new float[ lSampleCount * lCenterCount ];
	if( !pM ) return NULL;

	// temporary buffer
	float *pDij = new float[ lCenterCount ];
	if( !pDij ) return NULL;

	long c, // class
		s;	// sample

	// initialize the centers
	if( pSeedFile )
	{
		// read from seed file.
		ReadSeed( pSeedFile, pC, lCenterCount, data_length );
	}
	else
	{
		// uniformly divide the range [ 0, 255 ], only used to image.
		for( long c = 0; c < lCenterCount; c ++ )
		{
			// value
			float fValue = (float) c / lCenterCount;

			for(long m = 0; m < pC[ c ].GetSize(); m ++ )
				pC[ c ].Set( m, fValue );
		}
	}

	// begin iteration.
	long lIter = 0;

	{
		while( lIter < lMaxIterCount )
		{
			lIter ++;

			// compute the membership of every samples to every centers.
			for( s = 0; s < lSampleCount; s ++ )
			{
				float fm = 0;

				// index
				long sC = s * lCenterCount;


				// compute the sum of the distance from this sample to all centers
				for( c = 0; c < lCenterCount; c ++ )
				{
					float dis = pSampleSet[ s ].Distance( pC[ c ]);
					if ( dis < 1.0e-5 ) dis = 1.0e-5f;
					pDij[c] = 1.0f / dis;
					fm += pDij[ c ];
				}

				if( fabs( fm ) < 1.0e-3 )
				{
					// if the fm is nearly zero, set uniform membership for each class
					for( c = 0; c < lCenterCount; c ++ )
						pM[ sC + c ] = 1.0f / lCenterCount;
				}
				else
				{
					// for each class
					for( c = 0; c < lCenterCount; c ++ )
					{
						pM[ sC + c ] = pDij[ c ] / fm;
					}
				}
			}

			// temporay sample
			CSample cTemp;
			cTemp.Create( pC[0].GetSize() );

			// compute the new centers
			for( c = 0; c < lCenterCount; c ++ )
			{
				// initialize the temp sample
				for( long m = 0; m < cTemp.GetSize(); m ++ )
					cTemp.Set( m, 0 );

				float fm = 0;

				// for each sample
				for( s = 0; s < lSampleCount; s ++ )
				{
					// index
					long sC = s * lCenterCount;

					// sum
					float mik_2 = pM[ sC + c ];
					mik_2 *= mik_2;	
					fm += mik_2;

					for( long m = 0; m < cTemp.GetSize(); m ++ )
					{
						float fValue = cTemp.Get( m );
						fValue += mik_2 * pSampleSet[ s ].Get( m );
						cTemp.Set( m, fValue );
					}
				}

				if( fabs( fm ) < 1.0e-10f ) 
					fm = 1.0e-5f;
				for( long lm = 0; lm < cTemp.GetSize(); lm ++ )
				{
					pCp[ c ].Set( lm, cTemp.Get( lm ) / fm );
				}
			}

			// compare C and Cp
			bool bAll = true;
			for( c = 0; c < lCenterCount; c ++ )
			{
				// compute distance from C to Cp
				float dis = pC[ c ].Distance( pCp[ c ] );
				if( dis > fMovementThreshold )
				{
					bAll = false;
					break;
				}
			}

			// all finished?
			if( bAll )
				break;

			// swap the Cp and C, continue the iteration.
			CSample *pTemp = pCp;
			pCp = pC;
			pC = pTemp;
		}
	}

	// release.
	delete[] pM;
	delete[] pCp;
	delete[] pDij;

	return pC;
}

}