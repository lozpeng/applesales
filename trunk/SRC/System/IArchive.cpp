#include "stdafx.h"
#include "IArchive.h"
#include <boost/smart_ptr.hpp>
#include <boost/format.hpp>

SYSTEM::IArchive::IArchive()
{
    bRead = true;
}

bool SYSTEM::IArchive::IsRead()
{
    return bRead;
}

bool SYSTEM::IArchive::IsSave()
{
    return !bRead;
}

void SYSTEM::IArchive::SetReadState()
{
    bRead = true;
}

void SYSTEM::IArchive::SetWriteState()
{
    bRead = false;
}

void SYSTEM::IArchive::Archive(void *data , unsigned long sz )
{
    if( bRead )
	    Read(data,sz);
	else
	    Write(data,sz);
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(long &val)
{
	if( bRead )
	{
		Read(&val,4);
	}
	else
	{
		Write(&val,4);
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(unsigned long &val)
{
	if( bRead )
	{
		Read(&val,4);
	}
	else
	{
		Write(&val,4);
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(unsigned short &val)
{
	if( bRead )
	{
		Read(&val,2);
	}
	else
	{
		Write(&val,2);
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(int &val)
{
	if( bRead )
	{
		Read(&val,4);
	}
	else
	{
		Write(&val,4);
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(float &val)
{
	if( bRead )
	{
		Read(&val,4);
	}
	else
	{
		Write(&val,4);
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(double &val)
{
	if( bRead )
	{
		Read(&val,8);
	}
	else
	{
		Write(&val,8);
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(bool &val)
{
	if( bRead )
	{
		Read(&val,1);
	}
	else
	{
		Write(&val,1);
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(wchar_t &val)
{
	if( bRead )
	{
		Read(&val,sizeof(wchar_t));
	}
	else
	{
		Write(&val,sizeof(wchar_t));
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(char &val)
{
	if( bRead )
	{
		Read(&val,1);
	}
	else
	{
		Write(&val,1);
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::IArchive::operator &(unsigned char &val)
{
	if( bRead )
	{
		Read(&val,1);
	}
	else
	{
		Write(&val,1);
	}
	return *this;
}


SYSTEM::IArchive& SYSTEM::IArchive::operator &(std::string &val)
{
	if( bRead )
	{
	    long len;
	    Read(&len,4);
		if ( len <= 0 )
			return *this;

		try{
			boost::scoped_array<char> buffer(new char[len+1]);
			memset(buffer.get(), 0, len+1);
			Read(buffer.get(), len);
			val = buffer.get();
		}catch(std::exception& ex)
		{
			//ErrorLog(ex.what());
		}
	}
	else
	{
	    long len = val.size();
	    Write(&len, sizeof(long));
		if(len > 0)
			Write((void*)val.c_str(), len);
	}
	return *this;
}

void SYSTEM::IArchive::ExportToBinString(void *Data, long DataSize, char *Buffer)
{
	unsigned char tmp,tmp2;
	unsigned char* inData = (unsigned char*)Data;
	strcpy(Buffer,"0x");
	Buffer += 2;
	long i,j;
	for( i = 0,j = 0 ; i < DataSize*2 ; i+= 2,j++ )
	{
		tmp = inData[j] >> 4;
		tmp2 = inData[j] - (tmp<<4);
		if( tmp > 9 )
			Buffer[i] = tmp - 10 + 'A';
		else
			Buffer[i] = tmp + '0';

		if( tmp2 > 9 )
			Buffer[i+1] = tmp2 - 10 + 'A';
		else
			Buffer[i+1] = tmp2 + '0';

	}
	Buffer[i] = NULL;
}

bool SYSTEM::IArchive::ImportFromBinString(const char *BinString, void *outData, unsigned long DataSize)
{
	char tmp,tmp2;
	char *Buffer = (char *)outData;
	if( BinString[0] != '0' || BinString[1] != 'x' )
		return false;
	BinString += 2;
	for(unsigned long i = 0,j = 0 ; i < DataSize*2 ; i+= 2,j++ )
	{
		tmp = BinString[i]>>4; /* x/16  */
		tmp2 = BinString[i] - (tmp<<4); /* x%16 */
		if( tmp == 4 || tmp == 6 ) /*'A' or 'a'*/
		{
			tmp2 += 9;
		}
		Buffer[j] = tmp2*16;

		tmp = BinString[i+1]>>4; /* x/16  */
		tmp2 = BinString[i+1] - (tmp<<4); /* x%16 */
		if( tmp == 4 || tmp == 6 ) /*'A' or 'a'*/
		{
			tmp2 += 9;
		}
		Buffer[j] += tmp2;
	}
	return true;
}



SYSTEM::CBinArchive::CBinArchive(void* BinSource,unsigned long Size,bool bRef)
{
    bRead = true;
	m_bRef = bRef;
	m_Size = Size;
	if( bRef )
	    m_Data = (unsigned char*)BinSource;
	else
	{
	    m_Data = (unsigned char*)malloc(Size);
	    memcpy( m_Data, BinSource , Size );
	}
	m_Pos = 0;
}

// ±£´æ
SYSTEM::CBinArchive::CBinArchive(unsigned long InitalSize)
{
    bRead = false;
	m_bRef = false;
	m_Size = 0;
	m_Data = NULL;
	if( InitalSize != 0 )
	{
	    m_Size = InitalSize;
	    m_Data = (unsigned char*)malloc(m_Size);
	    memset( m_Data, 0 , m_Size );
	}
	m_Pos = 0;
}

SYSTEM::CBinArchive::~CBinArchive()
{
    if( !m_bRef )
	    free( m_Data );
}

void SYSTEM::CBinArchive::SetReadState()
{
    IArchive::SetReadState();
 //   m_Pos = 0;
}

void SYSTEM::CBinArchive::SetWriteState()
{
    IArchive::SetWriteState();
 //   m_Pos = 0;
}

void SYSTEM::CBinArchive::Read(void *Data, long len)
{
    memcpy( Data , &m_Data[m_Pos] , len );
	m_Pos += len;
}

void SYSTEM::CBinArchive::Write(void *Data, long len)
{
    if( m_Pos +len+1 > m_Size )
	{
		m_Size = m_Pos +len+1;
		if( m_Data == NULL )
			m_Data = (unsigned char *)malloc(m_Size);
		else
			m_Data = (unsigned char *)realloc(m_Data, m_Size );
	}
	if( Data != NULL )
		memcpy( &m_Data[m_Pos] , Data , len );
	m_Pos += len;
	m_Data[m_Pos] = NULL;
}

void* SYSTEM::CBinArchive::GetData()
{
	return m_Data;
}

unsigned long SYSTEM::CBinArchive::GetSize()
{
	return m_Size;
}

bool SYSTEM::CBinArchive::IsEOF()
{
	return m_Pos+1==m_Size;
}

_variant_t SYSTEM::CBinArchive::ExportToVariant()
{
	unsigned char *tmp;
	_variant_t vt;
	SAFEARRAYBOUND sgBound[1];
	sgBound[0].lLbound = 1;
	sgBound[0].cElements = m_Pos;
	vt.vt = VT_UI1|VT_ARRAY;
	vt.parray = SafeArrayCreate( VT_UI1 , 1 , sgBound );

	SafeArrayAccessData( vt.parray , (void**)&tmp);
	memcpy(tmp , m_Data , m_Pos );
	SafeArrayUnaccessData(vt.parray);
	return vt;
}

void SYSTEM::CBinArchive::ImportVariant(const _variant_t& vt)
{
	SetWriteState();
	if( vt.vt == (VT_UI1|VT_ARRAY) )
		Write( vt.parray->pvData , vt.parray->rgsabound[0].cElements );
	else if( vt.vt == VT_BSTR )
	{
		_bstr_t bstr = vt;
		if( bstr.length() != 0 )
			Write( (char*)bstr , (long)strlen( (char*)bstr ) );
	}
	m_Pos = 0;
}

unsigned long& SYSTEM::CBinArchive::GetCurrentPos()
{
	return m_Pos;
}

void SYSTEM::CBinArchive::SetPosToBegin()
{
	m_Pos = 0;
}

////////////////////////////////////////////////////////////////////////////////



SYSTEM::CStringArchive::CStringArchive(void* StringSource,unsigned long Size,bool bRef)
:SYSTEM::CBinArchive( StringSource , Size , bRef )
{

}

// ±£´æ
SYSTEM::CStringArchive::CStringArchive(unsigned long InitalSize)
:SYSTEM::CBinArchive( InitalSize )
{

}

SYSTEM::CStringArchive::~CStringArchive()
{
}

SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(long &val)
{
	if( bRead )
	{
		val = atoi( (char*)&m_Data[m_Pos+1] );
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%ld]") % val);
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(unsigned long &val)
{
	if( bRead )
	{
		val = atoi( (char*)&m_Data[m_Pos+1] );
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%ld]") % val);
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(unsigned short &val)
{
	if( bRead )
	{
		val = (unsigned short)atoi( (char*)&m_Data[m_Pos+1] );
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%d]") % val);
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(int &val)
{
	if( bRead )
	{
		val = atoi( (char*)&m_Data[m_Pos+1] );
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%ld]") % val);
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(float &val)
{
	if( bRead )
	{
		val = (float)atof( (char*)&m_Data[m_Pos+1] );
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%f]") % val);
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(double &val)
{
	if( bRead )
	{
		val = atof( (char*)&m_Data[m_Pos+1] );
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%lf]") % val);
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(bool &val)
{
	if( bRead )
	{
		val = atoi( (char*)&m_Data[m_Pos+1] ) == 1 ? true : false;
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%d]") % (val?1:0));
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}
/*
SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(wchar_t &val)
{
	if( bRead )
	{
		val = (wchar_t)m_Data[m_Pos+1];
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		SYSTEM::CString str;
		str.Format("[%c]",val);
		Write( (char*)str , str.length() );
	}
	return *this;
}
*/
SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(char &val)
{
	if( bRead )
	{
		val = m_Data[m_Pos+1];
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%c]") % val);
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}

SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(unsigned char &val)
{
	if( bRead )
	{
		val = m_Data[m_Pos+1];
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
	}
	else
	{
		std::string str = boost::str(boost::format("[%c]") % val);
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}



SYSTEM::IArchive& SYSTEM::CStringArchive::operator &(std::string &val)
{
	if( bRead )
	{
		int Pos = m_Pos+1;
		for( m_Pos++ ; m_Data[m_Pos] != '[' && m_Pos < m_Size ; m_Pos++ );
		m_Data[m_Pos-1] = NULL;
		val = (char*)&m_Data[Pos];
		m_Data[m_Pos-1] = ']';
	}
	else
	{
		std::string str("[");
		str += val + "]";
		WriteStr( (char*)str.c_str() );
	}
	return *this;
}

_variant_t SYSTEM::CStringArchive::ExportToVariant()
{
	return (char*)m_Data;
}

void SYSTEM::CStringArchive::Read(void *Data,long len)
{
	long lenRC;

	(*this) & lenRC;

	assert( len == lenRC );

	ImportFromBinString( (const char*)(m_Data + m_Pos) , Data , len );

}

void SYSTEM::CStringArchive::Write(void *Data,long len)
{
	(*this) & len;

	char *Buffer = new char[len*2+20];
	ExportToBinString( Data , len , Buffer);
	WriteStr( Buffer );
	delete[] Buffer;
}

void SYSTEM::CStringArchive::ReadStr(char *Data)
{
	//CBinArchive::Read( Data , strlen(Data) );
}

void SYSTEM::CStringArchive::WriteStr(char *Data)
{
	CBinArchive::Write( Data , strlen(Data) );
}
