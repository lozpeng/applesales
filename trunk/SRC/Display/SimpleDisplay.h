#ifndef CSIMPLEDISPLAY_H
#define CSIMPLEDISPLAY_H

#include "IDisplay.h"

namespace Display
{
class DISPLAY_DLL CSimpleDisplay: public IDisplay
{
public:
	CSimpleDisplay(BOOL bLayoutDisplay = FALSE);
	virtual ~CSimpleDisplay();
	
	virtual void OnBegineDraw( long hDC );

	virtual void OnEndDraw( long hDC );

};

typedef  SYSTEM::CSmartPtr<CSimpleDisplay> CSimpleDisplayPtr;
}
#endif