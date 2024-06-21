// Codeforces 1975E1 - Asterism (Easy Version)
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

const int maxn = 2010;

bool mark[maxn];
int a[maxn];

int main(void)
{
	int n, p;
	cin >> n >> p;

	mark[0] = 1;
	for (int i = p; i <= 2000; i += p)
		mark[i] = 1;

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	sort(a+1, a+n+1);

	vector<int> ans;

	for (int x = 1; x <= 2000; x++)
	{
		int ptr = 0;
		int sub = 0;
		bool ok = 1;

		for (int i = x; i < x+n; i++)
		{
			while (ptr+1 <= n and a[ptr+1] <= i)
				ptr++;

			if (mark[ptr-sub])
			{
				ok = 0;
				break;
			}

			sub++;
		}

		if (ok) ans.pb(x);
	}

	cout << ans.size() << "\n";
	for (auto x: ans)
		cout << x << " ";
	cout << "\n";
}
