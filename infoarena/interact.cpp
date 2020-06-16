// Infoarena - Interact
// Lúcio Cardoso

// Solution:

// We'll add the characters in alphabetic order. When processing character c, we will maintain the current
// substring of the whole string formed only with characters from 'a' to (c-1).

// Suppose s = 'c_1 c_2 c_3 ... c_k'. We'll try to add c as many times as possible before c_1, then
// as many times as possible between c_1 and c_2, etc., until we try to add c as many times as possible after c_k.

// The amount of operations will be at most 100*26 + 100 (for every character, we try to add as much as possible between
// at most 100 positions of the string and every time the character can be added this operation is counted as one more position
// in the answer, so that's why there's a 100 being summed individually). 

#include <bits/stdc++.h>

using namespace std;

string s = "";

int main(void)
{
	for (int i = 0; i <= 25; i++)
	{
		char c = (char)('a'+i);

		if (s.empty())
		{
			for (int j = 0; j < 100; j++)
			{
				s.push_back(c);

				int is;
				cout << "? " << s << endl;
				cin >> is;

				if (!is)
				{
					s.pop_back();
					break;
				}
			}
		}
		else
		{
			int pos = 0;

			while (pos < s.size() && s.size() < 100)
			{
				string aux;

				for (int j = 0; j < pos; j++)
					aux.push_back(s[j]);

				aux.push_back(c);

				for (int j = pos; j < s.size(); j++)
					aux.push_back(s[j]);

				int is;
				cout << "? " << aux << endl;
				cin >> is;

				if (is) swap(s, aux);
				++pos;
			}

			while (s.size() < 100)
			{
				string aux = s;
				aux.push_back(c);

				int is;
				cout << "? " << aux << endl;
				cin >> is;

				if (is) swap(s, aux);
				else break;
			}
		}
	}

	int menosum;
	cout << "! " << s << endl;
	cin >> menosum;
}
