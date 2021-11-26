#include "table.h"


Website makeWebsite()
{
        char newTopic[MAX_SIZE];
        char newAddress[MAX_SIZE];
        char newSummary[MAX_SIZE];
        char newReview[MAX_SIZE];
        char newKeyword[MAX_SIZE];
        int newRating;

        std::cout << "Please enter the website's topic: ";
        getString(newTopic);
        std::cout << "Please enter the website's keyword: ";
        getString(newKeyword);
        std::cout << "Please enter the website's address: ";
        getString(newAddress);
        std::cout << "Please enter a summary of the website: ";
        getString(newSummary);
        std::cout << "Please enter your review of the website: ";
        getString(newReview);
        std::cout << "Please enter a rating of the website from 1 to 5: ";
        newRating = getInt();
        while (newRating < 1 || newRating > 5)
        {
                std::cout << "Please enter a rating from 1 to 5: ";
                newRating = getInt();
        }
        return Website(newTopic, newKeyword, newAddress, newSummary, newReview, newRating);
}



int main()
{
	Website in;
	char toRemove[MAX_SIZE];
	char ch = 'a';
	Table table = Table();
	std::cout << "Inserting!!" << std::endl;
	while (ch != 'q')
	{
		in = makeWebsite();
		if (table.insert(in))
			std::cout << "Added!" << std::endl;
		else
			std::cout << "Not Added!" << std::endl;
		std::cout << "Press 'q' to quit: ";
		ch = getChar();
	}
	ch = 'a';
	std::cout << "Remove all by topic: " << std::endl;
	getString(toRemove);
	if (table.removeTopic(toRemove))
		std::cout << "Removed!" << std::endl;
	else
		std::cout << "Not removed!" << std::endl;
	/*while (ch != 'q')
        {
		getString(toRemove);
                if (table.remove(toRemove))
			std::cout << "Removed!" << std::endl;
		else
			std::cout << "Not Removed!" << std::endl;
                std::cout << "Press 'q' to quit: ";
                ch = getChar();
        }*/
	table.display();
	return 0;
}



