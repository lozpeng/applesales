#include "stdafx.h"
#include "MagicStick.h"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace ImageProcess
{

//���ӣ��������λ��
typedef struct{
	int Height;
	int Width;
}Seed;

GEOMETRY::geom::Polygon *MagicStick(Geodatabase::IRasterDataset* pDataset,int x,int y,unsigned char rate)
{

    return NULL;   
}


bool AreaIncrease(unsigned char *pRed,unsigned char *pGreen,unsigned char *pBlue,long lwidth,long lheight,int x,int y,unsigned char value,unsigned char rate,std::vector<IntPoint> &points)
{
	//��־�Ƿ��ǵ�����
	bool bsingle=false;
	if(0==pGreen && 0==pBlue)
	{
		bsingle=true;
	}


	if(value>255-rate )
		value=255-rate;
	if(value<rate)
		value=rate;

	//����ֵ
	unsigned char pixel;

	//���Ӷ�ջ��ָ��
	Seed *Seeds;
	int StackPoint;

	//��ǰ����λ��
	int iCurrentPixelx,iCurrentPixely;

	//��ǰɨ��������������
	const unsigned int nPixelCount=lwidth*lheight;
	//��־λ
	boost::dynamic_bitset<> sbitset;
	sbitset.resize((lwidth+2)*(lheight+2));

	//��ʼ������
	Seeds = new Seed[nPixelCount];
	Seeds[0].Height = y;
	Seeds[0].Width = x;
	StackPoint = 0;
	sbitset.set(lwidth*(y-1)+x-1);

	//������ʱ�����
	if(bsingle)
	{
		unsigned char *lpSrc=0;

		while( StackPoint != -1)
		{
			//ȡ������
			iCurrentPixelx = Seeds[StackPoint].Width;
			iCurrentPixely = Seeds[StackPoint].Height;
			StackPoint--;

			lpSrc = pRed + lwidth * (iCurrentPixely-1) + iCurrentPixelx-1;
			//ȡ�õ�ǰָ�봦������ֵ
			pixel = *lpSrc;

			//����ǰ��Ϳ��
			/**lpSrc = (unsigned char)255;*/

			//�ж�����ĵ㣬����ڷ�Χ�ڣ�����û�����ջ����ѹ���ջ

			if(iCurrentPixelx > 1)
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2))
				{
					lpSrc = pRed + lwidth * (iCurrentPixely-1) + iCurrentPixelx-2;
					//ȡ�õ�ǰָ�봦������ֵ
					pixel =*lpSrc;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely;
						Seeds[StackPoint].Width = iCurrentPixelx - 1;
						//��־λ��Ϊ1
						sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2);

					}
				}

			}

			//�ж�����ĵ㣬����ڷ�Χ�ڣ�����û�����ջ����ѹ���ջ
			if(iCurrentPixely > 1)
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1))
				{
					lpSrc = pRed+lwidth * (iCurrentPixely-2) + iCurrentPixelx-1;
					//ȡ�õ�ǰָ�봦������ֵ
					pixel =*lpSrc;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely-1;
						Seeds[StackPoint].Width = iCurrentPixelx ;
						//��־λ��Ϊ1
						sbitset.set(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1);

					}
				}
			}

			//�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ

			if(iCurrentPixelx < lwidth )
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx))
				{
					lpSrc = pRed + lwidth * (iCurrentPixely-1) + iCurrentPixelx;
					//ȡ�õ�ǰָ�봦������ֵ
					pixel =*lpSrc;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely;
						Seeds[StackPoint].Width = iCurrentPixelx +1;
						//��־λ��Ϊ1
						sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx);

					}
				}

			}

			//�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ

			if(iCurrentPixely <lheight )
			{
				if(!sbitset.test(lwidth * iCurrentPixely + iCurrentPixelx-1))
				{
					lpSrc = pRed+lwidth * iCurrentPixely + iCurrentPixelx-1;
					//ȡ�õ�ǰָ�봦������ֵ
					pixel =*lpSrc;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely+1;
						Seeds[StackPoint].Width = iCurrentPixelx ;
						//��־λ��Ϊ1
						sbitset.set(lwidth * iCurrentPixely + iCurrentPixelx-1);

					}
				}

			}
		}
	}
	//�ನ�ε����
	else
	{
		unsigned char *lpSrcR=0;
		unsigned char *lpSrcG=0;
		unsigned char *lpSrcB=0;
		long lmove;
		while( StackPoint != -1)
		{
			//ȡ������
			iCurrentPixelx = Seeds[StackPoint].Width;
			iCurrentPixely = Seeds[StackPoint].Height;
			StackPoint--;

			lmove=lwidth * (iCurrentPixely-1) + iCurrentPixelx-1;
			lpSrcR = pRed + lmove;
			lpSrcG = pGreen + lmove;
			lpSrcB = pBlue + lmove;
			//ȡ�õ�ǰָ�봦������ֵ
			pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

			//����ǰ��Ϳ��
			/**lpSrcR = (unsigned char)255;
			*lpSrcG = (unsigned char)255;
			*lpSrcB = (unsigned char)255;*/
			//�ж�����ĵ㣬����ڷ�Χ�ڣ�����û�����ջ����ѹ���ջ

			if(iCurrentPixelx > 1)
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2))
				{
					lmove=lwidth * (iCurrentPixely-1) + iCurrentPixelx-2;
					lpSrcR = pRed + lmove;
					lpSrcG = pGreen + lmove;
					lpSrcB = pBlue + lmove;
					//ȡ�õ�ǰָ�봦������ֵ
					pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely;
						Seeds[StackPoint].Width = iCurrentPixelx - 1;
						//��־λ��Ϊ1
						sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx-2);

					}
				}

			}

			//�ж�����ĵ㣬����ڷ�Χ�ڣ�����û�����ջ����ѹ���ջ
			if(iCurrentPixely > 1)
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1))
				{
					lmove=lwidth * (iCurrentPixely-2) + iCurrentPixelx-1;
					lpSrcR = pRed + lmove;
					lpSrcG = pGreen + lmove;
					lpSrcB = pBlue + lmove;
					//ȡ�õ�ǰָ�봦������ֵ
					pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely-1;
						Seeds[StackPoint].Width = iCurrentPixelx ;
						//��־λ��Ϊ1
						sbitset.set(lwidth * (iCurrentPixely-2) + iCurrentPixelx-1);

					}
				}
			}

			//�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ

			if(iCurrentPixelx < lwidth )
			{
				if(!sbitset.test(lwidth * (iCurrentPixely-1) + iCurrentPixelx))
				{
					lmove=lwidth * (iCurrentPixely-1) + iCurrentPixelx;
					lpSrcR = pRed + lmove;
					lpSrcG = pGreen + lmove;
					lpSrcB = pBlue + lmove;
					//ȡ�õ�ǰָ�봦������ֵ
					pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely;
						Seeds[StackPoint].Width = iCurrentPixelx +1;
						//��־λ��Ϊ1
						sbitset.set(lwidth * (iCurrentPixely-1) + iCurrentPixelx);

					}
				}

			}

			//�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ

			if(iCurrentPixely <lheight )
			{
				if(!sbitset.test(lwidth * iCurrentPixely + iCurrentPixelx-1))
				{
					lmove=lwidth * iCurrentPixely + iCurrentPixelx-1;
					lpSrcR = pRed + lmove;
					lpSrcG = pGreen + lmove;
					lpSrcB = pBlue + lmove;
					//ȡ�õ�ǰָ�봦������ֵ
					pixel = (*lpSrcR+*lpSrcG+*lpSrcB)/3;

					if (pixel <(value+rate) && pixel >(value-rate))
					{
						StackPoint++;
						Seeds[StackPoint].Height = iCurrentPixely+1;
						Seeds[StackPoint].Width = iCurrentPixelx ;
						//��־λ��Ϊ1
						sbitset.set(lwidth * iCurrentPixely + iCurrentPixelx-1);

					}
				}

			}
		}
	}

	/*****************************************************************************
	*�߽����
	*
	*****************************************************************************/
	long lpt1,lpt2,drawPt;//���ڱ�־λ�е�λ��
	int i,j;
	bool bStartPoint=false; //�Ƿ���ʼ��
	bool bPointfind=false;  //�Ƿ��ҵ��߽��
	IntPoint StartPoint; //��ʼ������
	IntPoint CurPoint,RecordPt; //��ǰ������

	//ɨ�跽��,����Ϊ0������ʱ�뷽������

	//int Direction[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
	int Direction[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
	//��ʼ����
	int BeginDirect;

	//�ҵ����Ͻǵ�һ���߽��
	for(j=0;j<lheight;j++)
	{
		for(i=0;i<lwidth;i++)
		{
			//����ҵ��߽��
			if(sbitset.test(lwidth*j+i))
			{
				//����Ϊ��ʼ������
				StartPoint.x=i;
				StartPoint.y=j;
				bStartPoint=true;
				break;
			}
		}
		if(bStartPoint)
		{
			break;
		}
	}
	//�赱ǰ��Ϊ��ʼ������
	CurPoint.x=StartPoint.x;
	CurPoint.y=StartPoint.y;

	//��ʼɨ�跽��Ϊ�·�
	BeginDirect=3;
	bStartPoint=false;


	while(!bStartPoint)
	{
		bPointfind=false;
		while(!bPointfind)
		{
			//���ɨ�跽����
			if(3==BeginDirect)
			{
				lpt1=lwidth*CurPoint.y+CurPoint.x-1;
				lpt2=lwidth*CurPoint.y+CurPoint.x;
			}
			//ɨ�跽����
			else if(1==BeginDirect)
			{
				lpt1=lwidth*(CurPoint.y-1)+CurPoint.x-1;
				lpt2=lwidth*(CurPoint.y-1)+CurPoint.x;
			}
			//ɨ�跽����
			else if(0==BeginDirect)
			{
				lpt1=lwidth*(CurPoint.y-1)+CurPoint.x;
				lpt2=lwidth*CurPoint.y+CurPoint.x;
			}
			//ɨ�跽����
			else if(2==BeginDirect)
			{
				lpt1=lwidth*(CurPoint.y-1)+CurPoint.x-1;
				lpt2=lwidth*CurPoint.y+CurPoint.x-1;
			}


			//���Ǹ�������ͼ��߽�����
			//����������߽�㣬����ɨ�跽�������·���
			if(CurPoint.x==0 && (1==BeginDirect || 3==BeginDirect))
			{

				if(sbitset.test(lpt2))
				{
					bPointfind=true;
					drawPt=lpt2;
				}

			}
			//���������ұ߽��,����ɨ�跽�������·���
			else if(CurPoint.x==lwidth &&(1==BeginDirect || 3==BeginDirect))
			{

				if(sbitset.test(lpt1))
				{
					bPointfind=true;
					drawPt=lpt1;
				}

			}
			//���������ϱ߽��,����ɨ�跽�������ҷ���
			else if(CurPoint.y==0 &&(0==BeginDirect || 2==BeginDirect))
			{
				if(sbitset.test(lpt2))
				{
					bPointfind=true;
					drawPt=lpt2;
				}
			}
			//���������±߽��,����ɨ�跽�������ҷ���
			else if(CurPoint.y==lheight &&(0==BeginDirect || 2==BeginDirect))
			{
				if(sbitset.test(lpt1))
				{
					bPointfind=true;
					drawPt=lpt1;
				}
			}
			//����������ͨ���
			else
			{
				if( sbitset.test(lpt1) ^ sbitset.test(lpt2) )
				{
					bPointfind=true;
					if(sbitset.test(lpt1))
					{
						drawPt=lpt1;
					}
					else
					{
						drawPt=lpt2;
					}
				}
			}
			//����Ǳ߽��
			if(bPointfind)
			{
				CurPoint.x=CurPoint.x+Direction[BeginDirect][0];
				CurPoint.y=CurPoint.y+Direction[BeginDirect][1];
				//����ص���ʼ�㣬�˳�ѭ��
				if(CurPoint.x==StartPoint.x && CurPoint.y==StartPoint.y)
				{
					bStartPoint=true; 

				}
				//��¼�߽��
				RecordPt.x =drawPt%lwidth;
				RecordPt.y =drawPt/lwidth;
				points.push_back(RecordPt);

				//��ʱ�뷽����ת1��
				BeginDirect++;
				if(BeginDirect==4)
				{
					BeginDirect=0;
				}


			}
			//�����һ����û���ҵ�����ı�ɨ�跽��
			else
			{
				BeginDirect--;
				if(BeginDirect==-1)
				{
					BeginDirect=3;
				}

			}
		}
	}

	//�ͷŶ�ջ
	delete []Seeds;

	return true;



}


}