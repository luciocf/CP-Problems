// Codeforces 191E - Thwarting Demonstrations
// Lúcio Cardoso

// Solution is the same as in editorial, using policy-based tree

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;

typedef tree<
pair<ll, int>,
null_type,
less<pair<ll, int>>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int maxn = 1e5+10;

int n;
ll k;

int a[maxn];

bool ok(ll x)
{
	ordered_set st;

	ll ans = 0;
	ll qtd = 0, s = 0;

	st.insert({0, 0});

	for (int i = 1; i <= n; i++)
	{
		s += 1ll*a[i];

		ans += 1ll*(1ll*i-1ll*st.order_of_key({s-x, 0}));

		st.insert({s, i});
	}

	return ans >= (1ll*n*(n+1))/2ll - k+1ll;
}

int main(void)
{
	scanf("%d %lld", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	ll ini = -1e16, fim = 1e16, ans;

	while (ini <= fim)
	{
		ll mid = (ini+fim)/2ll;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	printf("%lld\n", ans);
}
