#pragma once
#ifndef Avl_node_HEADER
#define Avl_node_HEADER

#include<vector>

using namespace std;

class Avl_node
{
public:
	Avl_node();
	~Avl_node();
	Avl_node *left;
	Avl_node *right;
	void setPrice(double);
	double getPrice();
	void setProductName(string);
	vector<string> getProductName();

private:
	double price;
	vector<string> productName;

};

#endif