// APIO 2016 - Gap
// Lúcio Cardoso

// Solution is the same as this one: https://codeforces.com/blog/entry/44657?#comment-293060

// Essentialy, make queries on intervals with length >= (a_n - a_1)/(n-1).

#include <bits/stdc++.h>
#include "gap.h"
 
using namespace std;
 
const int maxn = 1e5+10;
const long long maxv = 1e18+10;
 
typedef long long ll;
 
ll a[maxn];
 
long long findGap(int T, int N)
{
	if (T == 1)
	{
		ll mn, mx;
		MinMax(0, maxv, &mn, &mx);
 
		int l = 1, r = N;
		a[1] = mn, a[N] = mx;
 
		while (true)
		{
			if (r-l <= 1) break;
 
			MinMax(a[l]+1, a[r]-1, &mn, &mx);
 
			a[++l] = mn, a[--r] = mx;
		}
 
		ll ans = 0;
		for (int i = 1; i < N; i++)
			ans = max(ans, a[i+1]-a[i]);
 
		return ans;
	}
 
	ll mn, mx;
	MinMax(0, 1e18, &mn, &mx);
 
	a[1] = mn, a[N] = mx;
	ll delta = (mx-mn)/(N-1);
 
	ll first = a[1], cur = a[1]+1;
	ll ans = 0;
 
	while (true)
	{
		if (cur > a[N])
			return ans;
 
		MinMax(cur, cur+delta-1, &mn, &mx);
 
		if (mn == -1)
		{
			cur += delta;
			continue;
		}
		else
		{
			ans = max(ans, mn-first);
			
			cur += delta;
			first = mx;

			delta = max(delta, ans);
		}
	}
}
