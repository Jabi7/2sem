#include<iostream>      //library header

using namespace std;    //namespace

void prt(int a[], int &p,int l, int h ){

	int k=a[p],s,o,i;

	
	for (i = h-1; i >= l; i--)
	{
		if(a[i]>a[p]){
			s=a[i];
			a[i]=a[p];
			a[p]=s;
			p=i;
		}else{
			if(a[i-1]>a[p]&&i-1>=l&&i!=p){

				o=a[i-1];
				a[i-1]=a[i];
				a[i]=o;
				i=h-1;
			}

		} 

	


	}

	
}

void qs(int a[],int l,int h){
	int p=h;
	if(l<h){
	prt(a,p,l,h);

	qs(a,l,p-1);
	qs(a,p+1,h);
}
	
}


//driver function
int main()
{
	int a[20],n;
	cout<<"enter size : ";
	cin>>n;
	for (int i = 0; i < n; i++)
	{
		cin>>a[i];/* code */
	}

	qs(a,0,n-1);

	cout<<"\n\n";
	for (int i = 0; i < n; i++)
	{
		cout<<a[i];/* code */
	}
	return 0;
}