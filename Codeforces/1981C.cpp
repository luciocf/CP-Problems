// Codeforces 1981C - Turtle and an Incomplete Sequence
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

int a[maxn], b[maxn];

vector<int> getPath(int x, int y)
{
	vector<int> l, r;

	while ((int)log2(x) > (int)log2(y))
	{
		l.push_back(x);
		x /= 2;
	}

	while ((int)log2(y) > (int)log2(x))
	{
		r.push_back(y);
		y /= 2;
	}

	while (x != y)
	{
		l.push_back(x); r.push_back(y);
		x /= 2; y /= 2;
	}

	l.push_back(x);

	reverse(r.begin(), r.end());
	for (auto k: r)
		l.push_back(k);

	return l;
}

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		int n;
		cin >> n;

		vector<int> pos;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			b[i] = a[i];
 			if (a[i] != -1) pos.push_back(i);
		}

		if (pos.size() == 0)
		{
			for (int i = 1; i <= n; i++)
			{
				if (i%2) cout << "1 ";
				else cout << "2 ";
			}
			cout << "\n";
			continue;
		}

		for (int i = pos[0]-1; i >= 1; i--)
		{
			if ((pos[0]-i)%2) b[i] = 2*a[pos[0]];
			else b[i] = a[pos[0]];
		}

		for (int i = pos.back()+1; i <= n; i++)
		{
			if ((i-pos.back())%2) b[i] = 2*a[pos.back()];
			else b[i] = a[pos.back()];
		}

		bool ok = 1;
		for (int i = 0; i+1 < pos.size(); i++)
		{
			int l = pos[i], r = pos[i+1];
			vector<int> v = getPath(a[l], a[r]);

			if (v.size() > r-l+1)
			{
				ok = 0;
				break;
			}

			int pos = l+v.size()-1;
			if ((r-pos)%2)
			{
				ok = 0;
				break;
			}

			for (int j = l; j <= pos; j++)
				b[j] = v[j-l];
			for (int j = pos+1; j <= r; j++)
			{
				if ((j-pos)%2) b[j] = 2*a[r];
				else b[j] = a[r];
			}
		}

		if (!ok) cout << "-1\n";
		else
		{
			for (int i = 1; i <= n; i++)
				cout << b[i] << " ";
			cout << "\n";
		}
	}
}
