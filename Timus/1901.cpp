// Timus 1901 - Space Elevators
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

const int maxn = 1e5+10;

int a[maxn];
bool mark[maxn];

int main(void)
{
	int n, s;
	cin >> n >> s;

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	sort(a+1, a+n+1);

	int pos = -1;
	for (int i = 1; i <= n; i++)
		if (a[i] <= s/2)
			pos = i;

	if (pos == -1)
	{	
		cout << n << "\n";
		for (int i = 1; i <= n; i++)
			cout << a[i] << " ";
		cout << "\n";
		return 0;
	}

	int ptr = pos+1;
	vector<int> ind;

	for (int i = pos; i >= 1; i--)
	{
		while (a[i]+a[ptr] <= s and ptr+1 <= n)
			ptr++;

		if (a[i]+a[ptr] <= s) break;

		ind.push_back(a[ptr]); ind.push_back(a[i]);
		mark[ptr] = mark[i] = 1;
		ptr++;
	}

	reverse(ind.begin(), ind.end());

	for (int i = n; i >= 1; i--)
		if (!mark[i])
			ind.push_back(a[i]);

	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans++;
		if (i < n-1 and ind[i]+ind[i+1] <= s)
			i++;
	}

	cout << ans << "\n";
	for (auto i: ind)
		cout << i << " ";
	cout << "\n";
}
