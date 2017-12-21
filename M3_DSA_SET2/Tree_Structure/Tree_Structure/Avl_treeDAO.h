#pragma once
#ifndef Avl_treeDAO_HEADER
#define Avl_treeDAO_HEADER
#include "Avl_tree.h"

class Avl_treeDAO 
{
public:
	Avl_treeDAO();
	~Avl_treeDAO();
	string insert();
	void display();
	void getNoOfProduct();
	void mirrorTree();
	int checkUserInput();
	

private:
	Avl_tree avlTree;

	double checkPrice();
};

#endif