// USACO Gold US Open 2016 - Splitting the Field
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4+10;
const int inf = 1e9+10;

typedef long long ll;

struct pt
{
	int x, y;
} P[maxn];

int n;
int pref[4][maxn], suf[4][maxn];

ll area;

bool comp1(pt a, pt b) {return a.x < b.x;}

bool comp2(pt a, pt b) {return a.y < b.y;}

ll solve1(void)
{
	sort(P+1, P+n+1, comp1);

	for (int i = 0; i <= n+1; i++)
	{
		pref[0][i] = suf[0][i] = pref[2][i] = suf[2][i] = inf;
		pref[1][i] = suf[1][i] = pref[3][i] = suf[3][i] = 0;
	}

	for (int i = 1; i <= n; i++)
	{
		pref[0][i] = min(pref[0][i-1], P[i].x);
		pref[1][i] = max(pref[1][i-1], P[i].x);

		pref[2][i] = min(pref[2][i-1], P[i].y);
		pref[3][i] = max(pref[3][i-1], P[i].y);
	}

	suf[0][n+1] = inf;
	suf[2][n+1] = inf;

	for (int i = n; i >= 1; i--)
	{
		suf[0][i] = min(suf[0][i+1], P[i].x);
		suf[1][i] = max(suf[1][i+1], P[i].x);

		suf[2][i] = min(suf[2][i+1], P[i].y);
		suf[3][i] = max(suf[3][i+1], P[i].y);
	}

	ll menor = 1ll*inf*inf;

	for (int i = 1; i <= n; i++)
	{
		ll area1 = 1ll*(pref[1][i]-pref[0][i])*(pref[3][i]-pref[2][i]);
		ll area2 = 1ll*(suf[1][i+1]-suf[0][i+1])*(suf[3][i+1]-suf[2][i+1]);

		menor = min(menor, area1+area2);
	}

	return menor;
}

ll solve2(void)
{
	sort(P+1, P+n+1, comp2);

	for (int i = 0; i <= n+1; i++)
	{
		pref[0][i] = suf[0][i] = pref[2][i] = suf[2][i] = inf;
		pref[1][i] = suf[1][i] = pref[3][i] = suf[3][i] = 0;
	}

	for (int i = 1; i <= n; i++)
	{
		pref[0][i] = min(pref[0][i-1], P[i].x);
		pref[1][i] = max(pref[1][i-1], P[i].x);

		pref[2][i] = min(pref[2][i-1], P[i].y);
		pref[3][i] = max(pref[3][i-1], P[i].y);
	}

	suf[0][n+1] = inf;
	suf[2][n+1] = inf;

	for (int i = n; i >= 1; i--)
	{
		suf[0][i] = min(suf[0][i+1], P[i].x);
		suf[1][i] = max(suf[1][i+1], P[i].x);

		suf[2][i] = min(suf[2][i+1], P[i].y);
		suf[3][i] = max(suf[3][i+1], P[i].y);
	}

	ll menor = 1ll*inf*inf;

	for (int i = 1; i <= n; i++)
	{
		ll area1 = 1ll*(pref[1][i]-pref[0][i])*(pref[3][i]-pref[2][i]);
		ll area2 = 1ll*(suf[1][i+1]-suf[0][i+1])*(suf[3][i+1]-suf[2][i+1]);

		menor = min(menor, area1+area2);
	}

	return menor;
}

int main(void)
{
	FILE *fin = fopen("split.in", "r");
	FILE *fout = fopen("split.out", "w");

	fscanf(fin, "%d", &n);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d %d", &P[i].x, &P[i].y);

	int menorX = inf, maiorX = 0, menorY = inf, maiorY = 0;
	for (int i = 1; i <= n; i++)
	{
		menorX = min(menorX, P[i].x);
		maiorX = max(maiorX, P[i].x);

		menorY = min(menorY, P[i].y);
		maiorY = max(maiorY, P[i].y);
	}

	area = 1ll*(maiorX-menorX)*(maiorY-menorY);

	ll a1 = solve1();
	ll a2 = solve2();

	fprintf(fout, "%lld\n", area-min(a1,a2));
}
