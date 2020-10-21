// CSES 1091 - Concert Tickets
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	multiset<int> st;

	for (int i = 1; i <= n; i++)
	{
		int v;
		scanf("%d", &v);

		st.insert(v);
	}

	for (int i = 1; i <= m; i++)
	{
		int v;
		scanf("%d", &v);

		auto it = st.upper_bound(v);

		if (it == st.begin()) printf("-1\n");
		else
		{
			--it;

			printf("%d\n", *it);
			st.erase(it);
		}
	}
}
