// Codeforces 1367D - Task On The Board
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

const int maxn = 55;

int a[maxn];
bool mark[maxn];

char ans[maxn];

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		string s;
		cin >> s;

		int n = s.size(), m;
		cin >> m;

		map<char, int> fq;
		for (auto c: s)
			fq[c]++;

		for (int i = 1; i <= m; i++)
		{
			mark[i] = 0;
			cin >> a[i];
		}

		char c = 'z';
		while (true)
		{
			vector<int> pos;
			for (int i = 1; i <= m; i++)
			{
				if (!mark[i] and a[i] == 0)
				{
					mark[i] = 1;
					pos.pb(i);
				}
			}

			while (fq[c] < pos.size())
				c--;

			for (auto i: pos)
			{
				ans[i] = c;
				for (int j = 1; j <= m; j++)
						if (!mark[j])
							a[j] -= abs(i-j);
			}

			if (pos.size() == 0) break;

			c--;
		}

		for (int i = 1; i <= m; i++)
			cout << ans[i];
		cout << "\n";
	}
}
