// Codeforces 1367E - Necklace Assembly
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

const int maxn = 2e3+10;

int fq[27];
bool mark[maxn];

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		int n, k;
		cin >> n >> k;

		string s;
		cin >> s;

		for (int i = 0; i < 26; i++)
			fq[i] = 0;

		for (auto c: s)
			fq[c-'a']++;

		for (int m = n; m >= 1; m--)
		{
			multiset<int> st;
			for (int i = 0; i < 26; i++)
				st.insert(-fq[i]);

			vector<int> sz;

			for (int i = 0; i < m; i++)
				mark[i] = 0;

			for (int i = 0; i < m; i++)
			{
				if (mark[i]) continue;

				int at = i, qtd = 0;
				while (!mark[at])
				{
					qtd++;
					mark[at] = 1;
					at = (at+k)%m;
				}

				sz.pb(qtd);
			}

			sort(sz.begin(), sz.end());

			bool ok = 1;
			for (int i = sz.size()-1; i >= 0; i--)
			{
				if (st.size() == 0 or -*st.begin() < sz[i])
				{
					ok = 0;
					break;
				}

				int x = -*st.begin();
				st.erase(st.begin());

				x -= sz[i];
				if (x > 0) st.insert(-x);
			}

			if (ok)
			{
				cout << m << "\n";
				break;
			}
		}
	}	
}
