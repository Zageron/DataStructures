// Author: Adam Bryant
// Creation Date: April. 15th, 2014
// Last Edited: April. 22nd, 2014
// Version: 0.03
// Generic Class Definition

#pragma once

#include <type_traits>

// Binary Tree specific definitions
namespace BT
{
	// Node Definition
	template <typename T>
	class Node
	{
	public:
		Node(const T& data)
			: mValue(data)
			, mpParent(nullptr)
			, mpLeft(nullptr)
			, mpRight(nullptr)
		{ }

		Node(const T& data, const Node*& pParent, const Node* pLeft = nullptr, const Node* pRight = nullptr)
			: Node(data)
			, mpParent(pParent)
			, mpLeft(pLeft)
			, mpRight(pRight)
		{ }

		~Node()
		{

		}

		Node<T>* mpParent;
		Node<T>* mpLeft;
		Node<T>* mpRight;

		const T& GetValue() const { return mValue; }

	private:
		T mValue;
	};
} // Namespace: BT

using BT::Node;

namespace DS
{
	// B-Tree Definition
	template <typename T>
	class BinaryTree
	{
	public:
		BinaryTree();
		BinaryTree(const T& data);
		~BinaryTree();

		// Single Item Operations
		void Insert(T data);
		void Delete(T data);

		// Branch Operations
		void Graft(Node<T>* pNode);

		//template <typename RT = void>
		//RT Prune(::Node<T>* pNode);

		// Selection & Enumeration
		const Node<T>& Find(const u64 id) const;
		const u16 GetHeight() const;
		// Enumeration?

	private:
		Node<T>** GetParentNode(T data);
		Node<T>* mpRoot;
	};

	//-----------------------------------------------------------------------------------------------------------

	template <typename T>
	BinaryTree<T>::BinaryTree()
		: mpRoot(nullptr)
	{ }

	//-----------------------------------------------------------------------------------------------------------

	template <typename T>
	BinaryTree<T>::BinaryTree(const T& data)
		: BinaryTree()
	{
		mpRoot = new Node(data);
	}

	//-----------------------------------------------------------------------------------------------------------

	template <typename T>
	BinaryTree<T>::~BinaryTree()
	{

	}

	//-----------------------------------------------------------------------------------------------------------

	template <typename T>
	void BinaryTree<T>::Insert(T data)
	{
		Node<T>** pParentAddr = GetParentNode(data);

		// Root is empty
		BT::Node<T>* pNode = new BT::Node<T>(data);
		if (mpRoot == nullptr)
		{
			mpRoot = pNode;
		}
		else 
		{
			(*pParentAddr) = pNode;
		}
	}

	//-----------------------------------------------------------------------------------------------------------

	template <typename T>
	void BinaryTree<T>::Delete(T data)
	{
		Node<T>** pParentAddr = GetParentNode(data);
		Node<T>* pCurNode = nullptr;

		// Target Node has parent
		if (pParentAddr != nullptr)
		{
			pCurNode = (*pParentAddr);
		}

		// Is Root
		else
		{
			pCurNode = mpRoot;
		}

		// Target Node does not have Left Child
		if (pCurNode->mpLeft == nullptr)
		{
			// Target Node does not have Right Child
			if (pCurNode->mpRight == nullptr)
			{
				delete pCurNode;

				// Is Root
				if (pParentAddr == nullptr)
				{
					mpRoot = nullptr;
				}

				// Not Root
				else
				{
					(*pParentAddr) = nullptr;
				}
			}

			// Target Node has Right Child
			else
			{
				Node<T>** pLeafParent = &(pCurNode->mpRight);
				Node<T>* pTempLeaf = pCurNode->mpRight;
				delete pCurNode;

				// Is Root
				if (pParentAddr == nullptr)
				{
					mpRoot = pTempLeaf;
				}

				// Not Root
				else
				{
					(*pParentAddr) = pTempLeaf;
				}
			}
		}

		// Target Node has Left Child
		else
		{
			// Move left one position from the to-be-deleted node.
			Node<T>* pTempLeaf = pCurNode->mpLeft;

			// Traverse as far right as possible, to find parent of leaf.
			Node<T>** pLeafParent = nullptr;
			while (pTempLeaf->mpRight != nullptr)
			{
				pLeafParent = &(pTempLeaf->mpRight);
				pTempLeaf = pTempLeaf->mpRight;
			}

			// Remove old parent's reference to leaf.
			if (pLeafParent != nullptr)
			{
				(*pLeafParent) = pTempLeaf->mpLeft;
			}

			if (pCurNode->mpRight != nullptr && pCurNode->mpRight->GetValue() != pTempLeaf->GetValue())
			{
				pTempLeaf->mpRight = pCurNode->mpRight;		// Leaf right = target right
			}

			if (pCurNode->mpLeft != nullptr && pCurNode->mpLeft->GetValue() != pTempLeaf->GetValue())
			{
				pTempLeaf->mpLeft = pCurNode->mpLeft;		// Leaf left = target left
			}

			delete pCurNode;

			// Is Root
			if (pParentAddr == nullptr)
			{
				mpRoot = pTempLeaf;
			}

			// Not Root
			else
			{
				(*pParentAddr) = pTempLeaf;
			}
		}
	}

	//-----------------------------------------------------------------------------------------------------------

	//template <typename T>
	//template <typename RT = void>
	//RT BinaryTree<T>::Prune(::Node<T>* pNode)
	//{
	//	
	//	return nullptr;
	//}

	//-----------------------------------------------------------------------------------------------------------

	template <typename T>
	Node<T>** BinaryTree<T>::GetParentNode(T data)
	{
		Node<T>* pCurNode = mpRoot;
		Node<T>** pParentAddr = nullptr;

		// Find the parent of the target node.
		while (pCurNode != nullptr)
		{
			// pNode is greater
			if (data > pCurNode->GetValue())
			{
				pParentAddr = &(pCurNode->mpLeft);
				pCurNode = pCurNode->mpLeft;
			}

			// pNode is less
			else if (data < pCurNode->GetValue())
			{
				pParentAddr = &(pCurNode->mpRight);
				pCurNode = pCurNode->mpRight;
			}

			// pNode is the same
			else
			{
				break;
			}
		}

		return pParentAddr;
	}

	//-----------------------------------------------------------------------------------------------------------

} // Namespace: DS

/** TODO

- Balance Tree
	- Insertion?
	- Deletion?
	- Rotation?
	
- Pruning
- Grafting
- Meta-Programming Improvements
- Actual Template type support (Interface?)

*/

/** Changelog

2014-04-22 10:02 UTC - Zageron
- Implemented base of Deletion function.
- Tested all deletion cases.
- Version: 0.03

2014-04-22 09:02 UTC - Zageron
- Main changed to reflect Insert format change.
- GetParentNode created to remove code copypaste.
- Version: 0.02

2014-04-22 08:30 UTC - Zageron
- Added changelog
- Completed Insert
- Version: 0.01

*/