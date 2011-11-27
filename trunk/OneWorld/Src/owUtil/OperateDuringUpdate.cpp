#include <owUtil/OperateDuringUpdate.h>
#include <osg/ref_ptr>
#include <osg/NodeCallback>
#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>

namespace owUtil
{
	class ChildrenUpdateCallback : public osg::NodeCallback
	{
	public:
		ChildrenUpdateCallback(osg::Group* group)
			: mParent(group)
		{
			if (group->getUpdateCallback())
				group->getUpdateCallback()->addNestedCallback(this);

			else
				group->setUpdateCallback(this);
		}

		~ChildrenUpdateCallback()
		{
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
			mChildrenWillAdd.clear();
			mChildrenWillRemove.clear();
			mChildrenWillReplace.clear();
		}

		void AddChild(osg::Node* child)
		{
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
			mChildrenWillAdd.push_back(child);
		}

		void RemoveChild(osg::Node* child)
		{
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
			mChildrenWillRemove.push_back(child);
		}

		void ReplaceChild(osg::Node* child, osg::Node* by)
		{
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
			mChildrenWillReplace.push_back(std::make_pair(child, by));
		}

		virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
		{
			
			{
				OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
				std::vector<osg::ref_ptr<osg::Node>>::iterator it_add = mChildrenWillAdd.begin();
				for (it_add; it_add != mChildrenWillAdd.end(); ++it_add)
				{
					mParent->addChild((*it_add).get());
				}
				mChildrenWillAdd.clear();

				std::vector<osg::ref_ptr<osg::Node>>::iterator it_remove = mChildrenWillRemove.begin();
				for (it_remove; it_remove != mChildrenWillRemove.end(); ++it_remove)
				{
					mParent->removeChild((*it_remove).get());
				}
				mChildrenWillRemove.clear();

				std::vector<std::pair<osg::ref_ptr<osg::Node>, osg::ref_ptr<osg::Node>>>::iterator itr = mChildrenWillReplace.begin();
				for (itr; itr != mChildrenWillReplace.end();++itr )
				{
					mParent->replaceChild(((*itr).first).get(), ((*itr).second).get());
				}
				mChildrenWillReplace.clear();


			}
			//if (mParent->getUpdateCallback() == this)
			//{
			//	if (getNestedCallback())
			//		mParent->setUpdateCallback(getNestedCallback());
			//	else
			//		mParent->setUpdateCallback(NULL);
			//} else
			//{
			//	osg::ref_ptr<osg::NodeCallback> nc = getNestedCallback();

			//	mParent->getUpdateCallback()->removeNestedCallback(this);

			//	if (nc.get()) mParent->getUpdateCallback()->addNestedCallback(nc.get());
			//}

		}

	private:
		std::vector<osg::ref_ptr<osg::Node>> mChildrenWillAdd;
		std::vector<osg::ref_ptr<osg::Node>> mChildrenWillRemove;
		std::vector<std::pair<osg::ref_ptr<osg::Node>, osg::ref_ptr<osg::Node>>> mChildrenWillReplace;

		OpenThreads::Mutex _mutex;

		osg::ref_ptr<osg::Group> mParent;
	};

	ChildrenUpdateCallback* GetChildrenUpdateCallback(osg::Node* parent)
	{
		osg::NodeCallback* callback = parent->getUpdateCallback();
		if (!callback) return NULL;

		ChildrenUpdateCallback* cucc = dynamic_cast<ChildrenUpdateCallback*>(callback);
		if (cucc) return cucc;

		osg::NodeCallback* nc = callback->getNestedCallback();
		while (nc)
		{
			cucc = dynamic_cast<ChildrenUpdateCallback*>(nc);

			if (cucc) return cucc;

			nc = nc->getNestedCallback();
		}

		return NULL;
	}

	void AddChildToParentDuringUpdate(osg::Node* child, osg::Group* parent)
	{
		ChildrenUpdateCallback* cucc = GetChildrenUpdateCallback(parent);

		if (!cucc) cucc = new ChildrenUpdateCallback(parent);

		cucc->AddChild(child);
	}

	void RemoveChildFromParentDuringUpdate(osg::Node* child, osg::Group* parent)
	{
		ChildrenUpdateCallback* cucc = GetChildrenUpdateCallback(parent);

		if (!cucc) cucc = new ChildrenUpdateCallback(parent);

		cucc->RemoveChild(child);
	}

	void ReplaceChildFromParentDuringUpdate(osg::Node* child, osg::Node* by, osg::Group* parent)
	{
		ChildrenUpdateCallback* cucc = GetChildrenUpdateCallback(parent);

		if (!cucc) cucc = new ChildrenUpdateCallback(parent);

		cucc->ReplaceChild(child, by);
	}
}

