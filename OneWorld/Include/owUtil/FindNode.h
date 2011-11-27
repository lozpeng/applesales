#ifndef owUtil_FINDNODE_H_
#define owUtil_FINDNODE_H_ 1

#include <osg/NodeVisitor>

namespace owUtil 
{
	template<typename T>
	class FindAllNodesOfTypeVisitor : public osg::NodeVisitor
	{
	public:
		FindAllNodesOfTypeVisitor():
		  osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
		  {

		  }

		  void apply(osg::Node& node)
		  {
			  T* result = dynamic_cast<T*>(&node);
			  if (result)
			  {
				  _foundNodes.push_back(result);
			  }
			  else
			  {
				  traverse(node);
			  }
		  }

		  std::vector< osg::ref_ptr<T>> _foundNodes;
	};

	/**
	* Visitor that located a node by its type
	*/
	template<typename T>
	class FindTopMostNodeOfTypeVisitor : public osg::NodeVisitor
	{
	public:
		FindTopMostNodeOfTypeVisitor():
		  osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
			  _foundNode(0)
		  {}

		  void apply(osg::Node& node)
		  {
			  T* result = dynamic_cast<T*>(&node);
			  if (result)
			  {
				  _foundNode = result;
			  }
			  else
			  {
				  traverse(node);
			  }
		  }

		  T* _foundNode;
	};

	/**
	* Searchs the scene graph downward starting at [node] and returns the first node found
	* that matches the template parameter type.
	*/
	template<typename T>
	T* findTopMostNodeOfType(osg::Node* node)
	{
		if (!node) return 0;

		FindTopMostNodeOfTypeVisitor<T> fnotv;
		fnotv.setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
		node->accept(fnotv);

		return fnotv._foundNode;
	}    

	/**
	* Searchs the scene graph upward starting at [node] and returns the first node found
	* that matches the template parameter type.
	*/
	template<typename T>
	T* findFirstParentOfType(osg::Node* node)
	{
		if (!node) return 0;

		FindTopMostNodeOfTypeVisitor<T> fnotv;
		fnotv.setTraversalMode(osg::NodeVisitor::TRAVERSE_PARENTS);
		node->accept(fnotv);

		return fnotv._foundNode;
	}

	/**
	* Searchs the scene graph starting at [node] and returns the first node found
	* that matches the template parameter type. First searched upward, then downward.
	*/
	template<typename T>
	T* findRelativeNodeOfType(osg::Node* node)
	{
		if ( !node ) return 0;
		T* result = findFirstParentOfType<T>( node );
		if ( !result )
			result = findTopMostNodeOfType<T>( node );
		return result;
	}
}

#endif //owUtil_FINDNODE_H_