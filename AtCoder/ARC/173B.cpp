// ARC 173B - Make Many Triangles
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
#define mkp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 310;

int n;
pii a[maxn];

ll cross(pii p1, pii p2)
{
	return 1ll*p1.ff*p2.ss - 1ll*p1.ss*p2.ff;
}

bool col(pii p1, pii p2, pii p3)
{
	p2.ff -= p1.ff; p2.ss -= p1.ss;
	p3.ff -= p1.ff; p3.ss -= p1.ss;
	return cross(p2, p3) == 0;
}

int main(void)
{
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> a[i].ff >> a[i].ss;

	int mx = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i+1; j <= n; j++)
		{
			int qtd = 2;
			for (int k = j+1; k <= n; k++)
				if (col(a[i], a[j], a[k]))
					qtd++;

			mx = max(mx, qtd);
		}
	}

	cout << min(n/3, n-mx) << "\n";
}
