// CSAcademy - IOI 2016 Training Round - Balanced String
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

bool ok(string s)
{
	int n = s.size();

	int pos = 0;

	for (int i = 0; i < n; i++)
	{
		if (s[i] == 'B')
		{
			pos = i;
			break;
		}
	}

	string s2;

	for (int i = 0; i < n; i++)
		s2 += s[(pos+i)%n];

	s = s2;

	vector<int> V;

	for (int i = 0; i < n; i++)
	{
		if (s[i] == 'B' && s[(i+1)%n] == 'B')
		{
			V.push_back(0);
			continue;
		}

		if (s[i] == 'B') continue;

		int j = i;
		for (; j < n && s[j] == 'A'; j++)
			;
		--j;

		V.push_back(j-i+1);
		i = j;
	}

	int mx = 0, mn = n+1;
	for (auto x: V)
	{
		mx = max(mx, x);
		mn = min(mn, x);
	}

	if (V.size() <= 1) return true;
	if (mn < mx-1) return false;

	string t;
	for (auto x: V)
		t += (x == mx ? 'A' : 'B');

	return ok(t);
}

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		string s;
		cin >> s;

		if (ok(s)) printf("1\n");
		else printf("0\n");
	}
}
