// Codeforces 1980F1 - Field Division (Easy Version)
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

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

int ans[maxn];

struct F
{
	int x, y, ind;

	bool operator<(const F &o) const
	{
		if (x == o.x) return y < o.y;
		return x < o.x;
	}
};

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		int n, m, k;
		cin >> n >> m >> k;

		vector<F> pos;

		for (int i = 1; i <= k; i++)
		{
			int x, y;
			cin >> x >> y;

			pos.pb({x, y, i});
			ans[i] = 0;
		}

		sort(all(pos));

		int mn = m+1;
		ll tot = 0;
		int ant = n+1;

		for (int i = pos.size()-1; i >= 0; i--)
		{
			while (i > 0 and pos[i-1].x == pos[i].x)
				i--;

			if (mn > pos[i].y) ans[pos[i].ind] = 1;
			else ans[pos[i].ind] = 0;

			tot += 1ll*(mn-1)*(ant-pos[i].x-1);

			mn = min(mn, pos[i].y);
			ant = pos[i].x;

			tot += 1ll*(mn-1);
		}

		tot += 1ll*(ant-1)*(mn-1);

		cout << tot << "\n";
		for (int i = 1; i <= k; i++)
			cout << ans[i] << " ";
		cout << "\n";
	}
}
