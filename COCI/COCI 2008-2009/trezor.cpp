// COCI 2008/2009 - Trezor
// Lúcio Cardoso

// Solution is the same as in: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2009/contest4_solutions

#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e3+10;

typedef long long ll;

int tot_a[maxn], tot_b[maxn];
int tot[maxn];

vector<int> get(int x)
{
	vector<int> p;

	for (int i = 2; i*i <= x; i++)
	{
		if (x%i) continue;

		p.push_back(i);

		while (x%i == 0)
			x /= i;
	}

	if (x > 1) p.push_back(x);

	return p;
}

int main(void)
{
	int a, b, l;
	scanf("%d %d %d", &a, &b, &l);

	for (int i = 0; i <= a+b; i++)
	{
		vector<int> p = get(i);
		int sz = p.size();

		for (int mask = 1; mask < (1<<sz); mask++)
		{
			int qtd = 0, prod = 1;
			for (int j = 0; j < sz; j++)
				if (mask&(1<<j))
					++qtd, prod *= p[j];

			if (qtd%2) tot_a[i] += l/prod;
			else tot_a[i] -= l/prod;
		}

		p = get(b-i+a);
		sz = p.size();

		for (int mask = 1; mask < (1<<sz); mask++)
		{
			int qtd = 0, prod = 1;
			for (int j = 0; j < sz; j++)
				if (mask&(1<<j))
					++qtd, prod *= p[j];

			if (qtd%2) tot_b[i] += l/prod;
			else tot_b[i] -= l/prod;
		}

		tot_a[i] = l-tot_a[i];
		tot_b[i] = l-tot_b[i];

		if (i == 0) tot_a[i] = 1;
		if (b-i+a == 0) tot_b[i] = 1;

		vector<int> aux = get(i);

		for (auto x: aux)
			p.push_back(x);

		sort(p.begin(), p.end()); p.erase(unique(p.begin(), p.end()), p.end());
		sz = p.size();


		for (int mask = 1; mask < (1<<sz); mask++)
		{
			int qtd = 0, prod = 1;
			for (int j = 0; j < sz; j++)
				if (mask&(1<<j))
					++qtd, prod *= p[j];

			if (qtd%2) tot[i] += l/prod;
			else tot[i] -= l/prod;
		}

		tot[i] = l-tot[i];

		if (i == 0 || b-i+a == 0) tot[i] = 1;
	}

	ll ans1 = 0, ans2 = 0;

	for (int i = 0; i <= b+a; i++)
	{
		ans1 += 1ll*(tot_a[i]-tot[i]);
		ans1 += 1ll*(tot_b[i]-tot[i]);

		ans2 += 1ll*tot[i];
	}

	printf("%lld\n%lld\n%lld\n", 1ll*l*(a+b+1)-ans1-ans2, ans1, ans2);
}
