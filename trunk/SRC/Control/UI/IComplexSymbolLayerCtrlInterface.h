#pragma once
class IComplexSymbolLayerCtrlInterface
{

public:
	virtual void UpdateComplexSymbolLayerCtrl() = 0;
	virtual void UPdateSymbol( int nIndex, int nState ) = 0;
	virtual int GetSelect() = 0;
	virtual void SetCopySymbol( void ) = 0;
	virtual void SetPropList( int nSelect ) = 0;
	virtual void SetSelect(int nSelect) = 0;
};