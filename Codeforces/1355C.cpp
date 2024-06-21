// Codeforces 1355C - Count Triangles
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

const int maxn = 1e6+10;

ll sum[maxn];
int add[maxn];

int main(void)
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;

	for (int x = a; x <= b; x++)
	{
		add[x+c]++;
		add[x+b-1]--;
	}

	for (int i = b+c; i >= 0; i--)
	{
		add[i] += add[i+1];
		sum[i] = add[i] + sum[i+1];
	}

	ll ans = 0;
	for (int z = c; z <= d; z++)
		ans += 1ll*sum[z+1];

	cout << ans << "\n";
}
