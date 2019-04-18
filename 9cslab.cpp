#include<iostream>

using namespace std;

class BinaryHeap
{
	public:
		//Pointer to point to element in the array
		int *hArr;
		//Maximum possible size of the array
		int msize;
		//Current size of the array
		int csize;
		
		//constructor implementation
		BinaryHeap(int max_size)	
		{
			hArr = new int[msize];
			msize = max_size;   
			csize = -1;
		}
		
		//function that swaps 2 integer values
		void swap(int &a, int &b)
		{
			//use of temporary variable to initiate swap
			int temp = a;
			a = b;
			b = temp;
		}
		
		//returns index of parent of node
		int parent(int i)
		{
			return (i-1)/2;
		}
		
		//returns index of left child of node
		int left(int i)
		{
			return (i*2)+1;
		}
		
		//returns index of right child of node
		int right(int i)
		{
			return (i*2)+2;
		}
		
		//returns the least element of the binary heap (min heap)
		int getMin()
		{
			return hArr[0];
		}
		
		//function to insert values into the binary heap
		void insert(int value)
		{
			//Base case, for heap overflow
			if(csize == msize)
				return;
				
			hArr[++csize] = value;    //inserts value at the end of the array
			
			//Check it for all hierarchy with the loop (for min heap)
			int i = csize;
			while((i>-1) && (hArr[i] < hArr[parent(i)]))
			{
				swap(hArr[i],hArr[parent(i)]);
				//to compare parent of node (A) with its won parent (A's parent's parent)
				i = parent(i);
			}
		}
		
		//function to implement heapify algorithm using recursion
 		void min_heapify(int i)
		{
			//base case
			if(hArr[parent(i)] < hArr[i])
				return;
				
			//compare with left and right
			else if(hArr[left(i)] < hArr[right(i)])
			{
				//replace with minimum child and heapify
				swap(hArr[i],hArr[left(i)]);
				min_heapify(left(i));
			}
			
			else
			{
				//replace with minimum child and heapify
				swap(hArr[i],hArr[right(i)]);
				min_heapify(right(i));
			}
		}
		
		
		//displays the binary heap in the form of array
		void display()
		{
			for(int i=0; i<=csize; i++)
				cout<<hArr[i]<<",";
		}
		
		//function that extracts minimum node i.e., the root and removes it from the heap
		//heapifies the remaining heap to maintain condition of min heap
		int extract_min()
		{
			//Base case for empty heap
			if(csize == -1)
				return 0;
				
			//Base case for heap with 1 element
			if(csize == 0)
			{
				return hArr[csize--];	             //returns the 1 element and decreases size of the heap to -1 (empty case)
			}
			
			int min = hArr[0];           //stores root value aka minimum value
			//place last element in place of root to maintain condition of complete binary tree
			hArr[0] = hArr[csize--];
			min_heapify(0);
			
			return min;	
		}
		
		//function that decreases value of a node and subsequently changes the heap to maintain the condition of min heap
		void decreaseKey(int i, int new_val)
		{
			//new_val is less than the current value
			hArr[i] = new_val;
			
			//Loop for correcting heap for property 2 (condition for min heap) till i=0 or when there's no violation
			while((i>-1) && (hArr[i] < hArr[parent(i)]))
			{
				swap(hArr[i],hArr[parent(i)]);
				//compare the old parent with its own parent to heapify with
				i = parent(i);  
			}
		}
		
		//Deletes elements indexed at i
		void deleteKeyAt(int i)
		{
			//decreases the node value to a value that is lesser than the root
			decreaseKey(i,hArr[0]-1);
			
			//call extract_min() to remove this minimum element
			extract_min();           //this essentially deletes the node
		}
};

//driver function
int main()
{
	BinaryHeap bh1(20);
    for(int i = 10; i >0 ; i--)
	{
        cout << "Inserting " << i << endl;
        bh1.insert(i);
        bh1.display();
    }
    
    cout<<endl;
    cout<<endl<<"After extracting minimum: \n";
    cout<<"Minimum element: "<<bh1.extract_min()<<endl;
    bh1.display();
    cout<<endl;
    cout<<"\nAfter deleting at index 3: \n";
    bh1.deleteKeyAt(3);
    bh1.display();
    cout << endl;
    
    return 0;
}