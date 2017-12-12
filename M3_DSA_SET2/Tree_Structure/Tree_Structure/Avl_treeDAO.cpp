#include "Avl_treeDAO.h"


double price;
string productName;
vector<string> product;
Avl_node *temp;

Avl_treeDAO::Avl_treeDAO()
{
	
}


Avl_treeDAO::~Avl_treeDAO()
{
}

/*DAO method to Insert values into the avl tree*/
string Avl_treeDAO::insert(){

	cout << "Enter the product name" << endl;
	cin >> productName;
	cout << "Enter the price" << endl;
	cin >> price;
	if (cin.fail()){
		price = checkPrice();
	}
	avlTree.root = avlTree.insert(avlTree.root, price, productName);
	if (avlTree.root != NULL){
		return "Inserted Successfully";
	}
	else
	{
		return "Insertion Failed";
	}
}

/*DAO method for calling GetNoOfproduct method*/
void Avl_treeDAO::getNoOfProduct(){
	cout << "Enter the price" << endl;
	cin >> price;
	if (cin.fail()){
		price = checkPrice();
	}
	if (avlTree.root != NULL){
		temp = avlTree.getNoOfProduct(avlTree.root, price);
		if (temp != NULL){
			product = temp->productName;
			cout << "No of product for the given price " << price << ":" << '\t' << product.size() << endl;
			cout << "They are: " << endl;
			for (int i = 0; i < product.size(); i++){
				cout << product[i] << endl;
			}
		}
		else
		{
			cout << "No product for the given price / price is not available" << '\n' << "Try with different price value" << endl;
		}
	}
	else
	{
		cout << "Need to Create tree inorder to display tree" << endl;
	}

}

/*DAO method for mirror tree*/
void Avl_treeDAO::mirrorTree(){
	if (avlTree.root != NULL){
		temp = avlTree.mirrorTree(avlTree.root);
		if (temp != NULL){
			avlTree.display(temp);
		}
		else{
			cout << "Mirror Tree is empty" << endl;
		}
	}
	else{
		cout << "Need to Create tree inorder to display tree" << endl;
	}
}

/*DAO method for displaying the tree*/
void Avl_treeDAO::display(){
	if (avlTree.root != NULL){
		avlTree.display(avlTree.root);
	}
	else{
		cout << "Need to Create tree inorder to display tree" << endl;
	}
}

/*Method for User input validation*/
int Avl_treeDAO::checkUserInput() {
	int input;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cout << "Enter the correct value" << endl;
			cin >> input;
		}
		else if (!cin.fail()) {
			return input;
			break;
		}
	}
}

/*Method for user input validation for price variable*/
double Avl_treeDAO::checkPrice() {
	double input;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cout << "Enter correct price" << endl;
			cin >> input;
		}
		else if (!cin.fail()) {
			return input;
			break;
		}
	}
}



