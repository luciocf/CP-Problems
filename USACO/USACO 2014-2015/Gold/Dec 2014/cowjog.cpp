// USACO Gold Dec 2014 - Cowjog
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;
 
const int maxn = 1e5+10;

ll a[maxn];
 
int main(void)
{
	freopen("cowjog.in", "r", stdin);
	freopen("cowjog.out", "w", stdout);
	
	int n, T;
	scanf("%d %d", &n, &T);
 
	for (int i = 1; i <= n; i++)
	{
		int p, v;
		scanf("%d %d", &p, &v);

		a[i] = 1ll*p + 1ll*T*v;
	}
 
	multiset<ll> st;
 
	for (int i = 1; i <= n; i++)
	{
		auto pos = st.lower_bound(a[i]);
 
		if (pos == st.begin()) st.insert(a[i]);
		else
		{
			st.erase(--pos);
			st.insert(a[i]);
		}
	}	
 
	printf("%d\n", st.size());
}
