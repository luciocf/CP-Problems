// Codeforces 1117E - Decypher the String
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;

char ans[maxn];

tuple<char, char, char> code[maxn];
map<tuple<char, char, char>, int> mp;

int main(void)
{
	string t;
	cin >> t;

	int n = t.size();

	int ptr = 0;

	for (char c1 = 'a'; c1 <= 'z' && ptr < n; c1++)
		for (char c2 = 'a'; c2 <= 'z' && ptr < n; c2++)
			for (char c3 = 'a'; c3 <= 'z' && ptr < n; c3++)
				code[ptr++] = make_tuple(c1, c2, c3), mp[make_tuple(c1, c2, c3)] = ptr-1;

	string s0, s1, s2;
	string a0, a1, a2;

	for (int i = 0; i < n; i++)
	{
		s0.push_back(get<0>(code[i]));
		s1.push_back(get<1>(code[i]));
		s2.push_back(get<2>(code[i]));
	}

	cout << "? " << s0 << endl;
	cin >> a0;

	cout << "? " << s1 << endl;
	cin >> a1;

	cout << "? " << s2 << endl;
	cin >> a2;

	for (int i = 0; i < n; i++)
		ans[mp[make_tuple(a0[i], a1[i], a2[i])]] = t[i];

	cout << "! ";
	for (int i = 0; i < n; i++)
		cout << ans[i];
	cout << endl;
}
