// Author: Adam Bryant
// Creation Date: April. 15th, 2014
// Last Edited: April. 15th, 2014
// Version: 0.01
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

		~Node();

		Node<T>* mpParent;
		Node<T>* mpLeft;
		Node<T>* mpRight;

		const T& GetValue() const { return mValue; }

	private:
		T mValue;
	};
}

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
		Node<T>* pCurNode = mpRoot;
		Node<T>** pParentAddr = GetParentNode(data);
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
			else
			{
				pParentAddr = &(pCurNode->mpRight);
				pCurNode = pCurNode->mpRight;
			}
		}

		return pParentAddr;
	}

	//-----------------------------------------------------------------------------------------------------------

} // Namespace: DS

/** Changelog

2014-04-22 09:02 UTC - Zageron
- Main changed to reflect Insert format change.
- GetParentNode created to remove code copypaste.
- Version: 0.02

2014-04-22 08:30 UTC - Zageron
- Added changelog
- Completed Insert
- Version: 0.01
*/