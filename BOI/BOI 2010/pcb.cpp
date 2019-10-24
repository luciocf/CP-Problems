// BOI 2010 - Printed Circuit Board
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef pair<int, int> pii;

pii a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i].first, &a[i].second);

	sort(a+1, a+n+1);

	multiset<int> st;

	for (int i = 1; i <= n; i++)
	{
		auto it = st.lower_bound(a[i].second);

		if (it != st.begin())
			st.erase(--it);

		st.insert(a[i].second);
	}

	printf("%d\n", st.size());
}
