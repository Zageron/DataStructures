#include "types.h"
#include "structures.h"

void main()
{
	DS::BinaryTree<u32> bTree0; // Single Integer value Binary Tree

	bTree0.Insert(20);
	bTree0.Insert(18);
	bTree0.Insert(24);
	bTree0.Insert(30);
	bTree0.Insert(27);
	bTree0.Insert(28);
	bTree0.Insert(19);
	bTree0.Insert(15);
	bTree0.Insert(16);
	bTree0.Insert(13);

	// One at a time deletion tests
	//bTree0.Delete(24); // WORKS
	//bTree0.Delete(28); // WORKS
	//bTree0.Delete(27); // WORKS
	//bTree0.Delete(30); // WORKS
	//bTree0.Delete(15); // WORKS
	//bTree0.Delete(20); // WORKS

	int i = 0;
}