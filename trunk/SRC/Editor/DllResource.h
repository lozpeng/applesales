#ifndef _DLL_RESOURCE_H_
#define _DLL_RESOURCE_H_

namespace Editor
{

class CDllResource
{
public:
	CDllResource(void);
	~CDllResource(void);
protected:
	HINSTANCE m_hOldInst;
};

}
#endif


