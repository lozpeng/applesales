#include "stdafx.h"
#include "OGRFeatureCursor.h"
#include "OGRFeatureClass.h"
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

COGRFeatureCursor::COGRFeatureCursor(COGRFeatureClass *pFeatureClass,const char* fields) 
:IFeatureCursor(pFeatureClass)
{


	m_curPos =-1;

	
	InitFields(fields);
}

COGRFeatureCursor::~COGRFeatureCursor()
{
    for(size_t i=0;i<m_Features.size();i++)
	{
		OGRFeature::DestroyFeature(m_Features[i]);
	}
}



CFeaturePtr COGRFeatureCursor::NextFeature()
{

    m_curPos++;
	if(m_curPos>=m_Features.size())
	{
		return CFeaturePtr();
	}

	CFeature *pFeature =NULL;
	if(!((COGRFeatureClass*)m_pTable)->ConvertFeature( m_Features[m_curPos],&pFeature))
	{
		return CFeaturePtr();
	}

	return CFeaturePtr(pFeature);
}


bool COGRFeatureCursor::IsEOF() const
{
	long size =m_Features.size();
	if(m_curPos>= (size-1))
	{
		return true;
	}


	return false;
}



void COGRFeatureCursor::InitFields(const char* fields)
{

	long fieldcount =0;
	long i=0;
	m_bhasGeometry =false;
	COGRFeatureClass *pFeatureClass =(COGRFeatureClass*)m_pTable;
	//包含所有字段
	if(!stricmp(fields,"*"))
	{
		m_bhasGeometry =true;
		fieldcount =pFeatureClass->FieldCount();

		for(i=1;i<=fieldcount;i++)
		{
			
			m_Fields.push_back(pFeatureClass->GetField(i));
		}

	}
	else
	{
		size_t curpos =0;
		size_t lastpos =0;
		string strFields =fields;
		curpos =strFields.find(",");

		//只有一个字段
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
						
					}
				}

				lastpos =curpos+1;
				curpos =strFields.find(",",lastpos);
			}
			//处理最后一个字段
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
					
				}
			}
		}
	}

}

long COGRFeatureCursor::FieldCount() const
{
	return m_Fields.size();
}

long COGRFeatureCursor::FindField(const char* name)
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

CFieldPtr COGRFeatureCursor::GetField(long index)
{
	if(index<=0 || index>m_Fields.size())
	{
		return CFieldPtr();
	}

	return m_Fields[index-1];
}
