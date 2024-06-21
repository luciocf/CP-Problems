// Codeforces 1368D - AND, OR and square sum
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

const int maxn = 2e5+10;

int a[maxn], qtd[30];

int main(void)
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];

		for (int b = 0; b < 30; b++)
			if (a[i]&(1<<b))
				qtd[b]++;
	}

	ll ans = 0;

	for (int i = n; i >= 1; i--)
	{
		a[i] = 0;
		for (int b = 0; b < 30; b++)
		{
			if (qtd[b])
			{
				qtd[b]--;
				a[i] += (1<<b);
			}
		}

		ans += 1ll*a[i]*a[i];
	}

	cout << ans << "\n";
}
