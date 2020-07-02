// CEOI 2017 - Palindromic Partitions
// Lúcio Cardoso

// Solution is the same as in: https://ceoi2017.acm.si/files/ceoi2017-solutions-day2.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;
const int mod = 1e9+7;
const int P = 31;

int suf[maxn];
int pot[maxn];

int main(void)
{
	int tc;
	cin >> tc;

	pot[0] = 1;
	for (int i = 1; i < maxn; i++)
		pot[i] = (1ll*P*pot[i-1])%mod;

	while (tc--)
	{
		string s;
		cin >> s;

		suf[s.size()] = 0;

		for (int i = s.size()-1; i >= 0; i--)
			suf[i] = (1ll*suf[i+1]*P + 1ll*(int)(s[i]-'a'+1))%mod;

		int l = 0, r = s.size()-1, len = 0;
		int hsh = 0, ans = 0;

		while (l <= r)
		{
			++len;
			hsh = (1ll*hsh + 1ll*pot[len-1]*(int)(s[l]-'a'+1))%mod;

			if (hsh == (suf[r] - (1ll*suf[r+len]*pot[len])%mod + mod)%mod)
			{
				if (l == r) ans++;
				else ans += 2;
				len = 0, hsh = 0;
			}


			l++, r--;
		}

		if (len) ans++;

		printf("%d\n", ans);
	}
}
