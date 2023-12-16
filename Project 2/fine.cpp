#include <iostream>
#include <string>

using namespace std;
int main()
{
	cout.setf(ios::fixed);
	cout.precision(3);

	string identification;
	string location;
	double value;
	double fine;

	//Gathering paramaters for the program to rund
	
	cout << "Identification: ";
	getline(cin, identification);

	cout << "Overstated amount (in millions): ";
	cin >> value;
	cin.ignore(10000, '\n');	

	cout << "Location: ";
	getline(cin, location);

	cout << "---\n";

	/* return 0; will tell the program to exit and
	to stop running the rest of the program */

	if (identification == "")
	{
		cout << "You must enter a property identification.\n";
		return 0;
	}

	if (!(value > 0))
	{
		cout << "The overstated amount must be positive.\n";
		return 0;
	}

	if (location == "")
	{
		cout << "You must enter a location.\n";
		return 0;
	}

	//Program continues after previous if statements are false
	//Next if/else statements calculate variable fine

	if (value <= 60.0)
	{
		fine = 0.1111 * value;
	}
	else if (value <= 150.0)
	{
		if (location == "florida" || location == "new york")
		{
			fine = (60.0 * 0.1111) + ((value - 60.0) * 0.18);
		}
		else
		{
			fine = (60.0 * 0.1111) + ((value - 60.0) * 0.153);
		}
	}
	else
	{
		if (location == "florida" || location == "new york")
		{
			fine = (60.0 * 0.1111) + (90.0 * 0.18) + ((value - 150.0) * 0.21);
		}
		else
		{
			fine = (60.0 * 0.1111) + (90.0 * 0.153) + ((value - 150.0) * 0.21);
		}
	}

	//Outputs the fine in the format given in the spec
	cout << "The fine for " << identification << " is $" << fine << " million.\n";

}