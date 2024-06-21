// Codeforces 1360G - A/B Matrix
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

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const int maxn = 55;

int num[maxn][maxn];
int qtd[maxn];

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		int n, m, a, b;
		cin >> n >> m >> a >> b;

		for (int i = 1; i <= n; i++)
		{	
			for (int j = 1; j <= m; j++)
				num[i][j] = qtd[j] = 0;
		}

		for (int i = 1; i <= n; i++)
		{
			vector<pii> pos;
			for (int j = 1; j <= m; j++)
				pos.pb({qtd[j], j});

			sort(pos.begin(), pos.end());

			for (int j = 0; j < a; j++)
			{
				num[i][pos[j].ss] = 1;
				qtd[pos[j].ss]++;
			}
		}

		bool ok = 1;
		for (int i = 1; i <= m; i++)
			if (qtd[i] != b)
				ok = 0;

		if (!ok) cout << "NO\n";
		else
		{
			cout << "YES\n";
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= m; j++)
					cout << num[i][j];
				cout << "\n";
			}
		}
	}
}
