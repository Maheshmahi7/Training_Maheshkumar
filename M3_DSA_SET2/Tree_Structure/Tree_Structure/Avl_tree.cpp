#include "Avl_tree.h"

int leftHeight, rightHeight, maxmiumHeight, balanceFactor;

Avl_node *temp1;

Avl_tree::Avl_tree()
{
	
}


Avl_tree::~Avl_tree()
{
}

/*Finding the maximum value for the given input value*/
int Avl_tree::max(int first, int second){
	if (first > second){
		return first;
	}
	else
	{
		return second;
	}
}

/*Method to calculate the height of the given node(depth of the tree)*/
int Avl_tree::heightOfTree(Avl_node *temp){
	int height = 0;
	if (temp != NULL){
		leftHeight = heightOfTree(temp->left);
		rightHeight = heightOfTree(temp->right);
		maxmiumHeight = max(leftHeight, rightHeight);
		height = maxmiumHeight + 1;
	}
	return height;
}

/*Method to calculate the balance factor*/
int Avl_tree::differenceBetweenNode(Avl_node *temp){
	leftHeight = heightOfTree(temp->left);
	rightHeight = heightOfTree(temp->right);
	balanceFactor = leftHeight - rightHeight;
	return balanceFactor;
}

/*Method to rotate the tree according to the balance factor value*/
Avl_node *Avl_tree::balance_factor(Avl_node *temp){
	balanceFactor = differenceBetweenNode(temp);
	    if (balanceFactor > 1)
	    {
	        if (differenceBetweenNode(temp->left) > 0)
	            temp = leftLeftRotation(temp);
	        else
	            temp = leftRightRotation(temp);
	    }
	    else if (balanceFactor < -1)
	    {
	        if (differenceBetweenNode(temp->right) > 0)
	            temp = rightLeftRotation(temp);
	        else
	            temp = rightRightRotation(temp);
	    }
	    return temp;
}

Avl_node *Avl_tree::rightRightRotation(Avl_node *temp){
	temp1 = temp->right;
	temp->right = temp1->left;
	temp1->left = temp;
	return temp1;
}

Avl_node *Avl_tree::leftLeftRotation(Avl_node *temp){
	temp1 = temp->left;
	temp->left = temp1->right;
	temp1->right = temp;
	return temp1;
}

Avl_node *Avl_tree::rightLeftRotation(Avl_node *temp){
	temp1 = temp->right;
	temp->right = leftLeftRotation(temp1);
	return rightRightRotation(temp);
}

Avl_node *Avl_tree::leftRightRotation(Avl_node *temp){
	temp1 = temp->left;
	temp->left = rightRightRotation(temp1);
	return leftLeftRotation(temp);
}

Avl_node *Avl_tree::insert(Avl_node *root,double price,string productName){
	if (root == NULL)
		{
		root = new Avl_node;
		root->price = price;
		root->productName.push_back(productName);
		root->left = NULL;
		root->right = NULL;
		}
	else if (price == root->price)
	{
		root->productName.push_back(productName);
	}
	else if (price < root->price)
		{
		root->left = insert(root->left, price,productName);
		root = balance_factor(root);
		}
	else if (price >= root->price)
		{
		root->right = insert(root->right, price,productName);
		root = balance_factor(root);
		}
	return root;
}

/*Method to get number of product in */
Avl_node *Avl_tree::getNoOfProduct(Avl_node *temp,double price){
	/*searching for the price from the tree*/
	if (price == temp->price)
	{
	}
	else if (price < temp->price)
	{
		temp = getNoOfProduct(temp->left, price);
	}
	else if (price >= temp->price)
	{
		temp = getNoOfProduct(temp->right, price);
	}
	return temp;
}

Avl_node *Avl_tree::mirrorTree(Avl_node *tree){
		if (tree == NULL)
				return tree;
			/*Recursively calling the mirror function*/
			mirrorTree(tree->left);
			mirrorTree(tree->right);

			/*swap the left and right child of the node*/
			temp1 = tree->left;
			tree->left = tree->right;
			tree->right = temp1;
			return tree;
}

/*Methos for displaying the node*/
void Avl_tree::display(Avl_node *temp){
	display(temp->left);
	cout << temp->price << endl;
	display(temp->right);
}

void Avl_tree::display(Avl_node *temp,int level){
	int i;
    if (temp!=NULL)
    {
        display(temp->right, level + 1);
        printf("\n");
        if (temp == root)
        cout<<"Root -> ";
        for (i = 0; i < level && temp != root; i++)
            cout<<"        ";
        cout<<temp->price;
        display(temp->left, level + 1);
    }
}