// USACO 2014/2015 Gold - Censoring
// Lúcio Cardoso

// Solution is the same as in editorial (using hashing)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int mod = 1e9+7;
const int P = 31;

int hsh[maxn];
int pot[maxn];

int cmp[maxn], back[maxn];

vector<string> V;

unordered_map<int, bool> tem[450];

int gethash(int h, int c)
{
	return (1ll*h*P + 1ll*c)%mod;
}

void compress(void)
{
	map<int, int> mp;

	for (auto t: V)
		mp[t.size()] = 0;

	int aux = 0;
	for (auto x: mp)
	{
		cmp[x.first] = ++aux;
		back[aux] = x.first;
	}
}

int main(void)
{
	freopen("censor.in", "r", stdin); freopen("censor.out", "w", stdout);

	string S;
	cin >> S;

	int n;
	cin >> n;

	pot[0] = 1; 
	for (int i = 1; i < maxn; i++)
		pot[i] = (1ll*P*pot[i-1])%mod;

	for (int i = 1; i <= n; i++)
	{
		string t;
		cin >> t;

		V.push_back(t);
	}

	compress();

	for (auto t: V)
	{
		int h = 0;

		for (int i = 0; i < t.size(); i++)
			h = gethash(h, (int)(t[i]-'a'+1));

		tem[cmp[t.size()]][h] = true;
	}

	vector<char> ans(S.size()+2);
	hsh[0] = 0;

	int at = 1;

	for (int i = 1; i <= S.size(); i++)
	{
		hsh[at] = gethash(hsh[at-1], (int)(S[i-1]-'a'+1));

		bool ok = true;

		for (int j = 1; j < 450; j++)
		{
			if (back[j] == 0 || back[j] > at) break;

			int l = back[j];

			int h = (hsh[at] - (1ll*hsh[at-l]*pot[l])%mod + mod)%mod;

			if (tem[j].find(h) != tem[j].end())
			{
				ok = false, at -= (l-1);
				break;
			}
		}

		if (ok) ans[at] = S[i-1], ++at;
	}

	for (int i = 1; i < at; i++)
		cout << ans[i];
	cout << "\n";
}
