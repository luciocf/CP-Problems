// JOI Open Contest 2015 - Sterilizing Spray
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 1e5+10;
 
int n, q, k;
int a[maxn];
 
struct FenwickTree
{
	ll bit[maxn];
 
	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] += 1ll*v;
	}
 
	ll soma(int x)
	{
		ll ans = 0;
		for (; x > 0; x -= (x&-x))
			ans += bit[x];
		return ans;
	}
 
	ll get(int l, int r)
	{
		return soma(r)-soma(l-1);
	}
} BIT;
 
void solve1(void)
{
	while (q--)
	{
		int op, l, r;
		scanf("%d %d %d", &op, &l, &r);
 
		if (op == 1)
		{
			BIT.upd(l, r-a[l]);
			a[l] = r;
		}
		else if (op == 3)
		{
			printf("%lld\n", BIT.get(l, r));
		}
	}
}
 
int main(void)
{
	scanf("%d %d %d", &n, &q, &k);
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		BIT.upd(i, a[i]);
	}
 
	if (k == 1)
	{
		solve1();
		return 0;
	}
 
	set<int> st;
	for (int i = 1; i <= n; i++)
		if (a[i] != 0)
			st.insert(i);
 
	while (q--)
	{
		int op, l, r;
		scanf("%d %d %d", &op, &l, &r);
 
		if (op == 1)
		{
			if (r != 0 && st.find(l) == st.end())
				st.insert(l);
 
			BIT.upd(l, r-a[l]);
			a[l] = r;
		}
		else if (op == 2)
		{
			for (auto it = st.lower_bound(l); it != st.end() && *it <= r; )
			{
				int p = *it;
 
				BIT.upd(p, a[p]/k - a[p]);
				a[p] /= k;
 
				if (a[p] == 0) it = st.erase(it);
				else it++;
			}
		}
		else
		{
			printf("%lld\n", BIT.get(l, r));
		}
	}
}
