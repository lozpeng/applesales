/* Generated by Together */

#ifndef CPICLINESYMBOL_H
#define CPICLINESYMBOL_H
#include "ILineSymbol.h"
#include "IArchive.h"
#include "IArchive.h"
class CtoBitMapSymbol;
namespace Display{
class CPicLineSymbol : public ILineSymbol 
{
friend class CtoBitMapSymbol;
public:
	CPicLineSymbol();
	~CPicLineSymbol();

	virtual void Draw(void * pObject );   
	void SetXScale(double dScaleX);
	void SetYScale(double dScaleY);
	void SetBitMapSymbol(CtoBitMapSymbol* pBitMapSymbol);

    virtual void serialization(SYSTEM::IArchive & ar);

private:

	double m_dScaleX;			//x�Ŵ�
	double m_dScaleY;			//y�Ŵ�

//	CBitMapSymbol* m_pBitMapSymbol;
};

}
namespace Display{

typedef SYSTEM::CSmartPtr<CPicLineSymbol> IPicLineSymbolPtr;
}
#endif //CPICLINESYMBOL_H
