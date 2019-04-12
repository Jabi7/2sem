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
		
		//function that replaces the node of parent at parent
		void replace_At_Parent(Node *a, Node *b)                   //replaces node 'a' with node 'b' and removes node 'a'
		{
			Node *temp = a->parent;      //temporary variable to store parent of node 'a'
			//checks if node 'a' is left child
			if(a->data < a->parent->data)
			{
				//replace
				a->parent->left = b;                //forward link
				if(b->data < b->parent->data)
				{
					b->parent->left = NULL;
					b->parent = temp;	
				}
				
				else
				{
					b->parent->right = NULL;
					b->parent = temp;               //backward link
				}
			}
			
			else
			{
				//replace
				a->parent->right = b;               //forward link
				if(b->data < b->parent->data)
				{
					b->parent->left = NULL;
					b->parent = temp;	
				}
				
				else
				{
					b->parent->right = NULL;
					b->parent = temp;               //backward link
				}
				
			}
		}
		
		//function to swap values using function replace_At_Parent()
		void swap(int val1, int val2)
		{
			Node *a = search2(root,val1);          //'a' becomes node corresponding to the value val1
			Node *b = search2(root,val2);          //'b' becomes node corresponding to the value val2
			replace_At_Parent(a,b);
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
};

//driver function
int main()
{
	BST b1;
	//insertion of nodes into the tree
	b1.insert(41);
	b1.insert(50);
	b1.insert(32);
	b1.insert(74);
	b1.insert(12);
	b1.insert(20);
	b1.insert(71);
	b1.insert(18);
	b1.insert(26);
	b1.insert(81);
	b1.insert(79);
	b1.insert(84);
	b1.insert(48);
	
	//displaying the tree
	b1.display();
	cout<<endl;
	b1.fancydisplay();
	b1.deleteNode(41);
	cout<<endl<<"After deleting:\n";
	b1.fancydisplay();
	b1.display();
	
	//return
	return 0;
}