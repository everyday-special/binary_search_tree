#include "table.h"

int main()
{
	int in = 1;
	Table table = Table();
	while (in >= 0)
	{
		table.insert(in);
		std::cout << "Please enter an integer to add: ";
		in = getInt();
	}
	in = 1;
	while (in >= 0)
        {
                table.remove(in);
                std::cout << "Please enter an integer to remove: ";
                in = getInt();
        }
	table.display();
	return 0;
}
