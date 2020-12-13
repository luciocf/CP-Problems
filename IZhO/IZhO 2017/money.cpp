// IZhO 2017 - Money
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e6+10;
 
int a[maxn];

struct FenwickTree
{
	int bit[maxn];

	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] += v;
	}

	int soma(int x)
	{
		int ans = 0;
		for (; x > 0; x -= (x&-x))
			ans += bit[x];
		return ans;
	}

	int get(int s)
	{
		int pos = 0, soma = 0;

		for (int i = 20; i >= 0; i--)
			if (pos+(1<<i) < maxn && soma + bit[pos+(1<<i)] < s)
				pos += (1<<i), soma += bit[pos];

		return pos+1;
	}
} BIT;

int main(void)
{
	int n;
	scanf("%d", &n);
  
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		BIT.upd(a[i], 1);
	}
 
	int ans = 0;
 
	for (int r = n; r >= 1; r--)
	{
		++ans;
 
		int l = r;
 		BIT.upd(a[l], -1);

		while (l > 1 && a[l-1] == a[l])
		{
			l--;
			BIT.upd(a[l], -1);
		}
 
		while (l > 1)
		{
			if (a[l] == a[r] && a[l-1] != BIT.get(BIT.soma(a[l]-1))) break;
			if (a[l] != a[r] && a[l-1] != BIT.get(BIT.soma(a[l]))) break;

			--l;
			BIT.upd(a[l], -1);
		}
 
		r = l;
	}
 
	printf("%d\n", ans);
}
