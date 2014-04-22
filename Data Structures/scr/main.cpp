#include "types.h"
#include "structures.h"

void main()
{
	DS::BinaryTree<u32> bTree0; // Single Integer value Binary Tree

	bTree0.Insert(new BT::Node<u32>(10));
	bTree0.Insert(new BT::Node<u32>(5));
	bTree0.Insert(new BT::Node<u32>(15));
	bTree0.Insert(new BT::Node<u32>(13));
	bTree0.Insert(new BT::Node<u32>(3));
	bTree0.Insert(new BT::Node<u32>(7));
	bTree0.Insert(new BT::Node<u32>(20));
	bTree0.Insert(new BT::Node<u32>(18));
	bTree0.Insert(new BT::Node<u32>(8));

	int i = 0;
}