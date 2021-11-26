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



bool Table::remove(const char toDelete[])
{
	int old_size = *size;
	root = remove(root, toDelete);
	int new_size = *size;
	return (old_size != new_size);
}



bool Table::removeTopic(const char topic[])
{
	int old_size = *size;
	root = removeTopic(root, topic);
	int new_size = *size;
	return (old_size != new_size);
}



bool Table::insert(Website& newWebsite)
{
	int old_size = *size;
	root = insert(root, newWebsite);
	int new_size = *size;
	return (old_size != new_size);
}



node * Table::remove(node *& root, const char toDelete[])
{
	if (!root)
		return root;
	char rootKeyword[MAX_SIZE];
	(*(root->data)).getKeyword(rootKeyword);
	int result = strcmp(toDelete, rootKeyword);
	if (result == 0)
	{
		(*size)--;
		return deleteNode(root);
	}
	else if (result > 0)
		root->right = remove(root->right, toDelete);
	else
		root->left = remove(root->left, toDelete);
	if (getHeight(root->left) - getHeight(root->right) > 1 || getHeight(root->left) - getHeight(root->right) < -1)
                root = rotate(root);
        return root;
}



node * Table::removeTopic(node *& root, const char topic[])
{
        if (!root)
                return root;
	root->left = removeTopic(root->left, topic);
        root->right = removeTopic(root->right, topic);
        char rootTopic[MAX_SIZE];
        (*(root->data)).getTopic(rootTopic);
        int result = strcmp(topic, rootTopic);
        if (result == 0)
        {
                (*size)--;
                return deleteNode(root);
        }
        /*if (getHeight(root->left) - getHeight(root->right) > 1 || getHeight(root->left) - getHeight(root->right) < -1)
                root = rotate(root);*/
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



node * Table::insert(node *& root, Website& newWebsite)
{
	if (!root)
	{
		node * newNode = new node(newWebsite);
		(*size)++;
		return newNode;
	}
	char rootKeyword[MAX_SIZE];
	char newKeyword[MAX_SIZE];
	(*(root->data)).getKeyword(rootKeyword);
	newWebsite.getKeyword(newKeyword);
	int result = strcmp(newKeyword, rootKeyword);
	if (result == 0)
	return root;
	else if (result > 0)
		root->right = insert(root->right, newWebsite);
	else
		root->left = insert(root->left, newWebsite);
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
		std::cout << *root << std::endl;
		display(root->right);
	}
}
