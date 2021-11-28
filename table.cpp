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



bool Table::retrieve(const char keyword[], Website & retrieved)
{
	return retrieve(root, keyword, retrieved);
}



bool Table::retrieve(node * root, const char keyword[], Website & retrieved)
{
	if (!root)
		return false;
	char rootKeyword[MAX_SIZE];
	(*(root->data)).getKeyword(rootKeyword);
	int result = strcmp(keyword, rootKeyword);
	if (result == 0)
	{
		retrieved = *(root->data);
		return true;
	}
	else if (result > 0)
		return retrieve(root->right, keyword, retrieved);
	else
		return retrieve(root->left, keyword, retrieved);
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



int Table::getHeight()
{
	return getHeight(root);
}



int Table::getHeight(node * root)
{
	if (!root)
		return 0;
	return 1 + std::max(getHeight(root->left), getHeight(root->right));
}



bool Table::display()
{
	if (*size > 0)
	{
		display(root);
		return true;
	}
	else
		return false;
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



bool Table::saveToFile(const char filename[])
{
	bool ret;
	std::ofstream outFile;

	outFile.open(filename);
	if (!outFile)
		return false;

	ret = saveToFile(root, outFile);
	outFile.close();
	return ret;
}



bool Table::saveToFile(node * root, std::ofstream & outFile)
{
	if (!root)
		return false;

	// Save left and right children
	saveToFile(root->left, outFile);
	saveToFile(root->right, outFile);

	// Save current node data
	char temp[MAX_SIZE];
	root->data->getKeyword(temp);
	outFile << temp << ';';
	root->data->getTopic(temp);
	outFile << temp << ';';
	root->data->getAddress(temp);
	outFile << temp << ';';
	root->data->getSummary(temp);
	outFile << temp << ';';
	root->data->getReview(temp);
	outFile << temp << ';';
	outFile << root->data->getRating() << std::endl;

	return true;
}



bool Table::loadFromFile(const char filename[])
{
	char tempKeyword[MAX_SIZE]; // Stores keyword data from file
	char tempTopic[MAX_SIZE]; // Stores topic data from file
        char tempAddress[MAX_SIZE]; // stores address data from file
        char tempSummary[MAX_SIZE]; // stores summary data from file
        char tempReview[MAX_SIZE]; // stores review data from file
        int tempRating; // stores rating data from file
        std::ifstream inFile; // file stream

        inFile.open(filename);
        if (!inFile)
                return false;

        inFile.get(tempKeyword, MAX_SIZE, ';');
        while (!inFile.eof())
        {
                inFile.get();
		inFile.get(tempTopic, MAX_SIZE, ';');
		inFile.get();
                inFile.get(tempAddress, MAX_SIZE, ';');
                inFile.get();
                inFile.get(tempSummary, MAX_SIZE, ';');
                inFile.get();
                inFile.get(tempReview, MAX_SIZE, ';');
                inFile.get();
                inFile >> tempRating;
                inFile.ignore(MAX_SIZE, '\n');

                Website newWebsite(tempTopic, tempKeyword, tempAddress, tempSummary, tempReview, tempRating);
                insert(newWebsite);

                inFile.get(tempKeyword, MAX_SIZE, ';');
        }
        inFile.close();
        return true;
}

