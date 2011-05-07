#ifndef _BLOCKDATA_H
#define _BLOCKDATA_H
namespace Geodatabase
{


struct STBlockPos
{
	long lBand;
	long lBlockX;
	long lBlockY;

};

inline bool operator< (const STBlockPos &posa, const STBlockPos &posb)
{
	if(posa.lBand > posb.lBand)
	{
		return false;
	}

	if(posa.lBand < posb.lBand)
	{
		return true;
	}

	if(posa.lBlockY > posb.lBlockY)
	{
		return false;
	}

	if(posa.lBlockY < posb.lBlockY)
	{
		return true;
	}

	if(posa.lBlockX >= posb.lBlockX)
	{
		return false;
	}
	else if(posa.lBlockX < posb.lBlockX)
	{
		return true;
	}
}

template <class T>
class BDlist
{
public :
	struct node
	{
		node *prior;
		T data;
		node *next;
	};
	typedef node* pointer;
public:
	node *head;  //第一个节点的地址
	long length; //双向链表的长度
public:
	BDlist()
	{
		head=NULL;
		length=0;
	}
	~BDlist()
	{
		Clear();
	}
	//定位到某一元素
	node* Loc(long address)
	{
		node *p=NULL;
		long j=1;
		if((address>=1)&&(address<=length))
		{
			p=head;
			while(j<address)
			{
				p=p->next;
				j++;
			}

		}
		return p;
	}
	//在链表后添加一个新元素
	void push_back(T element)
	{
		node *newNode,*lastNode;
		newNode=new node;
		newNode->data=element;
		//如果链表中原来没有元素
		if(length==0)
		{
			head=newNode;
			newNode->prior=newNode; 
			newNode->next=newNode;
			length++;
		}
		else
		{
			lastNode=Loc(length);
			lastNode->next=newNode;
			newNode->prior=lastNode;
			newNode->next=head;
			head->prior=newNode;
			length++;
		}


	}
	//将所有的节点删除
	void Clear()
	{
		node *p,*q;
		p=head;
		for(long i=0;i<length;i++)
		{
			q=p;
			p=p->next;
			delete q;

		}
		head=NULL;
		length=0;
	}
	//链表长度
	long size()
	{
		return length;
	}

};

class GEODATABASE_DLL CBlockData
{
public:
	CBlockData();
	~CBlockData();
public:
	void *m_pBuffer;
	long m_lBufferWidth;
	long m_lBufferHeight;
	long m_lDataType;

	long m_lWidth;
	long m_lHeight;

	STBlockPos m_Pos;
	bool m_bDirty;

public:
	void Create(long lBufferWidth,long lBufferHeight,BANDDATATYPE lDataType);
	void Free();

	inline  void GetPixel(long lCol, long lRow, void *pVal);

	inline  void SetPixel(long lCol, long lRow, void *pVal);

	void SetBlockSize(long lWidth, long lHeight);

};

#define SET_PIXEL(lCol, lRow, pVal, obj)\
{\
	\
	switch (obj->m_lDataType)\
{\
	case 0:\
{\
	unsigned char* pucVal, *pucVal2;\
	pucVal = (unsigned char*)obj->m_pBuffer;\
	pucVal2 = (unsigned char*)pVal;\
	*(pucVal+obj->m_lWidth*(lRow-1)+lCol-1) =  *pucVal2 ;\
}\
	break;\
	 case 1:\
{\
	unsigned short* pusVal, *pusVal2;\
	pusVal = (unsigned short*)obj->m_pBuffer;\
	pusVal2 = (unsigned short*)pVal;\
	*(pusVal+obj->m_lWidth*(lRow-1)+lCol-1) = *pusVal2 ;\
}\
	break;\
	 case 2:\
{\
	short *psVal, *psVal2;\
	psVal = (short *)obj->m_pBuffer;\
	psVal2 = (short *)pVal;\
	*(psVal+obj->m_lWidth*(lRow-1)+lCol-1) = *psVal2 ;\
}\
	break;\
	 case 3:\
{\
	float *pfVal,*pfVal2;\
	pfVal = (float *)obj->m_pBuffer;\
	pfVal2 = (float *)pVal;\
	*(pfVal+obj->m_lWidth*(lRow-1)+lCol-1) =  *pfVal2;\
}\
	break;\
	 default:\
	 break;\
}\
	\
	obj->m_bDirty = true;\
}\

#define GET_PIXEL(lCol, lRow, pVal, obj)\
{\
	\
	switch (obj->m_lDataType)\
{\
	case 0:\
{\
	unsigned char* pucVal, *pucVal2;\
	pucVal = (unsigned char*)obj->m_pBuffer;\
	pucVal2 = (unsigned char*)pVal;\
	*pucVal2 = *(pucVal+obj->m_lWidth*(lRow-1)+lCol-1);\
}\
	break;\
	 case 1:\
{\
	unsigned short* pusVal, *pusVal2;\
	pusVal = (unsigned short*)obj->m_pBuffer;\
	pusVal2 = (unsigned short*)pVal;\
	*pusVal2 = *(pusVal+obj->m_lWidth*(lRow-1)+lCol-1);\
}\
	break;\
	 case 2:\
{\
	short *psVal, *psVal2;\
	psVal = (short *)obj->m_pBuffer;\
	psVal2 = (short *)pVal;\
	*psVal2 = *(psVal+obj->m_lWidth*(lRow-1)+lCol-1);\
}\
	break;\
	 case 3:\
{\
	float *pfVal,*pfVal2;\
	pfVal = (float *)obj->m_pBuffer;\
	pfVal2 = (float *)pVal;\
	*pfVal2 =  *(pfVal+obj->m_lWidth*(lRow-1)+lCol-1);\
}\
	break;\
	 default:\
	 break;\
}\
}

}

#endif