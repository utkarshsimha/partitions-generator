#include<iostream>
//#include<set>
//#include<ctime>
//#include<vector>
//#include<stdlib.h>
//#include<iomanip>
//#include<climits>
//#include<memory>
using namespace std;
class List;
int num;
int dim;
int * p[100000];
int res[100];
int * possible[100000];
long double sum[100];
int *a;
int *d;
//vector<int*> possibleNodes;
void addpart(int, int, int, shared_ptr<List>);
bool ispossible(int**, int *, int);
bool checkPartition(int**, int *, int);
bool compare(int *, int *);
int *copyNode(int *);
int *node(int);
void printPartition(int **, int );
void printNode(int *);
void nplus(int **, int, int);
