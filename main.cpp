#include "table.h"

int main()
{
	int in = 1;
	Table table = Table();
	std::cout << "Please enter an integer to add: ";
	in = getInt();
	while (in >= 0)
	{
		table.insert(in);
		std::cout << "Please enter an integer to add: ";
		in = getInt();
	}
	std::cout << "please enter an integer to remove: ";
	in = getInt();
	while (in >= 0)
        {
                table.remove(in);
                std::cout << "Please enter an integer to remove: ";
                in = getInt();
        }
	table.display();
	return 0;
}
