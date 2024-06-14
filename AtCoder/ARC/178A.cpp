// ARC 178A - Good Permutation 2
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

bool mark[maxn];
bool done[maxn];

int main(void)
{
	int n, m;
	cin >> n >> m;

	bool ok = 1;
	for (int i = 1; i <= m; i++)
	{
		int x;
		cin >> x;

		mark[x] = 1;
		if (x == 1 or x == n) ok = 0;
	}

	if (!ok)
	{
		cout << "-1\n";
		return 0;
	}

	for (int i = 1; i <= n; i++)
	{
		if (done[i]) continue;
		done[i] = 1;

		if (mark[i])
		{
			int j;
			for (j = i+1; j <= n; j++)
			{
				cout << j << " ";
				done[j] = 1;

				if (!mark[j]) break;
			}
			cout << i << " ";
			i = j;
		}
		else cout << i << " ";
	}
	cout << "\n";
}
