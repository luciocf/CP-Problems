// CSES 1164 - Room Allocation
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e5+10;

int n;
int a[maxn], b[maxn];

vector<int> in[maxn], out[maxn];

int ans[maxn];

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[a[i]] = mp[b[i]] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
	{
		in[mp[a[i]]].push_back(i);
		out[mp[b[i]]].push_back(i);
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i], &b[i]);

	compress();

	set<int> st;
	for (int i = 1; i <= n; i++)
		st.insert(i);

	for (int i = 1; i <= 2*n; i++)
	{
		for (auto ind: in[i])
		{
			ans[ind] = *st.begin();
			st.erase(st.begin());
		}

		for (auto ind: out[i])
			st.insert(ans[ind]);
	}

	printf("%d\n", *max_element(ans+1, ans+n+1));
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
