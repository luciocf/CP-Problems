// XI Samara Regional Intercollegiate Programming Contest - M - Forgotten Spell
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

string s[3];

int tot(string a, int i)
{
	int qtd = 0;

	for (int j = 0; j < a.size(); j++)
		if (s[i][j] != a[j])
			++qtd;

	return qtd;
}

bool ok(string a, int i)
{
	return tot(a, i) <= 1;
}

int main(void)
{
	cin >> s[0] >> s[1] >> s[2];

	if (s[0] == s[1] && s[1] == s[2])
	{
		cout << "Ambiguous\n";
		return 0;
	}

	set<string> st;

	if (max({tot(s[0], 1), tot(s[0], 2), tot(s[1], 0), tot(s[1], 2), tot(s[2], 0), tot(s[2], 1)}) > 2)
	{
		cout << "Impossible\n";
		return 0;
	}

	if (ok(s[0], 1) && ok(s[0], 2))
		st.insert(s[0]);

	if (ok(s[1], 0) && ok(s[1], 2))
		st.insert(s[1]);

	if (ok(s[2], 0) && ok(s[2], 1))
		st.insert(s[2]);

	for (int i = 0; i < 3; i++)
	{
		string a = s[i];

		for (int j = 0; j < 3; j++)
		{
			if (i == j) continue;

			for (int l = 0; l < s[0].size(); l++)
			{
				if (s[i][l] != s[j][l])
				{
					for (char c = 'a'; c <= 'z'; c++)
					{
						a[l] = c;

						if (ok(a, 0) && ok(a, 1) && ok(a, 2)) st.insert(a);

						a[l] = s[i][l];
					}
				}
			}
		}
	}

	if (st.size() == 0) cout << "Impossible\n";
	else if (st.size() > 1) cout << "Ambiguous\n";
	else cout << *st.begin() << "\n";
}
