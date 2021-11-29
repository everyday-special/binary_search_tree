#include "table.h"

Table::Table()
/* Constructor for table class
 * Parameters: None
 * Return: None
 */
{
	root = nullptr;
	size = new int(0);
}



Table::~Table()
/* Destructor for table class
 * Parameters: None
 * Return: None
 */
{
	destroy(root);
	delete size;
	size = nullptr;
}



void Table::destroy(node *& root)
/* Recursive backend for destructor and deleting all nodes in the tree
 * Parameters: node *& root - current root of the tree. Passed by reference
 * Return: None
 */
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
/* Removes the website that matches the keyword from the tree.
 * Parameters: const char toDelete[] - cstring representing the keyword of the website to be removed from the tree
 * Return: bool - True if website was removed. False if not.
 */
{
	int old_size = *size;
	root = remove(root, toDelete);
	int new_size = *size;
	return (old_size != new_size);
}



bool Table::removeTopic(const char topic[])
/* Removes all websites that match a specified topic from the tree
 * Parameters: const char topic[] - cstring representing the topic to be removed from the tree
 * Return: bool - true if websites were removed, false if no websites were removed.
 */
{
	int old_size = *size;
	root = removeTopic(root, topic);
	int new_size = *size;
	return (old_size != new_size);
}



bool Table::insert(Website& newWebsite)
/* Adds a new website to the tree
 * Parameters: Website& newWebsite - website to be added. passed by reference
 * Return: bool - true if website was added, false if not.
 */
{
	int old_size = *size;
	root = insert(root, newWebsite);
	int new_size = *size;
	return (old_size != new_size);
}



bool Table::retrieve(const char keyword[], Website & retrieved)
/* Retrieves a specific website from the tree.
 * Parameters:
 * 	-const char keyword[] - cstring representing the keyword to retrieve
 * 	-Website & retrieved - stores the website data if there is a keyword match
 * Return: bool - true if there was a keyword match and data was retrieved, false if no
 */
{
	return retrieve(root, keyword, retrieved);
}



bool Table::retrieve(node * root, const char keyword[], Website & retrieved)
/* Recursive searches tree for a keyword match. If there is a match, stores the data in retrieved
 * Parameters:
 * 	-node * root - current node
 * 	-const char keyword[] - keyword of website to retrieve
 * 	-Website & retrieved - stores website data in case of keyword match. Passed by reference
 * Return: bool - true if keyword match and data is retrieved, false if not
 */
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
/* Recursive backend for removing a node
 * Parameters:
 * 	- node *& root - Pointer to current node in tree. Passed by reference.
 * 	- const char toDelete[] - cstring containing keyword of website to be removed from the tree
 * Return: node * - pointer to node that should be at this location after a node is removed
 */
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
/* Recursive backend for removing all nodes of a topic
 * Parameters:
 *      - node *& root - Pointer to current node in tree. Passed by reference.
 *      - const char topic[] - cstring containing topic to be removed from the tree
 * Return: node * - pointer to node that should be at this location after topic is removed
 */
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
/* Deletes the given node and returns the node that should be at that location (next order)
 * Parameters: node *& toDelete - pointer to node that is to be deleted
 * Return: node * - pointer to node that should be at the location of the old node
 */
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
/* Recursive backend for inserting a new website/node into the tree
 * Parameters:
 * 	node *& root - current node in the tree. Passed by reference
 * 	Website& newWebsite - website data to be added to the tree. Passed by reference
 * Return: node * - node that should be at that location after insertion operation.
 */
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
/* Determines and performs the type of rotation that needs to be done to maintain balance at a given node
 * Parameters: node *& root - node that needs to be rotated. Passed by reference
 * Return: node * - pointer to node that should be at that location after the rotation operation
 */
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
/* Performs single left rotation
 * Parameters: node *& root -  pointer to node that needs to be rotated
 * Return: node * - pointer to node that should be at that location after rotation
 */
{
	node * r = root->right;
	root->right = r->left;
	r->left = root;
	return r;
}



node * Table::singleRight(node *& root)
/* Performs single right rotation
 * Parameters: node *& root -  pointer to node that needs to be rotated
 * Return: node * - pointer to node that should be at that location after rotation
 */
{
	node * l = root->left;
	root->left = l->right;
	l->right = root;
	return l;
}


node * Table::doubleLeft(node *& root)
/* Performs double left rotation
 * Parameters: node *& root -  pointer to node that needs to be rotated
 * Return: node * - pointer to node that should be at that location after rotation
 */
{
	node * r = singleRight(root->right);
	root->right = r->left;
	r->left = root;
	return r;
}



node * Table::doubleRight(node *& root)
/* Performs double right rotation
 * Parameters: node *& root -  pointer to node that needs to be rotated
 * Return: node * - pointer to node that should be at that location after rotation
 */
{
	node * l = singleLeft(root->left);
	root->left = l->right;
	l->right = root;
	return l;
}



int Table::getHeight()
/* Gets the height of the entire tree
 * Parameters: Nonde
 * Return: int - height of the tree (maximum length from root to leaf)
 */
{
	return getHeight(root);
}



int Table::getSize()
/* Returns the size/amount of nodes in the entire tree
 * Parameters: None
 * Return: int - size of the tree (number of nodes in the tree)
 */
{
	return *size;
}



int Table::getHeight(node * root)
/* Gets the height of a node
 * Paremeters: node * root - node to get the height of
 * Return: int - height of the node in the tree
 */
{
	if (!root)
		return 0;
	return 1 + std::max(getHeight(root->left), getHeight(root->right));
}



bool Table::display()
/* Displays all the website data in the tree in alphabetical order
 * Parameters: None
 * Return: bool - true if tree is non-empty and data was printed, false if tree is empty
 */
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
/* recursively displays data at root and its subtree
 * Parameters: node * root - root of subtree to print
 * Return: None
 */
{
	if (root)
	{
		display(root->left);
		std::cout << *root << std::endl;
		display(root->right);
	}
}



bool Table::saveToFile(const char filename[])
/* Saves data in tree to file
 * Parameters: const char filename[] - name of file to save data to
 * Return: bool - true if save was successful, false if not
 */
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
/* Saves data in subtree at root to file
 * Parameters:
 * 	- node * root - root of subtree to save to file
 * 	- std::ofstream & outFile - file stream. Passed by reference
 * Return: bool - true if data was saved to file, false if not
 */
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
/* Loads data from file 'filename' and adds it to the tree
 * Paraeters: const char filename[] - name of file to load data from
 * Return: bool - true if data was successfully loaded, false if not
 */
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

