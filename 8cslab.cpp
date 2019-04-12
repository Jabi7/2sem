//C++ program to make a binary tree with extra member functions like finding minimum node, replacing at parent and deletion of a node
#include<iostream>

using namespace std;

//used to create an object of Node
class Node
{
	public:
		//holds data of a node
		int data;
		
		//pointers to point to left,right children and parent
		Node *left;
		Node *right;
		Node *parent;
		
		//parameterized constructor to initialize the pointers as NULL
		Node(int value)
		{
			left = NULL;
			right = NULL;
			parent = NULL;
			data = value;
		}
};

//defines the binary search tree
class BST
{
	public:
		//holds address of the root
		Node *root;
		
		//default constructor to set root as NULL
		BST()
		{
			root = NULL;
		}
		
		//function to insert nodes to the tree
		void insert(int value)
		{
			insert2(root,value);
		}
		
		//recursive function to insert a node
		void insert2(Node *curr,int value)
		{
			//checks if root is NULL, and if yes, then sets the first value to be inserted as the root
			if(root == NULL)
				root = new Node(value);
			
			//else moves to the left and if no node present, then inserts there	
			else if(value < curr->data)	
			{
				//condition for checking if no node is present
				if(curr->left == NULL)
				{
					curr->left = new Node(value);
					curr->left->parent = curr;             //links to its parent
				}
				
				else
				{
					//moves to left again and inserts there
					insert2(curr->left,value);
				}
			}
			
			//or else moves to the right and does the above, same as left
			else
			{
				//condition for checking no node being present
				if(curr->right == NULL)
				{
					curr->right = new Node(value);
					curr->right->parent = curr;              //links to its parent
				}
				
				else
				{
					//moves to right and inserts there
					insert2(curr->right,value);
				}
			}
		}
		
		//displays the binary tree
		void display()
		{
			display2(root);
		}
		
		//recursive function that displays the tree
		void display2(Node *curr)
		{
			//if curr becomes NULL, then returns void
			if(curr == NULL)
				return;
				
			//prints in the order, left child, parent and right child
			display2(curr->left);
			cout<<curr->data<<",";
			display2(curr->right);	
		}
		
		//function to search if a value is present in the tree
		void search(int value)
		{
			cout<<endl;
			Node *var = search2(root,value);
			if(var == NULL)
				cout<<"Does not exist\n";
				
			else
				cout<<"It is present in the tree\n";	
		}
		
		//recursive function to determine presence of a value in the tree
		Node *search2(Node *curr,int value)
		{
			//checks if node's data matches with value or if is NULL, if yes then returns current node
			if(curr == NULL || curr->data == value)
				return curr;
				
			else
			{
				//moves left of node to search
				if(value < curr->data)
				{
					return search2(curr->left,value);
				}	
				
				//moves right of node to search
				else
				{
					return search2(curr->right,value);
				}
			}	
		}
		
		//displays the binary tree in a structured form
		void fancydisplay()
		{
			cout<<"*****************************"<<endl;
			fancydisplay2(root,0);                             //initially the number of spaces is 0
			cout<<"*****************************"<<endl;
		}
		
		//recursive function to display the tree as a structured form
		void fancydisplay2(Node *curr,int space)
		{
			//base case
			if(curr == NULL)
				return;
				
			space += 5;
			//displays from right to left (line by line)
			fancydisplay2(curr->right,space);
			for(int i=5; i<=space; i++)
				cout<<" ";
			
			cout<<curr->data<<endl;	
			fancydisplay2(curr->left,space);
		}
		
		//returns node with minimum value in the sub tree
		Node *find_min(Node *curr)
		{
			//returns node if its left child is NULL
			if(curr->left == NULL)
				return curr;
			
			//moves to the left to find the minimum node	
			else
			{
				find_min(curr->left);
			}	
		}
		
		//recursive function that deletes a node in the tree
		void deleteNode(int value)
		{
			//first to search for the node to be deleted
			Node *curr = search2(root,value);
			if(curr == NULL)
				cout<<"Node does not exist!"<<endl;
				
			//cases for deleting a node based on the number of children it has
			//Node has 2 children
			if(curr->left && curr->right)
			{
				//only when if node to be deleted has right child itself as the minimum node of the node's right subtree
				//in other words, the right child of the deleted node has no left child
				if(curr->right->left == NULL)
				{
					curr->data = curr->right->data;       //replaces value of the node with that of its right child
					curr->right = curr->right->right;     //links right child of node's right child as the node's right child (this removes the node whose value was used to replace that of the main node)
					curr->right->parent = curr;           //backward link
				}
				
				//otherwise, the general trend of replacing the node with the smallest node in its right subtree
				else
				{
				//only when the deleted node's right child is NOT a leaf
				if(curr->right->left && curr->right->right)
				{
				//to replace the value of the minimum element of the right children with the node
				curr->data = find_min(curr->right)->data;
				//the node is destroyed whose value is used to replace the value in the deleted node
				find_min(curr->right)->parent->left = NULL;
				}
				
				//when right child of node to be deleted is a leaf
				else
				{
					//replaces value of the node with that of its right child (which is a leaf)
					curr->data = curr->right->data;
					//erases the child from the tree
					curr->right = NULL;
				}
				}
			}
			
			//Node has 1 child
			else if(curr->left || curr->right)
			{
				//replaces value of child with the value of node to be deleted
				//basically deletes the value in the node
				if(curr->left)
				{
					//condition to check if the node to deleted is the root (root could also have just one child)
					if(curr == root)
					{
						//update root
						if(curr->left)
						{
							root = curr->left;
						}
						
						else
						{
							root = curr->right;
						}
					}
					
					//checks if the node to be deleted is a left child or not
					//also this node CANNOT be the root
					if(curr->data < curr->parent->data)
					{
						curr->parent->left = curr->left;
					}
					
					else
					{
						curr->parent->right = curr->left; 
					}
				}
				
				else
				{
					//checks if the node to be deleted is a left child or not
					//similarly, even this node CANNOT be the root
					if(curr->data < curr->parent->data)
					{
						curr->parent->left = curr->right;
					}
					
					else
					{
						curr->parent->right = curr->right;
					}
				}
			}
			
			//Node has 0 children i.e. deleting a leaf
			else
			{
				//if child is left to the parent
				if(curr->data < curr->parent->data)
				{
					curr->parent->left = NULL;
				}
				
				//if child is right to the parent
				else
				{
					curr->parent->right = NULL;
				}
			}
				
		}
	
		//recursive function to count number of nodes of the sub tree
		int count(Node *curr)       
		{
			int ct = 0;				   //stores the number of nodes in the subtree
			if(curr == NULL)
				return 0;              //if it is leaf, then there are no nodes in this sub tree
				
			else
			{
				ct = count(curr->left) + count(curr->right) + 1;          //basically reaches a leaf and increments by 1 to represent that the leaf has been accounted for
				return ct;
			}	
		}
		
		//finds size of the tree 
		int size()
		{
			return count(root);           //returns the number of nodes in the tree
		}
		
		//function to print all node data x such that k1<=x<=k2 and also returns the number of nodes that contain such a data
		int rangeSearch(int k1,int k2)
		{
			rangeSearch2(k1,k2,root,0);
		}
		
		//recursive function to find data x s.t. k1 <= x <= k2 and returns the number of such nodes
		int rangeSearch2(int k1,int k2,Node *curr,int ct)        //variable ct stores the number of nodes
		{
			if(curr == NULL)                                     //such a node has no value to compare and the corresponding sub tree has no nodes to count
				return 0;
				
			rangeSearch2(k1,k2,curr->left,ct);                      //similar to the display2() function, since it traverses the entire tree
			if((curr->data >= k1) && (curr->data <= k2))
			{
				cout<<curr->data<<",";
				++ct;
			}
			rangeSearch2(k1,k2,curr->right,ct);
		}
		
		
		//function that returns the maximum value of 2 integers 
		int max(int a,int b)
		{
			if(a<b)
				return b;
				
			else
				return a;	
		}
		
		//recursive function that returns the height of the binary tree
		int height(Node *curr)
		{
			//base case: if node is NULL then corresponding tree has 0 height
			if(curr == NULL)
				return 0;
				
			//for a given sub-tree, check the heights of its left and right sub-trees and return the maximum	
			else
			{
				return max(height(curr->left),height(curr->right)) + 1;	
			}	
		}
		
		//displays the height
		int disp_height()
		{
			return height(root);
		}
		
};

int main()
{
	//variable declaration
	BST b1;
	//insertion of nodes into the tree
	b1.insert(41);
	b1.insert(45);
	b1.insert(31);
	b1.insert(11);
	b1.insert(33);
	b1.insert(14);
	b1.insert(49);
	b1.insert(43);
	b1.insert(50);
	b1.insert(21);
	
	//displays the tree
	b1.display();
	cout<<endl;
	b1.fancydisplay();
	
	//displays number of nodes present in the tree
	cout<<"Number of nodes: "<<b1.size()<<endl;
	cout<<endl;
	
	//displays the values of nodes lying between k1 and k2
	cout<<"Display in range:";
	b1.rangeSearch(30,48);
	
	cout<<endl<<endl;
	//displays height of the tree
	cout<<"Height: "<<b1.disp_height();
	return 0;
}