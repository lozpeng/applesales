#include "stdafx.h"
//#include "SymbolFactory.h"
#include "TextSymbol.h"


namespace Display{
CTextSymbol::CTextSymbol()
{
	m_lOffsetX = 0;							//����ƫ������ʼֵΪ0

	m_lOffsetY = 0;

	m_fOffsetX =m_fOffsetY =0.0;

	m_fAngle = 0.0f;						//����Ĭ�ϽǶ�Ϊ0

//	m_lTextSize = 10;						//���÷���Ĭ�ϴ�СΪ10;

	m_bMask = false;						//����Ĭ���Ƿ������Χ������Ĭ��false

	m_pSymbolMask = 0;						//��ʼ����Χ����ָ��

	m_dwDTFormat = DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_BOTTOM;//��ʼ��������Ϣ

	SetFont();								//��ʼ������

//	m_hFontHandle = NULL;

	m_enumUnit = SYSTEM::SYS_UNIT_POINT;

	m_fTextHeight = m_font.lfHeight;


	m_lColor = RGB(0,0,0);

	m_enumTextPosType = TXTPOS_CENTER;

}

CTextSymbol::~CTextSymbol()
{
	ClearDC();
}

CTextSymbol::CTextSymbol(const CTextSymbol& toTextSymbol)
{
	*this = toTextSymbol;	
}


void CTextSymbol::serialization(SYSTEM::IArchive & ar)
{
	ISymbol::serialization(ar); 

	ar & m_fOffsetX;				 
	ar & m_fOffsetY;				 
	ar & m_fAngle;
	ar & m_fTextSize;				 
	ar & m_bMask;
	ar & m_bRightToLeft;
	ar & m_fTextHeight;
	ar & m_font.lfHeight;				//�����ַ��߶�

	ar & m_font.lfWidth;/*m_lCharWidth;*/		//�����ַ����
	ar & m_font.lfEscapement;					//�����ַ���ת�Ƕ�
	ar & m_font.lfOrientation;
	ar & m_font.lfWeight;						//�����ַ�����,0ΪĬ��ֵ
	ar & m_font.lfItalic;					//�����ַ��Ƿ�Ϊб��
	ar & m_font.lfUnderline;					//�����ַ��Ƿ����»���
	ar & m_font.lfStrikeOut;					//���������Ƿ���ɾ����
	ar & m_font.lfCharSet;						//����������ַ���
	ar & m_font.lfOutPrecision;					//��������������ȷ��,0ΪĬ��
	ar & m_font.lfClipPrecision;					//��������Ĳü���ȷ��,0ΪĬ��
	ar & m_font.lfQuality;						//�������������,0ΪĬ������
	ar & m_font.lfPitchAndFamily;		//���������б�ʺͼ�����ʽ

	if(ar.IsRead())
	{
		std::string name;

		ar & name;

		memset(m_font.lfFaceName, 0, 32*sizeof(char));
		for(int i=0; i<name.size(); i++)
		{
			m_font.lfFaceName[i] = name.at(i);
		}

		long posType;
		ar & posType;
		m_enumTextPosType = (TEXT_POS_TYPE)posType;

	}
	else
	{
		std::string name;
		name.append(m_font.lfFaceName);
		ar & name;

		long posType = (long)m_enumTextPosType;
		ar & posType;
	}

}

CTextSymbol& CTextSymbol::operator = (const CTextSymbol& toTextSymbol)
{
	this->m_bMask			=		toTextSymbol.m_bMask;
	this->m_fAngle			=		toTextSymbol.m_fAngle;			
	this->m_fTextSize		=		toTextSymbol.m_fTextSize;
	this->m_fOffsetX		=		toTextSymbol.m_fOffsetX;
	this->m_fOffsetY		=		toTextSymbol.m_fOffsetY;

	*(ISymbol*)this = *(ISymbol*)&toTextSymbol;

	return *this;
}

void CTextSymbol::SetFont()
{
	m_font.lfHeight = 12;				//�����ַ��߶�

	m_font.lfWidth = 0;/*m_lCharWidth;*/		//�����ַ����
	m_font.lfEscapement = 0;					//�����ַ���ת�Ƕ�
	m_font.lfOrientation=0;
	m_font.lfWeight = 0;						//�����ַ�����,0ΪĬ��ֵ
	m_font.lfItalic = false;					//�����ַ��Ƿ�Ϊб��
	m_font.lfUnderline = false;					//�����ַ��Ƿ����»���
	m_font.lfStrikeOut = false;					//���������Ƿ���ɾ����
	m_font.lfCharSet = 1;						//����������ַ���
	m_font.lfOutPrecision = 0;					//��������������ȷ��,0ΪĬ��
	m_font.lfClipPrecision = 0;					//��������Ĳü���ȷ��,0ΪĬ��
	m_font.lfQuality = 0;						//�������������,0ΪĬ������
	m_font.lfPitchAndFamily = 0 | 0 << 4;		//���������б�ʺͼ�����ʽ

	strcpy(m_font.lfFaceName,"BatangChe");

}

void CTextSymbol::SetProperties( const char* PropertyName , const _variant_t& PropertyValue)
{
#define SETPROP(inVal,Val,inName,Name,VT) if( stricmp(inName,Name) == 0 ) { Val = (VT)inVal;return; }
#define SETPROP2(Val,Name,VT) SETPROP( PropertyValue , Val , PropertyName , Name , VT )

	

	SETPROP2( m_fOffsetX , "TextPosOffsetX" , float );

	SETPROP2( m_fOffsetY , "TextPosOffsetY" , float );

	SETPROP2( m_fAngle , "TextAngle" , float );

	SETPROP2( m_lColor , "TextColor" , long );

	if( stricmp( PropertyName , "TEXT_POS_TYPE" ) == 0 ) 
	{ 
		m_enumTextPosType = (TEXT_POS_TYPE)(long)PropertyValue;
		return; 
	}

	if( stricmp(PropertyName , "TextSize") == 0 ) 
	{ 
		m_fTextHeight = (float)PropertyValue;
		if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
		{
			if ( m_fTextHeight < 1.000000f )
				m_fTextHeight = 1.000000f;
		}
		else
		{
			if ( m_fTextHeight < 0.000001f)
			{
				m_fTextHeight = 0.000001f;
			}
		}
		float fHeight = UnitChangeTo( m_enumUnit , SYSTEM::SYS_UNIT_MILLIMETER , m_fTextHeight );
		m_font.lfHeight = (long)(fHeight*2.835+0.5);
		return; 
	}

	if(stricmp(PropertyName , "TextWidth") == 0)
	{
		float fRate = (float)PropertyValue;
		m_font.lfWidth = fRate*m_font.lfHeight;
		return;
	}

	if( stricmp(PropertyName , "TEXTBOLD") == 0 ) 
	{ 
		unsigned char bBold = (BOOL)PropertyValue;

		if(bBold)
			m_font.lfWeight = FW_BOLD;
		else
			m_font.lfWeight = FW_NORMAL;

		return;
	}

	SETPROP2( m_font.lfItalic , "TEXTITALIC" , BOOL );

	SETPROP2( m_font.lfUnderline , "TEXTUNDERLINE" , BOOL );

	SETPROP2( m_font.lfStrikeOut , "TEXTSTRIKEOUT" , BOOL );

	if( stricmp( PropertyName , "CHARSET" ) == 0 ) 
	{ 
		m_font.lfCharSet = (unsigned char)PropertyValue;
		return; 
	}

	if( stricmp( PropertyName , "FACENAME" ) == 0 ) 
	{ 
		std::string str;
		str = (_bstr_t)PropertyValue;
		memset(m_font.lfFaceName, 0,32*sizeof(char));
		strcpy(m_font.lfFaceName,(char*)str.c_str());
		return;
	}

	ISymbol::SetProperties(PropertyName , PropertyValue);

	
}

_variant_t CTextSymbol::GetProperties(const char* PropertyName)
{
	_variant_t vt;
#define GETPROP(inName,Name,Val,T) if( stricmp(inName,Name) == 0 ) { vt = (T)Val;return vt; }
#define GETPROP2(Name,Val,T) GETPROP(PropertyName , Name , Val , T )

	GETPROP2( "TextAngle" , m_fAngle , _variant_t );

	GETPROP2( "TextColor" , m_lColor , _variant_t );

	GETPROP2( "TextPosOffsetX" , m_fOffsetX , _variant_t );

	GETPROP2( "TextPosOffsetY" , m_fOffsetY , _variant_t );

	GETPROP2( "TEXT_POS_TYPE" , m_enumTextPosType , _variant_t );

	GETPROP2( "TextSize" , m_fTextHeight , _variant_t );

	if( stricmp(PropertyName , "TextWidth") == 0 ) 
	{ 
		if(m_font.lfHeight !=0 )
			return m_font.lfWidth/m_font.lfHeight;
		else
			return 0;
	}
//	GETPROP2( "TextWidth" , m_font.lfWidth , _variant_t );

	if( stricmp(PropertyName , "TEXTBOLD") == 0 ) 
	{ 
		unsigned char bBold;
		if(m_font.lfWeight == FW_BOLD)
			bBold =  true;
		else
			bBold =  false;

		GETPROP2( "TEXTBOLD" , bBold , _variant_t );
	}

	GETPROP2( "TEXTITALIC" , m_font.lfItalic , _variant_t );

	GETPROP2( "TEXTUNDERLINE" , m_font.lfUnderline , _variant_t );

	GETPROP2( "TEXTSTRIKEOUT" , m_font.lfStrikeOut , _variant_t); 

	GETPROP2( "CHARSET" , m_font.lfCharSet , _variant_t );

	if( stricmp(PropertyName , "FACENAME") == 0 ) 
	{ 
		std::string str = m_font.lfFaceName;
		GETPROP2( "FACENAME" , str.c_str(), _variant_t );
	}
		
	return ISymbol::GetProperties(PropertyName);

	
}			

SYMBOL_TYPE CTextSymbol::GetType()
{
	return TEXT_SYMBOL;
}									

void CTextSymbol::Zoom(float rate)
{
	if ( rate < 0.000000f )
	{
		rate = 1.000000f;
	}
	m_fOffsetX = m_fOffsetX * rate;
	m_fOffsetY = m_fOffsetY * rate;

	m_font.lfHeight = m_font.lfHeight* rate;
}



void Display::CTextSymbol::SelectDC(Display::CDC * pDC)
{

	ISymbol::SelectDC(pDC);

	DISPLAY_HANDLE hFont = pDC->CreateFont(m_font);

	if ( hFont == NULL )
	{
		//FALSERETURN_NOVAL("Error:Char Mark : SelectDC :Set Font")
	} 
	else
	{
		//m_hFontHandle = CDisplayCache::AddToDisplayCache( hFont , m_pDC );
	}

	pDC->SetFGColor(m_lColor);
	
}


void CTextSymbol::SetReadyDraw()
{

	//CDisplayCache::UseCache( m_hFontHandle , this );

}

void CTextSymbol::DrawLegend( DIS_RECT *rect , int nFlag )
{
	//if(m_fAngle)
	//{
		DIS_RECT textSize, drawRect;
		textSize.left = textSize.right = textSize.top = textSize.bottom = 0;
		m_pDC->DrawText(textSize, "Sample", DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_BOTTOM);

	
		int centerx = (rect->left + rect->right)/2;
		int centery = (rect->top + rect->bottom)/2;

		DIS_POINT ptOrg;

		switch(m_enumTextPosType)
		{
		case TXTPOS_LEFTTOP:
			{
				drawRect.left = centerx - textSize.Width();
				drawRect.right = centerx;
				drawRect.top = centery - textSize.Height();
				drawRect.bottom = centery;

				ptOrg.p.x = drawRect.right;
				ptOrg.p.y = drawRect.bottom;
			}
			break;
		case TXTPOS_CENTERTOP:
			{
				drawRect.left = centerx - textSize.Width()/2;
				drawRect.right = centerx + textSize.Width()/2;
				drawRect.top = centery - textSize.Height();
				drawRect.bottom = centery;

				ptOrg.p.x = (drawRect.left + drawRect.right)/2;
				ptOrg.p.y = drawRect.bottom;
			}
			break;
		case TXTPOS_RIGHTTOP:
			{
				drawRect.left = centerx;
				drawRect.right = centerx + textSize.Width();
				drawRect.top = centery - textSize.Height();
				drawRect.bottom = centery;

				ptOrg.p.x = drawRect.left;
				ptOrg.p.y = drawRect.bottom;
			}
			break;
		case TXTPOS_LEFTCENTER:
			{
				drawRect.left = centerx - textSize.Width();
				drawRect.right = centerx;
				drawRect.top = centery - textSize.Height()/2;
				drawRect.bottom = centery + textSize.Height()/2;

				ptOrg.p.x = drawRect.right;
				ptOrg.p.y = (drawRect.top + drawRect.bottom)/2;
			}
			break;
		case TXTPOS_CENTER:
			{
				drawRect.left = centerx - textSize.Width()/2;
				drawRect.right = centerx + textSize.Width()/2;
				drawRect.top = centery - textSize.Height()/2;
				drawRect.bottom = centery + textSize.Height()/2;

				ptOrg.p.x = (drawRect.left + drawRect.right)/2;
				ptOrg.p.y = (drawRect.top + drawRect.bottom)/2;
			}
			break;
		case TXTPOS_RIGHTCENTER:
			{
				drawRect.left = centerx;
				drawRect.right = centerx + textSize.Width();
				drawRect.top = centery - textSize.Height()/2;
				drawRect.bottom = centery + textSize.Height()/2;

				ptOrg.p.x = drawRect.left;
				ptOrg.p.y = (drawRect.top + drawRect.bottom)/2;
			}
			break;
		case TXTPOS_LEFTBOTTOM:
			{
				drawRect.left = centerx - textSize.Width();
				drawRect.right = centerx;
				drawRect.top = centery;
				drawRect.bottom = centery + textSize.Height();

				ptOrg.p.x = drawRect.right;
				ptOrg.p.y = drawRect.top;
			}
			break;
		case TXTPOS_CENTERBOTTOM:
			{
				drawRect.left = centerx - textSize.Width()/2;
				drawRect.right = centerx + textSize.Width()/2;
				drawRect.top = centery;
				drawRect.bottom = centery + textSize.Height();

				ptOrg.p.x = (drawRect.left + drawRect.right)/2;
				ptOrg.p.y = drawRect.top;
			}
			break;
		case TXTPOS_RIGHTBOTTOM:
			{
				drawRect.left = centerx;
				drawRect.right = centerx + textSize.Width();
				drawRect.top = centery;
				drawRect.bottom = centery + textSize.Height();

				ptOrg.p.x = drawRect.left;
				ptOrg.p.y = drawRect.top;
			}
			break;
		}

		drawRect.left+=m_lOffsetX;
		drawRect.right +=m_lOffsetX;
		drawRect.top += m_lOffsetY;
		drawRect.bottom += m_lOffsetY;
		XFORM old = m_pDC->SetWorldTransform( -m_fAngle , 1.0f , 1.0f , ptOrg.p.x+m_lOffsetX  ,ptOrg.p.y+m_lOffsetY);

		m_pDC->DrawText(drawRect ,"Sample" ,m_dwDTFormat);	//ʵ�ֻ���	

		m_pDC->SetWorldTransformBack(old);
	//}
	//else
	//{
	//	//ʵ�ֻ���
	//	m_pDC->DrawText(*rect , "Text" ,m_dwDTFormat);	//ʵ�ֻ���	
	//}
}

void CTextSymbol::Draw(void* pObject)
{
		if( CheckNoColor(m_lColor))
			return;
	DIS_TEXT *pText = (DIS_TEXT*)pObject;

	if( pText == NULL || pText->type != Dis_Text )
	{
		//FALSERETURN_NOVAL("Error:the param can't be NULL")
	}

	//����
	DIS_RECT rect;
	rect.left = pText->textPos.left;
	rect.top = pText->textPos.top;
	rect.right =pText->textPos.right;
	rect.bottom = pText->textPos.bottom;

	DIS_RECT textSize, drawRect;
	textSize.left = textSize.right = textSize.top = textSize.bottom = 0;
	m_pDC->DrawText(textSize, pText->cText, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_BOTTOM);

	DIS_POINT ptOrg;
	switch(m_enumTextPosType)
	{
	case TXTPOS_LEFTTOP:
		{
			drawRect.left = rect.left - textSize.Width();
			drawRect.right = rect.left;
			drawRect.top = rect.bottom - textSize.Height();
			drawRect.bottom = rect.bottom;

			ptOrg.p.x = drawRect.right;
			ptOrg.p.y = drawRect.bottom;
		}
		break;
	case TXTPOS_CENTERTOP:
		{
			drawRect.left = rect.left - textSize.Width()/2;
			drawRect.right = rect.left + textSize.Width()/2;
			drawRect.top = rect.bottom - textSize.Height();
			drawRect.bottom = rect.bottom;

			ptOrg.p.x = (drawRect.left + drawRect.right)/2;
			ptOrg.p.y = drawRect.bottom;
		}
		break;
	case TXTPOS_RIGHTTOP:
		{
			drawRect.left = rect.left;
			drawRect.right = rect.left + textSize.Width();
			drawRect.top = rect.bottom - textSize.Height();
			drawRect.bottom = rect.bottom;

			ptOrg.p.x = drawRect.left;
			ptOrg.p.y = drawRect.bottom;
		}
		break;
	case TXTPOS_LEFTCENTER:
		{
			drawRect.left = rect.left - textSize.Width();
			drawRect.right = rect.left;
			drawRect.top = rect.bottom - textSize.Height()/2;
			drawRect.bottom = rect.bottom + textSize.Height()/2;

			ptOrg.p.x = drawRect.right;
			ptOrg.p.y = (drawRect.top + drawRect.bottom)/2;
		}
		break;
	case TXTPOS_CENTER:
		{
			drawRect.left = rect.left - textSize.Width()/2;
			drawRect.right = rect.left + textSize.Width()/2;
			drawRect.top = rect.bottom - textSize.Height()/2;
			drawRect.bottom = rect.bottom + textSize.Height()/2;

			ptOrg.p.x = (drawRect.left + drawRect.right)/2;
			ptOrg.p.y = (drawRect.top + drawRect.bottom)/2;
		}
		break;
	case TXTPOS_RIGHTCENTER:
		{
			drawRect.left = rect.left;
			drawRect.right = rect.left + textSize.Width();
			drawRect.top = rect.bottom - textSize.Height()/2;
			drawRect.bottom = rect.bottom + textSize.Height()/2;

			ptOrg.p.x = drawRect.left;
			ptOrg.p.y = (drawRect.top + drawRect.bottom)/2;
		}
		break;
	case TXTPOS_LEFTBOTTOM:
		{
			drawRect.left = rect.left - textSize.Width();
			drawRect.right = rect.left;
			drawRect.top = rect.bottom;
			drawRect.bottom = rect.bottom + textSize.Height();

			ptOrg.p.x = drawRect.right;
			ptOrg.p.y = drawRect.top;
		}
		break;
	case TXTPOS_CENTERBOTTOM:
		{
			drawRect.left = rect.left - textSize.Width()/2;
			drawRect.right = rect.left + textSize.Width()/2;
			drawRect.top = rect.bottom;
			drawRect.bottom = rect.bottom + textSize.Height();

			ptOrg.p.x = (drawRect.left + drawRect.right)/2;
			ptOrg.p.y = drawRect.top;
		}
		break;
	case TXTPOS_RIGHTBOTTOM:
		{
			drawRect.left = rect.left;
			drawRect.right = rect.left + textSize.Width();
			drawRect.top = rect.bottom;
			drawRect.bottom = rect.bottom + textSize.Height();

			ptOrg.p.x = drawRect.left;
			ptOrg.p.y = drawRect.top;
		}
		break;
	}

	drawRect.left+=m_lOffsetX;
	drawRect.right +=m_lOffsetX;
	drawRect.top += m_lOffsetY;
	drawRect.bottom += m_lOffsetY;
	XFORM old = m_pDC->SetWorldTransform( -m_fAngle , 1.0f , 1.0f , ptOrg.p.x+m_lOffsetX,ptOrg.p.y+m_lOffsetY);

	m_pDC->DrawText(drawRect ,pText->cText ,m_dwDTFormat);	//ʵ�ֻ���	

	m_pDC->SetWorldTransformBack(old);

	//������Ӿ���
	double dblCosA = cos (m_fAngle);
	double dblSinA = sin (m_fAngle);

	double ax, ay, bx, by, cx, cy, dx, dy;

	ax = ptOrg.p.x + (drawRect.left - ptOrg.p.x)*dblCosA + (drawRect.bottom - ptOrg.p.y)*dblSinA;
	ay = ptOrg.p.y - (drawRect.left - ptOrg.p.x)*dblSinA + (drawRect.bottom - ptOrg.p.y)*dblCosA;

	bx = ptOrg.p.x + (drawRect.right - ptOrg.p.x)*dblCosA + (drawRect.bottom - ptOrg.p.y)*dblSinA;
	by = ptOrg.p.y - (drawRect.right - ptOrg.p.x)*dblSinA + (drawRect.bottom - ptOrg.p.y)*dblCosA;

	cx = ptOrg.p.x + (drawRect.right - ptOrg.p.x)*dblCosA + (drawRect.top - ptOrg.p.y)*dblSinA;
	cy = ptOrg.p.y - (drawRect.right - ptOrg.p.x)*dblSinA + (drawRect.top - ptOrg.p.y)*dblCosA;

	dx = ptOrg.p.x + (drawRect.left - ptOrg.p.x)*dblCosA + (drawRect.top - ptOrg.p.y)*dblSinA;
	dy = ptOrg.p.y - (drawRect.left - ptOrg.p.x)*dblSinA + (drawRect.top - ptOrg.p.y)*dblCosA;

	double minx,maxx, miny, maxy;
	minx = min(min(ax, bx), min(cx, dx));
	maxx = max(max(ax, bx), max(cx, dx));
	miny = min(min(ay, by), min(cy, dy));
 	maxy = max(max(ay, by), max(cy, dy));

	pText->textPos.left = minx;
	pText->textPos.right = maxx;
	pText->textPos.top = miny;
	pText->textPos.bottom = maxy;

}

void CTextSymbol::SetOffSet(float x , float y)
{
	m_fOffsetX = x;
	m_fOffsetY = y;
}				

float CTextSymbol::GetOffsetX()
{
	return m_fOffsetX;
}							

float CTextSymbol::GetOffsetY()
{
	return m_fOffsetY;
}
void CTextSymbol::SetAngle(float fAngle)
{
	m_fAngle = fAngle;

}				

float CTextSymbol::GetAngle()
{
	return m_fAngle;
}							

void CTextSymbol::SetTextSize(float textsize)
{
	m_fTextHeight = textsize;

	if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
	{
		if ( m_fTextHeight < 1.000000f )
			m_fTextHeight = 1.000000f;
	}
	else
	{
		if ( m_fTextHeight < 0.000001f)
		{
			m_fTextHeight = 0.000001f;
		}
	}

	float fHeight = UnitChangeTo( m_enumUnit , SYSTEM::SYS_UNIT_MILLIMETER , m_fTextHeight );
	m_font.lfHeight = (long)(fHeight*2.835+0.5);
}	

float CTextSymbol::GetTextSize()
{
	return m_fTextHeight;
}

void CTextSymbol::SetTextColor(unsigned long lColor)
{
	m_lColor = lColor;
}	

unsigned long CTextSymbol::GetTextColor()
{
	return m_lColor;
}		

void CTextSymbol::SetTextFont(DIS_FONT font)
{
	m_font = font;
}	

DIS_FONT CTextSymbol::GetTextFont()
{
	return m_font;
}

void CTextSymbol::SetReadDirection(BOOL bRightToLeft)
{
	m_bRightToLeft = bRightToLeft;
}

BOOL CTextSymbol::GetReadDirection()
{
	return m_bRightToLeft;
}

void CTextSymbol::SetMaskDrawable(bool bMask)
{
	m_bMask = bMask;
}				

bool CTextSymbol::GetMaskDrawable()
{
	return m_bMask;
}					

void CTextSymbol::SetMask(ISymbolPtr pSymbolMask)
{
	m_pSymbolMask = pSymbolMask;
}		

ISymbolPtr CTextSymbol::GetMask()
{
	return m_pSymbolMask;
}	

void CTextSymbol::SetDrawFormat(unsigned int dwDTFormat)
{
	m_dwDTFormat = dwDTFormat;
}


void CTextSymbol::SetTextPosType(TEXT_POS_TYPE eType)
{
	m_enumTextPosType = eType;
}

TEXT_POS_TYPE CTextSymbol::GetTextPosType()
{
	return m_enumTextPosType;
}

void CTextSymbol::ClearDC()
{
	//if( m_hFontHandle != NULL)
	//{
	//	CDisplayCache::ReleaseCache( m_hFontHandle );
	//	m_hFontHandle = NULL;
	//}

	ISymbol::ClearDC();
}

void CTextSymbol::OnUnitChanged(SYSTEM::SYS_UNIT_TYPE oldUnit , SYSTEM::SYS_UNIT_TYPE newUnit)
{
	ISymbol::OnUnitChanged(oldUnit , newUnit);

	m_fTextHeight = UnitChangeTo( oldUnit , newUnit , m_fTextHeight );
	m_fTextSize = UnitChangeTo( oldUnit , newUnit , m_fTextSize );
	m_fOffsetX = UnitChangeTo( oldUnit , newUnit , m_fOffsetX );
	m_fOffsetY = UnitChangeTo( oldUnit , newUnit , m_fOffsetY );
}


void CTextSymbol::OnChangingInSelectDC()
{
	m_fTextSize = UnitChange( m_enumUnit , m_fTextHeight );
	m_lOffsetX = UnitChange( m_enumUnit , m_fOffsetX );
	m_lOffsetY = UnitChange( m_enumUnit , m_fOffsetY );

	ISymbol::OnChangingInSelectDC();
}

}
