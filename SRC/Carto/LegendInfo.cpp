#include "stdafx.h"
#include "LegendInfo.h"

namespace Carto
{

/////////////////////////////CLegendGroup////////////////////////////////////

long CLegendGroup::GetItemCount()
{
	return (long)m_Items.size();
}

LegendItem CLegendGroup::GetItem(long index)
{
	assert(index>=0 && index<GetItemCount());

	return m_Items[index];
}

void CLegendGroup::Clear()
{
	m_Items.clear();
}

void CLegendGroup::AddItem(const Carto::LegendItem &item)
{
	m_Items.push_back(item);
}

std::string CLegendGroup::GetHeading()
{
	return m_strHeading;
}

void CLegendGroup::SetHeading(std::string strHeading)
{
	m_strHeading =strHeading;
}


/////////////////////////////CLegendInfo////////////////////////////////////

CLegendInfo::CLegendInfo()
{

}

CLegendInfo::~CLegendInfo()
{

}

long CLegendInfo::LegendGroupCount()
{
	return (long)m_Groups.size();
}

CLegendGroupPtr CLegendInfo::GetLegendGroup(long index)
{
	if(index<0 || index>=LegendGroupCount())
	{
		return NULL;
	}

	return m_Groups[index];
}

void CLegendInfo::AddGroup(Carto::CLegendGroupPtr pLegendGroup)
{
	m_Groups.push_back(pLegendGroup);
}


} //namespace Carto