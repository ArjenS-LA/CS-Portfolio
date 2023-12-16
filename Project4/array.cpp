#include <iostream>
#include <cassert>
#include <cctype>
#include <string>

using namespace std;

int reduplicate(string a[], int n)
{
	//checks if n is negative
	if (n < 0) return -1;

	//loops through elements of the array
	for (int i = 0; i < n; i++)
	{
		a[i] += a[i];
	}

	return n;
}

int locate(const string a[], int n, string target)
{
	//Checks if n is negative
	if (n < 0) return -1;

	//loops through array to locate target
	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)
			return i;
	}

	//there is no match in the array
	return -1;
}

int locationOfMax(const string a[], int n)
{
	//Returns -1 since n won't examine any elements of the array
	if (n <= 0) return -1;

	string max = a[0];
	int position = 0;

	//loops through the array comparing each element to max
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
			position = i;
		}
	}

	return position;
}

int circleLeft(string a[], int n, int pos)
{
	//Checks if n is negative or if pos is out of bounds
	if (n < 0 || pos >= n) return -1;
	
	string temp = a[pos];

	for (int i = pos; i < n - 1; i++)
	{
		a[i] = a[i + 1]; //Moves elements left from position
	}

	a[n - 1] = temp; //moves string at position to the end

	return pos;
}

int enumerateRuns(const string a[], int n)
{
	//Checks if n is negative
	if (n < 0) return -1;

	if (n == 0) return 0;

	int runs = 1; //runs starts = 1 because first position is technically a run

	for (int i = 1; i < n; i++)
	{
		if (a[i] != a[i - 1]) //If the current position is not == to the previous position, it's a new run
			runs++;
	}

	return runs;
}

int flip(string a[], int n)
{
	//Checks if n is negative
	if (n < 0) return -1;

	for (int i = 0; i < n / 2; i++)
	{
		string temp = a[(n - 1) - i];

		a[(n - 1) - i] = a[i]; 
		a[i] = temp;
	}

	return n;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
	//Determines if either n1 or n2 are negative
	if (n1 < 0 || n2 < 0) return -1;

	int minLength; //Sets minLength
	if (n1 < n2)
	{
		minLength = n1;
	}
	else
	{
		minLength = n2;
	}

	for (int i = 0; i < minLength; i++)
	{
		if (a1[i] != a2[i])
			return i;
	}

	return minLength;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	//Determines if either n1 or n2 are negative
	if (n1 < 0 || n2 < 0) return -1;

	if (n2 == 0) return 0; //Conditional expression determining the smallest array

	for (int i = 0; i <= n1 - n2; i++) //n1 - n2 prevents loop from going out of bounds
	{
		bool found = true;
		for (int j = 0; j < n2; j++)
		{
			if (a1[i + j] != a2[j])
			{
				found = false;
				break; //Match is not found, breaks out of inner loop
			}
		}

		if (found) 
			return i; //Found the match
	}
	return -1; //Match not found
}

int locateAny(const string a1[], int n1, const string a2[], int n2)
{
	//Determines if either n1 or n2 are negative
	if (n1 < 0 || n2 < 0) return -1;

	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (a1[i] == a2[j])
				return i; //Match is found, return i
		}
	}

	return -1; //Match not found
}

int divide(string a[], int n, string divider)
{
	//Checks if n is negative
	if (n < 0) return -1;

	int leftIndex = 0;
	int rightIndex = n - 1;

	for (int i = 0; i < n; i++)
	{
		while (leftIndex <= rightIndex && a[leftIndex] < divider) //Keeps going until leftIndex > rightIndex or an element >= divider
		{
			leftIndex++; //Moves to the right until loop finds an element < divider 
		}

		while (leftIndex <= rightIndex && a[rightIndex] >= divider) //Keeps going until leftIndex > rightIndex or an element < divider
		{
			rightIndex--; //Moves to the left until loop finds an element >= divider
		}

		if (leftIndex <= rightIndex) //Places element that is < divider before the rightIndex
		{
			string temp = a[leftIndex];
			a[leftIndex] = a[rightIndex];
			a[rightIndex] = temp;
		}
	}

	if (leftIndex == 0) return n; //there are no elements in the array that are < divider

	return leftIndex; //left is now stored

}

int main()
{
	string c[4] = { "ma", "can", "tu", "do" };
	string d[5] = { "ron", "ron", "ron", "chris", "chris" };
	string e[4] = { "asa", "vivek", "", "chris" };
	string f[3] = { "vivek", "asa", "tim" };
	string h[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
	string g[4] = { "nikki", "ron", "chris", "tim" };

	//Function fails and returns -1 (including functions where n = 0)
	assert(reduplicate(h, -4) == -1);
	assert(locate(h, 2, "asa") == -1);
	assert(locate(h, -1, "asa") == -1);
	assert(locate(h, 0, "asa") == -1);
	assert(locationOfMax(h, -1) == -1);
	assert(locationOfMax(h, 0) == -1);
	assert(circleLeft(h, -1, 2) == -1);
	assert(circleLeft(h, 0, 1) == -1);
	assert(circleLeft(h, 2, 2) == -1);
	assert(circleLeft(h, 0, 0) == -1);
	assert(enumerateRuns(h, -1) == -1);
	assert(locateDifference(c, -1, d, 1) == -1);
	assert(locateDifference(c, 1, d, -1) == -1);
	assert(locateDifference(c, -1, d, -1) == -1);
	assert(subsequence(d, 5, c, 2) == -1);
	assert(subsequence(c, 0, d, 5) == -1);
	assert(subsequence(c, 4, d, -5) == -1);
	assert(subsequence(c, -4, d, 5) == -1);
	assert(subsequence(c, -4, d, -5) == -1);
	assert(locateAny(c, 4, d, 5) == -1);
	assert(locateAny(c, -4, d, 5) == -1);
	assert(locateAny(c, 4, d, -5) == -1);
	assert(locateAny(c, -4, d, -5) == -1);
	assert(locateAny(c, 0, d, 5) == -1);
	assert(locateAny(c, 4, d, 0) == -1);
	assert(divide(h, -5, "man") == -1);


	//Where n = 0 is not an outright failure
	assert(reduplicate(h, 0) == 0);
	assert(enumerateRuns(h, 0) == 0);
	assert(flip(h, 0) == 0);
	assert(locateDifference(c, 4, d, 0) == 0);
	assert(locateDifference(c, 0, h, 0) == 0);
	assert(locateDifference(c, 0, h, 7) == 0);
	assert(subsequence(c, 0, d, 0) == 0);
	assert(subsequence(c, 4, h, 0) == 0);
	assert(divide(h, 0, "man") == 0);


	//----------------------------------------------
	assert(locate(h, 7, "chris") == 5);
	assert(locate(h, 7, "asa") == 2);
	assert(locationOfMax(h, 7) == 3);
	assert(locateAny(h, 7, f, 3) == 2);
	assert(locateDifference(h, 4, g, 4) == 2);
	assert(subsequence(h, 7, e, 4) == 2);
	assert(subsequence(h, 7, g, 2) == 0);

	assert(locationOfMax(c, 4) == 2);

	assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

	assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");

	assert(flip(g, 4) == 4 && g[0] == "ron" && g[2] == "chris");

	assert(enumerateRuns(d, 5) == 2);
	assert(enumerateRuns(g, 4) == 4);

	assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");

	assert(divide(h, 7, "donald") == 3);
	assert(locate(h, 7, "chris") == 0);

	assert(divide(c, 4, "cam") == 4);
	assert(locate(c, 1, "mA") == -1);

	cout << "All tests succeeded" << endl;
}