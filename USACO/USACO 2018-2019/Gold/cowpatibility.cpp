// USACO 2018-2019 - Cowpatibility
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4+10;
const int maxm = 1e6+10;

typedef long long ll;

int a[maxn][5];

map<int, int> mp1;
map<tuple<int, int>, int> mp2;
map<tuple<int, int, int>, int> mp3;
map<tuple<int, int, int, int>, int> mp4;
map<tuple<int, int, int, int, int>, int> mp5;

int main(void)
{
	FILE *fin = fopen("cowpatibility.in", "r");
	FILE *fout = fopen("cowpatibility.out", "w");

	int n;
	fscanf(fin, "%d", &n);

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 5; j++)
			fscanf(fin, "%d", &a[i][j]);

	for (int i = 1; i <= n; i++)
		sort(a[i], a[i]+5);

	for (int i = 1; i <= n; i++)
	{
		for (int mask = 1; mask < (1<<5); mask++)
		{
			int num[5], tam = -1;

			for (int j = 0; j < 5; j++)
				if (mask&(1<<j))
					num[++tam] = a[i][j];

			tam++;

			if (tam == 1)
			{
				int a1 = num[0];
				mp1[a1]++;
			}
			else if (tam == 2)
			{
				int a1 = num[0], a2 = num[1];
				mp2[make_tuple(a1, a2)]++;
			}
			else if (tam == 3)
			{
				int a1 = num[0], a2 = num[1], a3 = num[2];
				mp3[make_tuple(a1, a2, a3)]++;
			}
			else if (tam == 4)
			{
				int a1 = num[0], a2 = num[1], a3 = num[2], a4 = num[3];
				mp4[make_tuple(a1, a2, a3, a4)]++;
			}
			else
			{
				int a1 = num[0], a2 = num[1], a3 = num[2], a4 = num[3], a5 = num[4];
				mp5[make_tuple(a1, a2, a3, a4, a5)]++;
			}
		}
	}

	ll ans = 1ll*n*n;

	for (int i = 1; i <= n; i++)
	{	
		ll aux = 0;

		for (int mask = 1; mask < (1<<5); mask++)
		{
			int num[5], tam = -1;

			for (int j = 0; j < 5; j++)
				if (mask&(1<<j))
					num[++tam] = a[i][j];

			tam++;

			if (tam == 1)
			{
				int a1 = num[0];
				aux += 1ll*mp1[a1];
			}
			else if (tam == 2)
			{
				int a1 = num[0], a2 = num[1];
				aux -= 1ll*mp2[make_tuple(a1, a2)];
			}
			else if (tam == 3)
			{
				int a1 = num[0], a2 = num[1], a3 = num[2];
				aux += 1ll*mp3[make_tuple(a1, a2, a3)];
			}
			else if (tam == 4)
			{
				int a1 = num[0], a2 = num[1], a3 = num[2], a4 = num[3];
				aux -= 1ll*mp4[make_tuple(a1, a2, a3, a4)];
			}
			else
			{
				int a1 = num[0], a2 = num[1], a3 = num[2], a4 = num[3], a5 = num[4];
				aux += 1ll*mp5[make_tuple(a1, a2, a3, a4, a5)];
			}
		}

		ans -= aux;
	}

	fprintf(fout, "%lld\n", ans/2);
}
