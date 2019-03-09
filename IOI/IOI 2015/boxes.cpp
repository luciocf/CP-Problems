// IOI 2015 - Boxes with Souvenirs
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "boxes.h"
 
using namespace std;
 
const int maxn = 1e7+10;
 
typedef long long ll;
 
int p[maxn];
 
ll pref[maxn], suf[maxn];
 
long long delivery(int N, int K, int L, int positions[])
{
	int n = N, k = K;
	for (int i = 1; i <= n; i++)
		p[i] = positions[i-1];
 
	pref[1] = 2ll*p[1];
	for (int i = 2; i <= n; i++)
		pref[i] = 2ll*p[i] + pref[max(0, i-k)];

	suf[n] = 2ll*(L-p[n]);
	for (int i = n-1; i >= 1; i--)
		suf[i] = 2ll*(L-p[i]) + suf[min(n+1, i+k)];

	ll ans = min(pref[n], suf[1]);
	if (k == n) ans = min(ans, 1ll*L);
	
	for (int i = 1; i < n; i++)
		ans = min(ans, pref[i]+suf[i+1]);

	for (int i = 1; i <= n-k; i++)
		ans = min(ans, pref[i] + 1ll*L + suf[i+k+1]);
 
	return ans;
}
