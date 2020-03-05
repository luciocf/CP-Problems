// Codeforces 1282D - Enchanted Artifact
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;

int interact(string s)
{
	cout << s << endl;
	fflush(stdout);
 
	int diff;
	cin >> diff;

	if (diff == 0) exit(0);
 
	return diff;
}

int main(void)
{
	string out1 = "";
	for (int i = 1; i <= 300; i++)
		out1.push_back('a');

	int qa = interact(out1);
	qa = 300-qa;

	string out2 = "";
	for (int i = 1; i <= 300; i++)
		out2.push_back('b');

	int qb = interact(out2);
	qb = 300-qb;

	string s = "";
	for (int i = 1; i <= qa+qb; i++)
		s += 'a';

	int n = qa+qb;
	for (int i = 1; i < n; i++)
	{
		s[i-1] = 'b';

		int diff = interact(s);

		if (diff == qb+1)
			s[i-1] = 'a';
		else
			qb--;
	}

	if (qb) s.back() = 'b';
	else s.back() = 'a';

	interact(s);
}
