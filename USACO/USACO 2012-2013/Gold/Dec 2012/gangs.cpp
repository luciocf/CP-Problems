// USACO 2012/2013 Gold - Gangs of Instanbull/Cowstantinople
// Lúcio Cardoso

// Solution:

// 1. Let's fix the amount of 1s that are going to remain in the end. Notice it's always optimal for them to be
// in a suffix (the editorial mentions that in more detail), i.e, if x cows from gang 1 remain, these cows
// are going to be in the suffix [n-x+1, n]

// 2. Now, we need to make sure that no gang is going to be in control before the suffix of 1s, and find
// the lexicographically smallest sequence that achieves that. We'll use the following algorithm:

//	- Let l = n-x (the last position out of the suffix mentioned above). Suppose we're inserting the cow in position i.
//	- When inserting the cow in position i, let the amount of cows in the current active gang be y.
//	- The gang of cow i can be the smallest gang iff 2*(largest_gang_frequency) <= l-i + y
//	- Otherwise, the gang of cow i has to be the gang of largest frequency.

// We can use a set to find the gang of largest frequency at any point in the algorithm. Overall complexity
// is O(n^2 * log n)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;

typedef pair<int, int> pii;

int a[maxn], fq[maxn];

int aux[maxn];

int main(void)
{
	freopen("gangs.in", "r", stdin); freopen("gangs.out", "w", stdout);

	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
		scanf("%d", &a[i]);

	int ans = 0;

	for (int mx = a[1]; mx >= 1; mx--)
	{
		int l = n-mx+1;

		for (int i = 1; i <= m; i++)
			fq[i] = a[i];

		for (int i = l; i <= n; i++)
			aux[i] = 1, --fq[1];

		set<pii> st;
		for (int i = 1; i <= m; i++)
			st.insert({-fq[i], i});

		int resta = l-1, ptr = 1, ativo = 0, last = 0;

		for (int i = 1; i < l; i++)
		{
			while (!fq[ptr])
				++ptr;

			int maior = -(st.begin()->first);
			int ind_maior = st.begin()->second;

			int ativo2 = ativo + (ativo == 0 || last == ptr);

			if (maior > resta-1-maior+ativo2)
			{
				st.erase({-fq[ind_maior], ind_maior});
				fq[ind_maior]--;
				st.insert({-fq[ind_maior], ind_maior});

				aux[i] = ind_maior;

				if (ativo == 0 || last == ind_maior) ativo++, last = ind_maior;
				else ativo--;
			}
			else
			{
				st.erase({-fq[ptr], ptr});
				fq[ptr]--;
				if (fq[ptr] > 0) st.insert({-fq[ptr], ptr});

				aux[i] = ptr;

				if (ativo == 0 || last == ptr) ativo++, last = ptr;
				else ativo--;
			}

			resta--;
		}

		if (ativo) continue;

		printf("YES\n%d\n", mx);
		for (int i = 1; i <= n; i++)
			printf("%d\n", aux[i]);

		return 0;
	}

	printf("NO\n");
}
