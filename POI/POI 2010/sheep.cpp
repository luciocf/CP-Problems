// POI 2010 - Sheep
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 610;
const int maxk = 2e4+10;

int n, k, mod;

int S[maxn][maxn], T[maxn][maxn];

int ans[maxn][maxn];

bool isIn[maxn][maxn];

pii env[maxn], pt[maxk];

ll cross(pii a, pii b)
{
	return 1ll*a.ff*b.ss - 1ll*a.ss*b.ff;
}

int sign(ll x)
{
	if (x == 0) return 0;
	return (x > 0 ? 1 : -1);
}

bool ok(pii P, pii A, pii B, pii C, int pt1, int pt2, int pt3)
{
	P.ff -= C.ff, P.ss -= C.ss;
	A.ff -= C.ff, A.ss -= C.ss;
	B.ff -= C.ff, B.ss -= C.ss;

	ll c1 = cross(P, A), c2 = cross(P, B);

	if (!c1) isIn[pt1][pt2] = true;
	if (!c2) isIn[pt1][pt3] = true;

	if (!c2) return 0;

	return (sign(c1) != sign(c2) ? 1 : 0);
}

bool test(int P, int A, int B, int i)
{
	return ok(env[P], env[A], env[B], pt[i], P, A, B);
}

void calc_T(void)
{
	for (int i = 0; i < k; i++)
	{
		int best;
		for (int j = 0; j < n; j++)
			if (test(0, j, (j+1)%n, i))
				best = j;

		T[0][best]++;
		
		for (int P = 1; P < n; P++)
		{
			while (best == P || !test(P, best, (best+1)%n, i))
				best = (best+1)%n;

			T[P][best]++;
		}
	}
}

void calc_S(void)
{
	for (int L = 0; L < n; L++)
	{
		S[L][(L+2)%n] = T[L][(L+1)%n];

		for (int R = L+3; R < n; R++)
			S[L][R] = S[L][R-1] + T[L][R-1];

		for (int R = 0; R < L; R++)
			S[L][R] = S[L][(R-1+n)%n] + T[L][(R-1+n)%n];
	}
}

int main(void)
{
	scanf("%d %d %d", &n, &k, &mod);

	for (int i = 0; i < n; i++)
		scanf("%d %d", &env[i].ff, &env[i].ss);

	for (int i = 0; i < k; i++)
		scanf("%d %d", &pt[i].ff, &pt[i].ss);

	calc_T(); calc_S();

	for (int L = 0; L < n; L++)
	{
		if ((k - S[L][L+1] - S[L+1][L+2] - S[L+2][L])%2 == 0)
			ans[L][L+2] = 1;

		ans[L][L+1] = 1;
	}

	for (int x = 3; x < n; x++)
	{
		for (int L = 0; L+x < n; L++)
		{
			int R = L+x;

			for (int P = L+1; P < R; P++)
			{
				if (isIn[L][P] || isIn[P][R] || isIn[R][L]) continue;
				if ((k - S[L][P] - S[P][R] - S[R][L])%2) continue;

				ll tot = (1ll*ans[L][P]*ans[P][R]);

				ans[L][R] = (ans[L][R] + tot)%mod;
			}
		}
	}

	printf("%d\n", ans[0][n-1]);
}

/*
	* bounds (maxn)
	* long long
	* all variables reset?
	* check if indexing is ok
	* off by one? (n-i+1) or (n-i)?
	* edge cases (n=0, n=1, n < 0, n=maxn)
*/
