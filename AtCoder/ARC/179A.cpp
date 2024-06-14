// ARC 179A - Partition
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

int a[maxn];

int main(void)
{
	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	if (k > 0) sort(a+1, a+n+1);
	else sort(a+1, a+n+1, greater<int>());

	ll s = 0;
	bool done = (s >= k ? 1 : 0), ok = 1;

	for (int i = 1; i <= n; i++)
	{
		s += 1ll*a[i];
		if (s < k and done) ok = 0;
		if (s >= k) done = 1;
	}

	if (!ok) cout << "No\n";
	else
	{
		cout << "Yes\n";
		for (int i = 1; i <= n; i++)
			cout << a[i] << " ";
		cout << "\n";
	}
}
