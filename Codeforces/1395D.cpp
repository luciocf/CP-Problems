// Codeforces 1395D - Boboniu Chats with Du
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int a[maxn];
ll prefA[maxn], prefB[maxn];

int main(void)
{
	int n, d, m;
	scanf("%d %d %d", &n, &d, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	ll ans = 0;

	vector<int> A, B;

	for (int i = 1; i <= n; i++)
	{
		if (a[i] <= m) A.push_back(a[i]);
		else B.push_back(a[i]);
	}

	sort(A.begin(), A.end(), greater<int>());
	sort(B.begin(), B.end(), greater<int>());

	if (A.size()) prefA[0] = A[0];
	for (int i = 1; i < A.size(); i++)
		prefA[i] = prefA[i-1] + 1ll*A[i];

	if (B.size()) prefB[0] = B[0];
	for (int i = 1; i < B.size(); i++)
		prefB[i] = prefB[i-1] + 1ll*B[i];

	for (int k = 0; k <= B.size(); k++)
	{
		if (k > 0 && 1ll*(k-1)*(d+1) >= 1ll*n) continue;
		if (1ll*A.size() + 1ll*k*(d+1) < 1ll*n) continue;

		ll aux = (k == 0 ? 0 : prefB[k-1]);

		ll x = (k == 0 ? n : 1ll*n-(1ll*(k-1)*(d+1)+1ll));
		x = min(x, (ll)A.size());

		if (x > 0) aux += 1ll*prefA[x-1];

		ans = max(ans, aux);
	}

	printf("%lld\n", ans);
}
