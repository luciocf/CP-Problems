// Timus 2167 - Cipher Message 5
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

const int maxn = 3e6+10;

bool mark[maxn];
int pref[maxn];

void sieve(void)
{
	mark[1] = 1;
	for (int i = 2; i < maxn; i++)
		if (!mark[i])
			for (int j = 2*i; j < maxn; j += i)
				mark[j] = 1;
}

int qtd(int l, int r)
{
	return pref[r]-pref[(l == 0 ? 0 : l-1)];
}

int main(void)
{
	int n;
	cin >> n;

	sieve();

	for (int i = 1; i < maxn; i++)
		pref[i] = pref[i-1] + (mark[i] ? 0 : 1);

	while (n--)
	{
		int v;
		cin >> v;

		int s = 0;
		int ans = 0;

		for (int b = 20; b >= 0; b--)
		{
			if (v&(1<<b))
			{
				if (qtd(s+(1<<b), s+(1<<(b+1))-1) == 0)
					ans += (1<<b);
			}
			else
			{
				if (qtd(s, s+(1<<b)-1) == 0)
					ans += (1<<b);
			}

			if (v&(1<<b) and !(ans&(1<<b))) s += (1<<b);
			if (!(v&(1<<b)) and (ans&(1<<b))) s += (1<<b);
		}

		cout << ans << "\n";
	}
}
