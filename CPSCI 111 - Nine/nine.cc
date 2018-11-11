/************************************************************************
    File: nine.cc
    Author: Zach Kleinbaum
    Date: 11/7/16
    Assignment:  Lab 6 (Nine Short Problems on Trees)

    Implementation of various tree methods

************************************************************************/
#include "nine.h"
// nine.cc
// Alistair Campbell

// Implementation for "nine functions on trees"

size_t count_nodes(node *tree)
{
	// Return the number of nodes in the tree.
	// Use recursion to determine how many nodes are in left and right tree.

	if(!tree)
		return 0;
	else
		return count_nodes(tree -> left) + count_nodes(tree -> right) + 1;
}


size_t count_branches(node *tree)
{
	// Return the number of branches in the tree.
	// Branches is equal to the number of nodes minue one.

	if (!tree)
		return 0;
	else
		return (count_nodes(tree) - 1);
}


size_t count_leaves(node *tree)
{
	// Return the number of leaves in a tree
	// Use recursion to find where the leads are, and add that to the count.

	// Base case
	if (!tree)
		return 0;

	// A tree with no children is a leaf/
	if (!tree -> left and !tree -> right)
		return 1;
	else
		return count_leaves(tree -> right) + count_leaves(tree -> left);
}


double branching_factor(node *tree)
{
	// Return the branching factor by dividing braches by (nodes - leaves)

	if (count_branches(tree) == 0)
		return 0.0;
	else
		return ((double)count_branches(tree)) / (((double)count_nodes(tree))
			   - (double)count_leaves(tree));
}


size_t height(node *tree)
{
	// Return the height of the tree
	// Check to see if left or right height is larger

	if (!tree)
		return 0;

	// Establish variables for left and right heights.
	int lh = height(tree -> left);
	int rh = height(tree -> right);
	return (lh >= rh ? lh:rh) + 1;
}


void depth_traverse(node *tree, Direction direction,
					Order order, void (*visit)(node *tree))
{	// Traverse a tree in six different ways.
	// Use if statements to check direction and order.
	// Function call location depends on order.

	if (tree)
	{
		// Left to Right
		if (direction == LEFTTORIGHT)
		{
			if (order == PREORDER)
			{
				visit(tree);
				depth_traverse(tree -> left, direction, order, visit);
				depth_traverse(tree -> right, direction, order, visit);
			}
			if (order == INORDER)
			{
				depth_traverse(tree -> left, direction, order, visit);
				visit(tree);
				depth_traverse(tree -> right, direction, order, visit);
			}
			if (order == POSTORDER)
			{
				depth_traverse(tree -> left, direction, order, visit);
				depth_traverse(tree -> right, direction, order, visit);
				visit(tree);
			}
		}
		// Right to Left
		if (direction == RIGHTTOLEFT)
		{
			if (order == PREORDER)
			{
				visit(tree);
				depth_traverse(tree -> right, direction, order, visit);
				depth_traverse(tree -> left, direction, order, visit);
			}
			if (order == INORDER)
			{
				depth_traverse(tree -> right, direction, order, visit);
				visit(tree);
				depth_traverse(tree -> left, direction, order, visit);
			}
			if (order == POSTORDER)
			{
				depth_traverse(tree -> right, direction, order, visit);
				depth_traverse(tree -> left, direction, order, visit);
				visit(tree);
			}
		}
	}
}


bool is_full(node *tree)
{
	// Return true if the tree is full. False if it is not
	// Check that every node has two or zero children.

	// Base case.
	if(!tree)
		return false;

	if (!tree -> right and !tree -> left)
	{
		return true;
	}
	else
	{
		if (branching_factor(tree) == 2)
			return true;
		else
			return false;
	}
}


bool is_equal(node *tree1, node *tree2)
{
	// Return true if the trees are equal, false if they are not.
	// Check to see if both or one of the trees is empty.

	if (!tree1 and !tree2)
	{
		return true;
	}
	else if (!tree1 or !tree2)
	{
		return false;
	}
	else if (tree1 -> data == tree2 -> data)
	{
		return is_equal(tree1 -> left, tree2 -> right) || is_equal(tree1 ->
			   right, tree2 -> right);
	}
	else
		return false;
}


bool is_balanced(node *tree)
{
	// Return true if the tree is balanced.
	// Check to see if height is within a range of one on both sides of root.

	if (!tree)
	{
		return true;
	}
	else
	{
		size_t heightLeft = height(tree -> left);
		size_t heightRight = height(tree -> right);
		if(heightLeft == heightRight or heightLeft == heightRight + 1 or
			heightLeft == heightRight - 1)
			return is_balanced(tree -> left) and is_balanced(tree -> right);
		else
			return false;
	}
}
