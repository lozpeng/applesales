#include "StdAfx.h"
#include "CotElementProp.h"
#include "SimpleElementProperSheet.h"
#include "SimpleTextProperSheet.h"
#include "PictureElementProperSheet.h"

namespace otComUI
{
CElementProp::CElementProp(void)
{
}

CElementProp::~CElementProp(void)
{
}

int CElementProp::ShowElementProp(Element::IElementPtr pElement, Carto::CMap *pMap, otComUI::ILayerPropCallback *pCallback)
{
   if(!pElement)
   {
	   return IDCANCEL;
   }
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   int ret =IDCANCEL;

   switch(pElement->GetType())
   {
   case Element::ET_SIMPLE_POINT_ELEMENT:
   case Element::ET_POLYLINE_ELEMENT:
   case Element::ET_CURVE_ELEMENT:
   case Element::ET_BEZIERCURVE_ELEMENT:
   case Element::ET_FILL_RECTANGLE_ELEMENT:
   case Element::ET_FILL_POLYGON_ELEMENT:
   case Element::ET_FILL_CIRCLE_ELEMENT:
   case Element::ET_FILL_ELLIPSE_ELEMENT:
   case Element::ET_GROUP_ELEMENT:
	   {
		   

		   CSimpleElementProperSheet sheet(" Ù–‘");
		   sheet.SetElement(pElement,pMap,pCallback);
		   ret =sheet.DoModal();
	   }
	   break;
   case Element::ET_SIMPLE_TEXT_ELEMENT:
   case Element::ET_CALLOUT_TEXT_ELEMENT:
	   {
		   
		   CSimpleTextProperSheet sheet(" Ù–‘");
		   sheet.SetElement(pElement,pMap,pCallback);
		   ret =sheet.DoModal();
	   }
	   break;
   case Element::ET_EXT_PICTURE_ELEMENT:
	   {
		  

		   CPictureElementProperSheet sheet(" Ù–‘");
		   sheet.SetElement(pElement,pMap,pCallback);
		   ret =sheet.DoModal();
	   }
	   break;

   default:
	    return IDCANCEL;
	   break;
   }

   return ret;


}

} //namespace otComUI

