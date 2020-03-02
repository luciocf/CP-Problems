// COCI 2019/2020 - Nivelle
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
char a[maxn];

vector<int> pos[27];

bool good(int a, int b, int c, int d)
{
	return c*b < a*d;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf(" %c", &a[i]);

	for (int i = n; i >= 1; i--)
		pos[(int)(a[i]-'a')].push_back(i);

	int opt_a = 1, opt_b = 1;
	int opt_l = 1, opt_r = 1;

	for (int i = 1; i <= n; i++)
	{
		vector<int> p;

		for (int j = 0; j < 26; j++)
			if (pos[j].size() > 0)
				p.push_back(pos[j].back());

		sort(p.begin(), p.end());
		p.push_back(n+1);

		for (int j = 1; j < p.size(); j++)
		{
			if (good(opt_a, opt_b, j, p[j]-i))
			{
				opt_a = j, opt_b = p[j]-i;
				opt_l = i, opt_r = p[j]-1;
			}
		}

		pos[(int)(a[i]-'a')].pop_back();
	}

	printf("%d %d\n", opt_l, opt_r);
}
