#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

void Split(int x, int& a, int& b, int& c, int& d)
{
	d = x % 10; x /= 10;
	c = x % 10; x /= 10;
	b = x % 10; x /= 10;
	a = x % 10;
}

bool IsValid(int x)
{
	int a, b, c, d;
	Split(x, a, b, c, d);
	return
		(a >= 1) && (a <= 9) &&
		(a != b) && (a != c) && (a != d) && (b != c) && (b != d) && (c != d);
}

bool Matches(int n1, int n2, int bulls, int cows)
{
	int a1, b1, c1, d1, a2, b2, c2, d2;
	Split(n1, a1, b1, c1, d1);
	Split(n2, a2, b2, c2, d2);
	return
		bulls == (
			(a1 == a2) + (b1 == b2) + (c1 == c2) + (d1 == d2)
		) &&
		cows == (
			(a1 == b2) + (a1 == c2) + (a1 == d2) +
			(b1 == a2) + (b1 == c2) + (b1 == d2) +
			(c1 == a2) + (c1 == b2) + (c1 == d2) +
			(d1 == a2) + (d1 == b2) + (d1 == c2)
		);
}

const int setSize = 10000;
bool badNum[setSize];

int main()
{
	memset(badNum, 0, sizeof(badNum));
	for (int i = 0; i < setSize; i++)
		badNum[i] = !IsValid(i);
	while (true)
	{
		int bulls, cows;
		int question;
		for (question = 0; question < setSize && badNum[question]; question++);
		if (question >= setSize)
		{
			cout << "bye bye!";
			break;
		}
		cout << question << " ???" << endl;
		cout << "bulls, cows: ";
		cin >> bulls >> cows;
		if (bulls == 4 && cows == 0)
		{
			cout << "that's it :-)";
			break;
		}
		for (int i = 0; i < setSize; i++)
			badNum[i] = badNum[i] || !Matches(i, question, bulls, cows);
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
