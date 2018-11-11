#include "nine.h"
#include <iostream>

using namespace std;

int main()
{
	node* testtree = new node(12, new node(55, new node(85, new node(61, NULL, NULL), new node(13,NULL,NULL)), NULL), new node(23, NULL, new node(88, NULL, NULL)));
	node* testtree2 = new node(5, new node(4, NULL, NULL), NULL);//new node(8,NULL, NULL));

	cout << "Number of nodes = " << count_nodes(testtree) << endl;
	cout << "Number of Branches = " << count_branches(testtree) << endl;
	cout << "Count leaves = " << count_leaves(testtree) << endl;
	cout << "Branching Factor = " << branching_factor(testtree) << endl;
	cout << "Height = " << height(testtree) << endl;
	cout << "is it full ? " << is_full(testtree) << endl;
	cout << " are trees equal? " << is_equal(testtree, testtree2) << endl;
	cout << "are tree balanced " << is_balanced(testtree) << endl;



}
