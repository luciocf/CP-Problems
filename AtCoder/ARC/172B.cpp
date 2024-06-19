// ARC 172B - AtCoder Language
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

const int mod = 998244353;

int main(void)
{
	int n, k, l;
	cin >> n >> k >> l;

	int ans = 1;
	for (int i = 0; i < n-k; i++)
		ans = (1ll*ans*max(0, l-i))%mod;

	for (int i = n-k+1; i <= n; i++)
		ans = (1ll*ans*max(0, l-n+k))%mod;

	cout << ans << "\n";
}
