#include "Avl_node.h"


Avl_node::Avl_node()
{
	left = NULL;
	right = NULL;
}


Avl_node::~Avl_node()
{
}

void Avl_node::setPrice(double price) {
	this->price = price;
}
double Avl_node::getPrice() {
	return this->price;
}

void Avl_node::setProductName(string name) {
	this->productName.push_back(name);
}
vector<string> Avl_node::getProductName() {
	return this->productName;
}