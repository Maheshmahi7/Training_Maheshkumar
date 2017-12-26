#include "Avl_treeDAO.h"

Avl_treeDAO::Avl_treeDAO()
{

}


Avl_treeDAO::~Avl_treeDAO()
{
}

/*DAO method to Insert values into the avl tree*/
string Avl_treeDAO::insert(){
	string productName;
	double price;

	cout << "Enter the product name" << endl;
	cin.ignore();
	getline(cin, productName);
	cout << "Enter the price" << endl;
	cin >> price;
	if (cin.fail()){
		price = checkPrice();
	}
	avlTree.root = avlTree.insert(avlTree.root, price, productName);
	return (avlTree.root != NULL) ? "Inserted Successfully" : "Insertion Failed";
}

/*DAO method for calling GetNoOfproduct method*/
void Avl_treeDAO::getNoOfProduct(){
	double price;
	Avl_node *temp;
	cout << "Enter the price" << endl;
	cin >> price;
	if (cin.fail()){
		price = checkPrice();
	}
	if (avlTree.root != NULL){
		temp = avlTree.getNoOfProduct(avlTree.root, price);
		if (temp != NULL){
			cout << "No of product for the given price " << price << ":" << '\t' << temp->getProductName().size() << endl;
			cout << "They are: " << endl;
			for (int i = 0; i < temp->getProductName().size(); i++){
				cout << temp->getProductName()[i] << endl;
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
	Avl_node *temp1;
	if (avlTree.root != NULL){
		temp1 = avlTree.root;
		temp1 = avlTree.mirrorTree(temp1);
		if (temp1 != NULL){
			cout << "Mirror of the given tree" << endl;
			avlTree.display(temp1, 1);
			cout << endl;
		}
		else{
			cout << "Mirror Tree is empty" << endl;
		}
		temp1 = avlTree.root;
		temp1 = avlTree.mirrorTree(temp1);
		cout << "Given tree" << endl;
		if (temp1 != NULL)
			avlTree.display(temp1, 1);
		cout << endl;
	}
	else{
		cout << "Need to Create tree inorder to display tree" << endl;
	}
}

/*DAO method for displaying the tree*/
void Avl_treeDAO::display(){
	if (avlTree.root != NULL){
		avlTree.display(avlTree.root, 1);
		cout << endl;
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
