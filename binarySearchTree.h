/*
 * tree.h
 *
 *  Created on: Nov 4, 2019
 *      Author: Eric
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include<iostream>
// forward declaration of the template class binarySearchTree
template<class DataType>
class binarySearchTree;

// treeNode class
template <class DataType>
class treeNode
{
    friend class binarySearchTree<DataType>;
    // the rest of the treeNode class declaration goes here
public:
    treeNode();
    treeNode(DataType data);
    ~treeNode();
private:
    DataType data;
    treeNode<DataType>* left;
    treeNode<DataType>* right;
    treeNode<DataType>* leftNode()
	{
    	return left;
	}
    treeNode<DataType>* rightNode()
	{
		return right;
	}
    void changeLeft(treeNode<DataType>* leftNode)
	{
    	left = leftNode;
	}
    void changeRight(treeNode<DataType>* rightNode)
	{
		right = rightNode;
	}
    DataType& theData()
    {
    	return data;
    }
    void changeData(DataType a)
    {
    	data = a;
    }
};

// binarySearchTree class
template <class DataType>
class binarySearchTree
{
public:
	binarySearchTree();
	binarySearchTree& operator=(const binarySearchTree<DataType>& anotherTree);
	binarySearchTree(const binarySearchTree<DataType>& otherTree);
	virtual ~binarySearchTree()
	{
		deleteAll();
	}
	bool empty() const
	{
		return numNodes == 0;
	}
	std::size_t size() const
	{
		return numNodes;
	}
	void print() const
	{
		inOrder(this->root, std::cout);
	}
	void debug(std::ostream &out) const
	{
		inOrder(this->root, out);
	}
	bool find(const DataType &searchItem, void (*foundNode)(const DataType&));
	bool erase(const DataType &deleteItem);
	void insert(const DataType &newItem);
	void insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem));
	void traverse(void (*itemFound)(const DataType& foundItem)) const
	{
		inOrderTraverse(root, itemFound);
	}
    // Your binarySearchTree goes here
private:
	int numNodes;
	treeNode<DataType>* root = nullptr;
	void inOrderOther(treeNode<DataType>* theNode);
	void inOrderTraverse(treeNode<DataType>* theNode, void (*itemFound)(const DataType& foundItem)) const;
	void inOrder(treeNode<DataType>* theNode, std::ostream &out) const;
	void deleteAll();
	void deleteAll(treeNode<DataType>  *node);
};
template<typename DataType> binarySearchTree<DataType>::binarySearchTree()
{
	numNodes = 0;
	root = nullptr;
}
template<typename DataType> binarySearchTree<DataType>& binarySearchTree<DataType>::operator=(const binarySearchTree<DataType>& anotherTree)
{
	deleteAll();
	root = nullptr;
	inOrderOther(anotherTree.root);
	return *this;
}
template<typename DataType> binarySearchTree<DataType>::binarySearchTree(const binarySearchTree<DataType>& otherTree)
{
	numNodes = 0;
	root = nullptr;
	inOrderOther(otherTree.root);
}
template<typename DataType> bool binarySearchTree<DataType>::find(const DataType &searchItem, void (*foundNode)(const DataType&))
{
	treeNode<DataType>* currNode = root;
	while(currNode != nullptr)
	{
		if(currNode->theData() == searchItem)
		{
			foundNode(currNode->theData());
			return true;
		}
		if(currNode->theData() < searchItem)
			currNode = currNode->rightNode();
		else
			currNode = currNode->leftNode();
	}
	return false;
}
template<typename DataType> bool binarySearchTree<DataType>::erase(const DataType &deleteItem)
{
	treeNode<DataType>* parentNode = nullptr;
	treeNode<DataType>* currNode = root;
	while(currNode != nullptr)
	{
		if(currNode->theData() == deleteItem)
		{
			if(currNode->leftNode() == nullptr && currNode->rightNode() == nullptr)
			{
				if(parentNode == nullptr)
				{
					delete root;
				}
				else if(parentNode->leftNode()->theData() == deleteItem)
				{
					delete currNode;
					parentNode->changeLeft(nullptr);
				}
				else
				{
					delete currNode;
					parentNode->changeRight(nullptr);
				}
			}
			else if(currNode->leftNode() != nullptr && currNode->rightNode() == nullptr)
			{
				if(parentNode == nullptr)
				{
					root = currNode->leftNode();
					delete currNode;
				}
				else if(parentNode->leftNode()->theData() == deleteItem)
				{
					parentNode->changeLeft(currNode->leftNode());
					delete currNode;
				}
				else
				{
					parentNode->changeRight(currNode->leftNode());
					delete currNode;
				}
			}
			else if(currNode->leftNode() == nullptr && currNode->rightNode() != nullptr)
			{
				if(parentNode == nullptr)
				{
					root = currNode->rightNode();
					delete currNode;
				}
				else if(parentNode->leftNode()->theData() == deleteItem)
				{
					parentNode->changeLeft(currNode->rightNode());
					delete currNode;
				}
				else
				{
					parentNode->changeRight(currNode->rightNode());
					delete currNode;
				}
			}
			else
			{
				treeNode<DataType>* nodeDelete = currNode->rightNode();
				while(nodeDelete->leftNode() != nullptr)
				{
					nodeDelete = nodeDelete->leftNode();
				}
				DataType store = nodeDelete->theData();
				erase(store);
				currNode->changeData(store);
			}
			numNodes--;
			return true;
		}
		if(currNode->theData() > deleteItem)
		{
			parentNode = currNode;
			currNode = currNode->rightNode();
		}
		else
		{
			parentNode = currNode;
			currNode = currNode->leftNode();
		}
	}
	return false;
}
template<typename DataType> void binarySearchTree<DataType>::insert(const DataType &newItem)
{
	numNodes++;
	treeNode<DataType>* theItem = new treeNode<DataType>(newItem);
	if(root == nullptr)
	{
		root = theItem;
	}
	else
	{
		treeNode<DataType>* trackPar = nullptr;
		treeNode<DataType>* track = root;
		while(track != nullptr)
		{
			if(track->theData() == newItem)
			{
				track->changeData(newItem);
				return;
			}
			else if(track->theData() > newItem)
			{
				trackPar = track;
				track = track->leftNode();
			}
			else
			{
				trackPar = track;
				track = track->rightNode();
			}
		}
		if(trackPar->theData() > newItem)
		{
			trackPar->changeLeft(theItem);
		}
		else
		{
			trackPar->changeRight(theItem);
		}
	}
}
template<typename DataType> void binarySearchTree<DataType>::insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem))
{
	numNodes++;
	treeNode<DataType>* theItem = new treeNode<DataType>(newItem);
	if(root == nullptr)
	{
		root = theItem;
	}
	else
	{
		treeNode<DataType>* trackPar = nullptr;
		treeNode<DataType>* track = root;
		while(track != nullptr)
		{
			if(track->theData() == newItem)
			{
				duplicateItemFound(track->theData(), newItem);
				return;
			}
			else if(track->theData() > newItem)
			{
				trackPar = track;
				track = track->leftNode();
			}
			else
			{
				trackPar = track;
				track = track->rightNode();
			}
		}
		if(trackPar->theData() > newItem)
		{

			trackPar->changeLeft(theItem);
		}
		else
		{
			trackPar->changeRight(theItem);
		}
	}
}
template<typename DataType> void binarySearchTree<DataType>::inOrderOther(treeNode<DataType>* theNode)
{
	if(theNode == nullptr)
		return;
	insert(theNode->theData());
	inOrderOther(theNode->leftNode());
	inOrderOther(theNode->rightNode());
}
template<typename DataType> void binarySearchTree<DataType>::inOrderTraverse(treeNode<DataType>* theNode, void (*itemFound)(const DataType& foundItem)) const
{
	if(theNode == nullptr)
		return;
	inOrderTraverse(theNode->leftNode(), itemFound);
	itemFound(theNode->theData());
	inOrderTraverse(theNode->rightNode(), itemFound);
}
template<typename DataType> void binarySearchTree<DataType>::inOrder(treeNode<DataType>* theNode, std::ostream &out) const
{
	if(theNode == nullptr)
	{
		return;
	}
	inOrder(theNode->leftNode(), out);
	out << theNode->theData() << "\n";
	inOrder(theNode->rightNode(), out);
}
template<typename DataType> void binarySearchTree<DataType>::deleteAll()
{
	deleteAll(root);
	root = nullptr;
}
template<typename DataType> void binarySearchTree<DataType>::deleteAll(treeNode<DataType>  *node)
{
	if (node != nullptr)
	{
		// delete all nodes to the left
		deleteAll(node->leftNode());
		node->changeLeft(nullptr);

		// delete all nodes to the right
		deleteAll(node->rightNode());
		node->changeRight(nullptr);

		// delete the node now
		delete node;
		numNodes--;
	}
}
template<typename DataType> treeNode<DataType>::treeNode()
{
	left = nullptr;
	right = nullptr;
}
template<typename DataType> treeNode<DataType>::treeNode(DataType data)
{
	this->data = data;
	left = nullptr;
	right = nullptr;
}
template<typename DataType> treeNode<DataType>::~treeNode()
{
	delete left;
	delete right;
}
#endif /* BINARYSEARCHTREE_H_ */
