// CEOI 2010 - A Huge Tower
// Lúcio Cardoso

// Solution:

// 1. Let P(i) be the number that comes before i in any tower. Also, let Q(i) be the amount
// of indices j such that i != j, A[i] >= A[j] and A[j]+d >= A[i].

// 2. We will chose a subset of indices S = {p_1, p_2, ..., p_k} such that P(p_i) for every 1 <= i <= k
// is smaller than p_i, and choose the respective indices that come before them. After that, the order of the
// remaining n-k indices in the tower is defined (they have to be sorted increasingly).

// 3. Thus, the answer is (Q(1)+1)*(Q(2)+1)*...*(Q(n)+1). We can find Q(i) in O(n log n) by sorting the
// array.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;
const int mod = 1e9+9;

int a[maxn];

int main(void)
{
	int n, d;
	scanf("%d %d", &n, &d);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	int ans = 1, ptr = 1;

	for (int i = 1; i <= n; i++)
	{
		while (ptr < i && a[ptr]+d < a[i])
			ptr++;

		ans = (1ll*ans*(i-ptr+1))%mod;
	}

	printf("%d\n", ans);
}
