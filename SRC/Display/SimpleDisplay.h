#ifndef _SIMPLEDISPLAY_H
#define _SIMPLEDISPLAY_H

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
#endif //_SIMPLEDISPLAY_H