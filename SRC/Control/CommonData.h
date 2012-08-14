//
//������������ 
//
#pragma  once

typedef struct CalFieldValue
{
	CalFieldValue()
	{
		iIndex = -1;
		szFieldName = "";
		szType == "";
	}

	//����==������
	bool operator==( const CalFieldValue &e ) const
	{
		return e.szFieldName == szFieldName;
	}

	int iIndex;					//����
	std::string szFieldName;	//����
	std::string szType;			//����
}CAL_FIELDVALUE,  *LP_CAL_FIELDVALUE;

typedef struct FieldDisplayFormat
{
	FieldDisplayFormat()
	{
		szFieldName = "";
		szFormat = "";
		nTypeField = 0;
	}

	bool operator==( const FieldDisplayFormat &e ) const
	{
		return e.szFieldName == szFieldName;
	}

	std::string szFieldName;
	long nTypeField;
	std::string szFormat;		//��ʽ���ַ���
}FIELD_DISPLAY_FORMAT;

enum ROWTYPE
{
	FEAUTE_INDEX,
	TABLEROW_INDEX
};