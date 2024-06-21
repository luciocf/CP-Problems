// Codeforces 1360F - Spy-string
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

int n, m;
string s[11];

bool isOk(string t)
{
	for (int i = 1; i <= n; i++)
	{
		int qtd = 0;
		for (int j = 0; j < m; j++)
			if (s[i][j] != t[j])
				qtd++;

		if (qtd > 1) return 0;
	}
	return 1;
}

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		cin >> n >> m;

		for (int i = 1; i <= n; i++)
			cin >> s[i];

		bool done = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				string t = s[i];
				for (char c = 'a'; c <= 'z'; c++)
				{
					if (done) break;

					t[j] = c;
					if (isOk(t))
					{
						cout << t << "\n";
						done = 1;
						break;
					}
				}
			}
		}

		if (!done) cout << "-1\n";
	}
}
