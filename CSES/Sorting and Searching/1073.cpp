// CSES 1073 - Towers
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n;
	scanf("%d", &n);

	multiset<int> st;

	for (int i = 1; i <= n; i++)
	{
		int v;
		scanf("%d", &v);

		auto it = st.upper_bound(v);

		if (it != st.end())
			st.erase(it);
		
		st.insert(v);
	}	

	printf("%d\n", st.size());
}
