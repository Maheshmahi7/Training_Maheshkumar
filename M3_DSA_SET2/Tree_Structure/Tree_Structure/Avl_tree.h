#pragma once

#ifndef Avl_tree_HEADER
#define Avl_tree_HEADER

#include<iostream>
#include<string>
#include<vector>
#include "Avl_node.h"


using namespace std;

class Avl_tree
{
public:
	Avl_tree();
	~Avl_tree();
	Avl_node *rightLeftRotation(Avl_node *);
	Avl_node *leftRightRotation(Avl_node *);
	Avl_node *leftLeftRotation(Avl_node *);
	Avl_node *rightRightRotation(Avl_node *);
	int heightOfTree(Avl_node *);
	Avl_node *balance_factor(Avl_node *);
	Avl_node *getNoOfProduct(Avl_node *, double);
	int differenceBetweenNode(Avl_node *);
	Avl_node *insert(Avl_node *,double,string);
	Avl_node updatePrice(Avl_node *, double);
	void display(Avl_node *);
	int max(int, int);
	Avl_node *mirrorTree(Avl_node *);


	Avl_node *root;
};

#endif