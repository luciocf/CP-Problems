// USACO 2016/2017 - Why Did the Cow Cross the Road III
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const int inf = 1e9+10;
const int bucket = 320;

int pos[maxn];
int a[maxn];

int bit[maxn][bucket];

int bloco[maxn];

void upd(int x, int k, int v)
{
	x++;
	for (; x < maxn; x += (x&-x))
		bit[x][k] += v;
}

ll soma(int x, int k)
{
	x++;
	ll ans = 0;

	for (; x > 0; x -= (x&-x))
		ans += 1ll*bit[x][k];

	return ans;
}

int main(void)
{
	freopen("friendcross.in", "r", stdin);
	freopen("friendcross.out", "w", stdout);

	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++)
	{
		int x;
		scanf("%d", &x);

		pos[x-1] = i;
	}

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
		a[i]--;

		bloco[i] = inf;
	}

	ll ans = 0;

	for (int i = n-1; i >= 0; i--)
	{
		int l = 0, r = a[i]-k-1;
		int p = l/bucket, q = r/bucket;

		if (r >= 0)
		{
			if (p == q)
			{
				for (int j = l; j <= r; j++)
					if (bloco[j] < pos[a[i]])
						ans++;
			}
			else
			{
				for (int j = l; j < (p+1)*bucket; j++)
					if (bloco[j] < pos[a[i]])
						ans++;

				for (int j = q*bucket; j <= r; j++)
					if (bloco[j] < pos[a[i]])
						ans++;

				for (int j = p+1; j < q; j++)
					ans += 1ll*soma(pos[a[i]]-1, j);
			}
		}

		l = a[i]+k+1, r = n-1;
		p = l/bucket, q = r/bucket;

		if (l < n)
		{
			if (p == q)
			{
				for (int j = l; j <= r; j++)
					if (bloco[j] < pos[a[i]])
						ans++;
			}
			else
			{
				for (int j = l; j < (p+1)*bucket; j++)
					if (bloco[j] < pos[a[i]])
						ans++;

				for (int j = q*bucket; j <= r; j++)
					if (bloco[j] < pos[a[i]])
						ans++;

				for (int j = p+1; j < q; j++)
					ans += 1ll*soma(pos[a[i]]-1, j);
			}
		}

		bloco[a[i]] = pos[a[i]];

		upd(pos[a[i]], a[i]/bucket, 1);
	}

	printf("%lld\n", ans);
}
