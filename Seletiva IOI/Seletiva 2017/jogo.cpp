// Seletiva IOI 2017 - Jogo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e3+10;

const long long inf = 1e18+10;

typedef long long ll;

struct pt
{
	int x, y, v;
};

pt P[maxn], aux[maxn];

pt pivot;

bool comp(pt a, pt b)
{
	return a.x < b.x;
}

bool igual(pt a, pt b)
{
	return (a.x == b.x && a.y == b.y);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d %d", &P[i].x, &P[i].y, &P[i].v);
		aux[i] = {P[i].x, P[i].y, P[i].v};
	}

	sort(P+1, P+n+1, comp);
	sort(aux+1, aux+n+1, comp);

	ll ans_global = -inf;
	for (int i = 1; i <= n; i++)
	{
		pivot = P[i];

		unordered_map<double, ll> M;

		ll ans = -inf, add = 0LL;
		for (int j = 1; j <= n; j++)
		{
			if (aux[j].x < pivot.x) continue;

			if (igual(aux[j], pivot) == 0)
			{
				add += (ll)aux[j].v;
				continue;
			}

			double m1 = aux[j].y-pivot.y;
			double m2 = aux[j].x-pivot.x;
			double temp = (m2 ? m1/m2 : inf);

			M[temp] += (ll)aux[j].v;
			while (j < n && igual(aux[j], aux[j+1]))
				M[temp] += (ll)aux[++j].v;

			ans = max(ans, add+M[temp]);
		}

		ans_global = max(ans, ans_global);
	}

	printf("%lld\n", ans_global);
}