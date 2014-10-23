#include"head4.h"

class List 
{
	private:
	//A struct object to represent the node
		struct lnode {
			int * item;
			struct lnode * next;
		};
		struct lnode * first;
	public:
	List () //Constructor
	{
		first = NULL;
	}
	~List () //Destructor
	{
		struct lnode *q=first;
		struct lnode *lnext;
		while(q!=NULL)
		{
			lnext = q->next;
			delete [] q->item;
			delete q;
			q = lnext;
		}
	}
	void clear_list()
	{
		struct lnode *q=first;
		struct lnode *lnext;
		while(q!=NULL)
		{
			lnext = q->next;
			delete q;
			q = lnext;
		}
	}

	void insert_tail(int *x)
	{
		struct lnode *temp;
		struct lnode *q = first;
		//temp = (struct lnode *) malloc(sizeof(struct lnode));
		temp = new lnode;
		temp->item = x;
		temp->next = NULL;
		if(q!=NULL)
		{
			while(q->next!=NULL)
			{	
				q=q->next;
			}
			q->next = temp;
		}
		else
		{
			first = temp;
		}
	}
	
	int delete_node(int *x)
	{
		struct lnode *qr;
		struct lnode *prev;
		qr = first;
		prev = NULL;
		while((qr!=NULL)&&!compare(qr->item,x))
		{
			prev = qr;
			qr = qr->next;
		}
		if(qr!=NULL)
		{
			if(prev == NULL)
			{
				first = qr->next;
			}
			else
				prev->next = qr->next;
			delete [] qr->item;
			delete qr;
			return 1;
		}
		else
			return 0;
	}
	
	int listSize()
	{
		struct lnode *q = first;
		int i;
		while(q!=NULL)
		{
			i++;
			q=q->next;
		}
		return i;
	}
};



int main(int argc, char *argv[])
{
	cout << "Enter dimension" << endl;
	cin >> dim;
	//dim = 4;
	cout << "Enter number to generate partitions" << endl;
	cin >> num;
	//num = 20;

	//Initializing the array
	p[0] = node(dim);
	p[1] = node(dim);
	p[2] = node(dim);
	possible[0] = node(dim);
	possible[1] = node(dim);

	//Initializing possible with initial possible nodes
	int l=0; //Iterator
	for(int j=dim-1;j>=0;j--)
	{
		int *x = node(dim);
		x[j] = 1;
		delete [] possible[l];
		possible[l] = x;
		l++;
	}

	//Creating List object
	shared_ptr<List> initialList(new List());

	//Inserting 0 node
	initialList->insert_tail(node(dim));

	//pointer initialization
	d = NULL;
	a = NULL;

	//Initilization of results
	res[0] = 1;
	res[1] = 1;
	sum[0] = 0;
	sum[1] = 1;

	int start_s = clock();
	//The main call
	addpart(1,0,dim-1,initialList);
	int stop_s = clock();

	//Printing time
	cout << "Time : " << (stop_s - start_s)/(double)(CLOCKS_PER_SEC)*1000 << endl;

	//Deleting pointer a
	if(a!=NULL)
	{
		delete [] a;
	}

	//Deleting pointer d
	if(d!=NULL)
	{
		delete [] d;
	}

	//Result
	/*cout << "Result : " << endl;
	for(int j=0;j<=num;j++)
	{
		cout << "res["<<j<<"]" << ": " << res[j] << endl;
	}*/

	//Sum
	cout << "Sum : " << endl;

  for(int j=0;j<2000;j++)
	{
		if(j<=num)
		{
			cout << fixed << setprecision(0) << "sum["<<j<<"]" << ": " << sum[j] << endl;
		}

		//Deleting objects from the arrays
		if(p[j]!=NULL)
		{
			delete [] p[j];
		}

		if(possible[j]!=NULL)
		{
			delete [] possible[j];
		}
	}

	//Deleting List instance
  //delete initialList;
	
}

inline int * node(int dim)
{
	//Creating a new 0 node
	int *t = new int[dim];
	for(int j=0;j<dim;j++)
	{
		t[j] = 0;
	}
	return t;
}

void addpart(int n, int f, int t, shared_ptr<List> nodeList)
{

	//Contianer for deleted nodes
	vector<int *> dNodes(100);

	int i,j,it;
	int s=0;
	int ns =0;
	for(i=f;i<=t;i++)
	{
		a = copyNode(possible[i]);
		delete [] p[n+1];
		p[n+1] = a; //Transfering possible[i] to p[n+1]
		a = NULL;
		ns = 0;
		for(int l=dim-1;l>=0;l--)//Decrementing each coordinate
		{
			d = copyNode(possible[i]);
			d[l]--;
			if(nodeList->delete_node(d))
			{
				dNodes[ns] = d;
				ns++;
			}
			else
			{
				delete [] d;
			}
		}
	nodeList->insert_tail(copyNode(possible[i]));
	res[n+1]++;
	sum[n+1] += nodeList->listSize();
		if(n==num-1)
		{
			//Partition has been generated
			for(it=0;it<ns;it++)
			{
				nodeList->insert_tail(copyNode(dNodes[it]));
			}
			nodeList->delete_node(possible[i]);
			continue;
		}
		for(j=dim-1;j>=0;j--)//Increment each coordinate
		{
			a = copyNode(possible[i]);
			a[j]++;
			if(ispossible(p, a, n+1))//Check if node is possible
			{
				s++;
				delete [] possible[s+t];
				possible[s+t] = a;//Add to possible
				a = NULL;
			}
			else
			{
				delete []a;
			}
		}
		addpart(n+1, i+1, s+t, nodeList);//Recursive call
		s = 0;
		for(it=0;it<ns;it++)
		{
			nodeList->insert_tail(copyNode(dNodes[it]));
		}
		nodeList->delete_node(possible[i]);
		dNodes.clear();
	}
}

//To check if node a can be inserted
bool ispossible(int**p, int *a, int k)
{
	for(int j=dim-1;j>=0;j--)//Decrement each coordinate
	{
		int *b = copyNode(a);
			if(--b[j]>=0 && !checkPartition(p,b,k))//Check if node is positive and not present in partition
			{
				delete [] b;
				return false;
			}
			delete [] b;
	}
	//delete [] b;
	return true;
}

//To check if node b is present in partition
bool checkPartition(int**p, int *b, int k)
{
	for(int j=1;j<=k;j++)
		if(compare(p[j],b))
			return true;
	return false;
}

//Comparing two nodes
bool compare(int *a, int *b)
{
	int j=0;
	while(j<dim)
	{
		if(a[j] != b[j])
			return false;
		j++;
	}
	return true;
}

//Copying a node and returning a new pointer
inline int * copyNode(int *a)
{
	int *b = node(dim);
	for(int j=0;j<dim;j++)
		b[j] = a[j];
	return b;
}

void printPartition(int **p, int k)
{
	cout << "---------" << endl;
	for(int j=1;j<=k;j++)
	{
		printNode(p[j]);
	}
	cout << "---------" << endl;
}

void printNode(int *a)
{
	cout << "{ ";
	for(int j=0;j<dim;j++)
	{
		cout << a[j] <<" ";
	}
	cout << "}" << endl;
}

