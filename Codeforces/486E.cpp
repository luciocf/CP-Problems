// Codeforces 486E - LIS of Sequence
// Lúcio Cardoso

// Solution: https://codeforces.com/blog/entry/14678?#comment-196550

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn];

int bit[2][maxn];

int pref[maxn], suf[maxn];

int freq[maxn];

void upd(int x, int v, bool q)
{
	for (; x < maxn; x += (x&-x))
		bit[q][x] = max(bit[q][x], v);
}

int mx(int x, bool q)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans = max(ans, bit[q][x]);
	return ans;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int lis = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		int x = mx(a[i]-1, 0);
		pref[i] = x+1;

		upd(a[i], pref[i], 0);

		lis = max(lis, pref[i]);
	}
	

	for (int i = n; i >= 1; i--)
	{
		int x = mx(maxn-(a[i]+1), 1);
		suf[i] = x+1;

		upd(maxn-a[i], suf[i], 1);
	}

	for (int i = 1; i <= n; i++)
		if (pref[i]+suf[i]-1 == lis)
			freq[pref[i]]++;

	for (int i = 1; i <= n; i++)
	{
		if (pref[i]+suf[i]-1 < lis) printf("1");
		else if (freq[pref[i]] > 1) printf("2");
		else printf("3");
	}
	printf("\n");
}
