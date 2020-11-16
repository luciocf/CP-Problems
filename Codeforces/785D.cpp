// Codeforces 785D - Anton and School - 2
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int mod = 1e9+7;

char a[maxn];

int fat[maxn];

int pot(int a, int b)
{
	int ans = 1;

	for (; b; b /= 2, a = (1ll*a*a)%mod)
		if (b&1)
			ans = (1ll*ans*a)%mod;

	return ans;
}

int choose(int a, int b)
{
	if (a < b) return 0;
	return (1ll*fat[a]*pot((1ll*fat[b]*fat[a-b])%mod, mod-2))%mod;
}

int main(void)
{
	string s;
	cin >> s;

	int n = s.size(), open = 0, close = 0;

	for (int i = 0; i < n; i++)
		if (s[i] == ')')
			close++;

	fat[0] = 1;
	for (int i = 1; i <= n; i++)
		fat[i] = (1ll*i*fat[i-1])%mod;

	int ans = 0;

	for (int i = 0; i < n; i++)
	{
		if (s[i] == '(') ++open;
		else
		{
			ans = (ans + choose(open+close-1, close))%mod;
			--close;
		}
	}

	printf("%d\n", ans);
}
