# ifndef WORKFLOWWIZARDINCLUDE_H__
#define WORKFLOWWIZARDINCLUDE_H__

#ifdef WORKFLOWWIZARDEXPORT
	#define WSEXT_CLASS		__declspec(dllexport)
#else
	#define WSEXT_CLASS    __declspec(dllimport)
#endif

# include "afxmt.h"

#ifndef WORKFLOWWIZARDEXPORT
# include "ResizableLayout.h"
# include "ResizablePage.h"
# include "TreePropSheetUtil.hpp"
# include "TreePropSheetEx.h"
#endif
#endif	//WORKFLOWWIZARDINCLUDE_H__