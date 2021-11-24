#include "table.h"

Table::Table()
{
	root = nullptr;
	size = new int(0);
}



Table::~Table()
{
	destroy(root);
	delete size;
	size = nullptr;
}



void Table::destroy(node *& root)
{
	if (root)
	{
		destroy(root->left);
		destroy(root->right);
	}
	delete root;
	root = nullptr;
}



bool Table::remove(const int& val)
{
	int old_size = *size;
	root = remove(root, val);
	int new_size = *size;
	return (old_size != new_size);
}



bool Table::insert(const int& val)
{
	int old_size = *size;
	root = insert(root, val);
	int new_size = *size;
	return (old_size != new_size);
}



node * Table::remove(node *& root, const int& val)
{
	if (!root)
		return root;
	else if (*(root->data) == val)
		return deleteNode(root);
	else if (*(root->data) < val)
		root->right = remove(root->right, val);
	else
		root->left = remove(root->left, val);
	if (getHeight(root->left) - getHeight(root->right) > 1 || getHeight(root->left) - getHeight(root->right) < -1)
                root = rotate(root);
        return root;
}



node * Table::deleteNode(node *& toDelete)
{
	// If toDelete is a leaf...
	if (!(toDelete->left) && !(toDelete->right))
	{
		delete toDelete;
		toDelete = nullptr;
		return toDelete;
	}
	// If toDelete has only left branch
	else if (!(toDelete->right))
	{
		node * temp = toDelete->left;
		delete toDelete;
		toDelete = nullptr;
		return temp;
	}
	// If toDelete has only right branch
	else if (!(toDelete->left))
	{
		node * temp = toDelete->right;
		delete toDelete;
		toDelete = nullptr;
		return temp;
	}
	// If toDelete has both branches
	else
	{
		node * prev = nullptr;
		node * curr = toDelete->right;
		if (!(curr->left))
		{
			curr->left = toDelete->left;
			delete toDelete;
			toDelete = nullptr;
			return curr;
		}
		else
		{
			while (curr->left)
			{
				prev = curr;
				curr = curr->left;
			}
			prev->left = curr->right;
			curr->left = toDelete->left;
			curr->right = toDelete->right;
			delete toDelete;
			toDelete = nullptr;
			return curr;
		}
	}
}



node * Table::insert(node *& root, const int& val)
{
	if (!root)
	{
		node * newNode = new node(val);
		(*size)++;
		return newNode;
	}
	else if (*(root->data) == val)
		return root;
	else if (*(root->data) < val)
		root->right = insert(root->right, val);
	else
		root->left = insert(root->left, val);
	if (getHeight(root->left) - getHeight(root->right) > 1 || getHeight(root->left) - getHeight(root->right) < -1)
		root = rotate(root);
	return root;
}



node * Table::rotate(node *& root)
{
	node * l = root->left;
	node * r = root->right;
	if (getHeight(r) > getHeight(l))
	{
		if (getHeight(r->left) > getHeight(r->right))
			return doubleLeft(root);
		else
			return singleLeft(root);
	}
	else
	{
		if (getHeight(l->right) > getHeight(l->left))
			return doubleRight(root);
		else
			return singleRight(root);
	}
}



node * Table::singleLeft(node *& root)
{
	node * r = root->right;
	root->right = r->left;
	r->left = root;
	return r;
}



node * Table::singleRight(node *& root)
{
	node * l = root->left;
	root->left = l->right;
	l->right = root;
	return l;
}


node * Table::doubleLeft(node *& root)
{
	node * r = singleRight(root->right);
	root->right = r->left;
	r->left = root;
	return r;
}



node * Table::doubleRight(node *& root)
{
	node * l = singleLeft(root->left);
	root->left = l->right;
	l->right = root;
	return l;
}



int Table::getHeight(node * root)
{
	if (!root)
		return 0;
	return 1 + std::max(getHeight(root->left), getHeight(root->right));
}



void Table::display()
{
	display(root);
}



void Table::display(node * root)
{
	if (root)
	{
		display(root->left);
		std::cout << "Level " << getHeight(root) << ": " << *root << std::endl;
		display(root->right);
	}
}
