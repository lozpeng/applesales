//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2008-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2008.6
// ������  �༭����
//////////////////////////////////////////////////////////////////////

#ifndef  _FEATUREEDITCACHE_H_
#define  _FEATUREEDITCACHE_H_

#include "IFeatureClass.h"
#include "SpatialQuery.h"
#include <string>
#include <map>
#include <vector>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace Geodatabase
{

//Ҫ�ر༭������
enum EditOperationType
{
    OP_ADD =0,   //���
	OP_UPDATE =1, //����
	OP_DELETE =2  //ɾ��
};
//��һ��Ҫ�����б༭��һ������
struct FEditStep
{
    EditOperationType EditType; //����������
    long Fid; //Ҫ�صı��
	CFeaturePtr pFeature; 
};

class GEODATABASE_DLL CFeatureEditCache
{
public:
	CFeatureEditCache(IFeatureClass *pFeatureClass);
	virtual ~CFeatureEditCache();

public:

	//�������FeatureClass���ܵļ�¼��Ŀ������ɾ���ĺ��¼ӵ�
	long GetTotalNum() const;

	//�����Ч��¼����Ŀ
	long GetValidNum() const;

	//�Ƿ��ܽ��л��˲���
    bool CanUndo() const;
    //�Ƿ��ܽ�����������
	bool CanRedo() const;

	void Undo();

	void Redo();
	//���һ��Ҫ��
	void AppendFeature(CFeaturePtr pFeature);

	//ɾ��һ��Ҫ��
	void DeleteFeature(long Fid);
    //����һ��Ҫ��
    void UpdateFeature(CFeaturePtr pFeature);

	//Ҫ���Ƿ�ɾ��
	bool IsFeatureDelete(long Fid) const;

	//Ҫ���Ƿ�����ڱ༭������
	bool IsFeatureExist(long Fid) const;
	//�õ�ָ��Ҫ��
	CFeaturePtr GetFeature(long Fid);

	//������������༭��ջ��ʹ������һ��Ҫ�صļ�¼ֻ��һ��
	void Arrange();

	//�ڻ����в�ѯ
	void QueryByExtent(GEOMETRY::geom::Envelope *pEnvelop,boost::dynamic_bitset<> &flags);

	void Query(CSimpleQuery *query,boost::dynamic_bitset<> &flags);


private:

	//�������ջ�ж���ļ�¼
	void RemoveRedundant();

	//�򵥲�ѯ
	void SimpleQuery(CSimpleQuery *query,boost::dynamic_bitset<> &flags);

	//�ռ��ѯ
	void SpatialQuery(CSpatialQuery *query,boost::dynamic_bitset<> &flags);


public:
	IFeatureClass *m_pFeatureClass;

	std::vector<FEditStep*> m_operationStack;

	long   m_lCursor;    //��ǰ�Ļع�ָ��

	long   m_lnextRecId; //��һ����¼��Id,Ҳ�����ܵļ�¼��Ŀ��һ������ɾ���ĺ��¼ӵļ�¼

	long   m_lvalidNum; //��Ч�ļ�¼����Ŀ

};






}




#endif