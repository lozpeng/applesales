#include "stdafx.h"
#include "ShapeFeatureCursor.h"
#include "ShapeFeatureClass.h"
#include  <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateArraySequenceFactory.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/Polygon.h>

using namespace Geodatabase;
using namespace std;
using namespace GEOMETRY::geom;

CShapefileFeatureCursor::CShapefileFeatureCursor(CShapefileFeatureClass *pFeatureClass,const char* fields) 
:IFeatureCursor(pFeatureClass)
{


	CFeature *pFeature =new CFeature(pFeatureClass,0);
	m_pFeature =CFeaturePtr(pFeature);
	m_curPos =-1;

	
	InitFields(fields);
}

CShapefileFeatureCursor::~CShapefileFeatureCursor()
{

}



CFeaturePtr CShapefileFeatureCursor::NextFeature()
{

	long index =0;
	long size =m_flags.size();
	if(m_curPos>=0)
	{
		index =m_curPos+1;
	}

	while(index<size)
	{
		if(m_flags[index])
		{
			break;
		}
		index++;
	}
	m_curPos =index;

	if(m_curPos>=size)
	{
		return NULL;
	}


	//����һ�ε�ֵ�����
	m_pFeature->SetEmpty();

	CShapefileFeatureClass *pFeatureClass =(CShapefileFeatureClass*)m_pTable;
	index =m_curPos+1;

	m_pFeature->SetId(index);


	//����µ�����ֵ
	pFeatureClass->GetFeatureValue(index,m_pFeature,m_bhasGeometry,m_FieldsIndex);


	return m_pFeature;

}



bool CShapefileFeatureCursor::IsEOF() const
{
	long size =m_flags.size();
	if(m_curPos>=(size-1))
	{
		return true;
	}

	//���֮��û��ѡ�е�λ����Ҳ�ǵ��������

	size_t index =0;
	if(m_curPos>=0)
	{
		index =m_curPos+1;
	}

	while(index<size)
	{
		if(m_flags[index++])
		{
			return false;
		}
	}

	return true;
}


//��õ�ǰ��¼��ֵ
void CShapefileFeatureCursor::GetValues()
{


	//for(long index =1;index<=m_lFieldcount;index++)
	//{
	//	HFIELDVAL value = m_pdbInterface->Recs_GetFieldByIndex(m_hRecordset,index);

	//	if(!value)
	//	{
	//		continue;
	//	}

	//	//����Ǽ���ͼ���ֶΣ���ȡ��ͼ��
	//	if(m_Fields[index-1]->GetType()==FTYPE_GEOMETRY)
	//	{
	//		CttShape tshape;
	//		tshape.Create();

	//		if(m_pdbInterface->Field_GetShape(value,&tshape.mg_hShape))
	//		{
	//			Geometry *pGeometry =NULL;
	//			if(CotSdeFeatureClass::ConvertShape2Geometry(&tshape,&pGeometry))
	//			{
	//				m_pFeature->SetShape(pGeometry);
	//			}

	//		}
	//		tshape.Free();

	//	}
	//	else
	//	{

	//	}

	//	m_pdbInterface->Field_Free(value);
	//}



}


void CShapefileFeatureCursor::InitFields(const char* fields)
{

	long fieldcount =0;
	long i=0;
	m_bhasGeometry =false;
    CShapefileFeatureClass *pFeatureClass =(CShapefileFeatureClass*)m_pTable;
	//���������ֶ�
	if(!stricmp(fields,"*"))
	{
		m_bhasGeometry =true;
		fieldcount =pFeatureClass->FieldCount();

		for(i=1;i<=fieldcount;i++)
		{
			m_FieldsIndex.push_back(i);
			m_Fields.push_back(pFeatureClass->GetField(i));
		}

	}
	else
	{
		size_t curpos =0;
		size_t lastpos =0;
		string strFields =fields;
		curpos =strFields.find(",");

		//ֻ��һ���ֶ�
		if(curpos ==string::npos)
		{
			if(!stricmp(fields,pFeatureClass->ShapeFieldName().c_str()))
			{
				m_bhasGeometry =true;

			}
			else
			{
				long index =pFeatureClass->FindField(fields);
				if(index>0)
				{
					m_Fields.push_back(pFeatureClass->GetField(index));
					m_FieldsIndex.push_back(index);
				}
			}

		}
		else
		{
			string fieldname;
			while(curpos!=string::npos)
			{

				fieldname =strFields.substr(lastpos,curpos-lastpos);

				if(!stricmp(fieldname.c_str(),pFeatureClass->ShapeFieldName().c_str()))
				{
					m_bhasGeometry =true;

				}
				else
				{
					long index =pFeatureClass->FindField(fieldname.c_str());
					if(index>0)
					{
						m_Fields.push_back(pFeatureClass->GetField(index));
						m_FieldsIndex.push_back(index);
					}
				}

				lastpos =curpos+1;
				curpos =strFields.find(",",lastpos);
			}
			//�������һ���ֶ�
			fieldname =strFields.substr(lastpos,curpos-lastpos);

			if(!stricmp(fieldname.c_str(),pFeatureClass->ShapeFieldName().c_str()))
			{
				m_bhasGeometry =true;

			}
			else
			{
				long index =pFeatureClass->FindField(fieldname.c_str());
				if(index>0)
				{
					m_Fields.push_back(pFeatureClass->GetField(index));
					m_FieldsIndex.push_back(index);
				}
			}
		}
	}

}

long CShapefileFeatureCursor::FieldCount() const
{
	return m_Fields.size();
}

long CShapefileFeatureCursor::FindField(const char* name)
{
	long index =-1;
	for(size_t i=0;i<m_Fields.size();i++)
	{
		if(!stricmp(name,m_Fields[i]->GetName().c_str()))
		{
			index =i+1;
			break;
		}
	}
	return index;
}

CFieldPtr CShapefileFeatureCursor::GetField(long index)
{
	if(index<=0 || index>m_Fields.size())
	{
		return CFieldPtr();
	}

	return m_Fields[index-1];
}
