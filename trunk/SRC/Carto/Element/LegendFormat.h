#ifndef ILEGEND_FORMAT_H
#define ILEGEND_FORMAT_H
#include "ISerialization.h"

namespace Element{

class CARTO_DLL CLegendFormat : public SYSTEM::ISerialization
{
public:
	CLegendFormat(void);
	~CLegendFormat(void);

	virtual void serialization(SYSTEM::IArchive &ar);   

};

}
#endif
