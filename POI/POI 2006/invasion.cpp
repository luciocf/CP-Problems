// POI 2006 - The Invasion
// Lúcio Cardoso

// Solution:

// 1. If we fix a triangle in the polygon, its 3 sides will divide the polygon into 3 sections outside
// the triangle, each one formed by consecutive points in the polygon. If those sections are A, B and C,
// the answer for such a fixed triangle is equal to S - S(A) - S(B) - S(c), where S is the sum of all values
// and and S(A), S(B), S(C) is the sum of values inside each section.

// 2. From that observation, we can reduce the problem to counting the sum of values
// inside each section made by a range [l, r] of consecutive points in the polygon.
// We can reduce that even further by noticing we can calculate it with DP: Let S[l][r] be the sum
// of a section with points in range [l, r]. Then, S[l][r+1] = S[l][r] + T[l][r], where T[l][r]
// is the sum of the values inside the triangle with one vertex in l and the remaining vertices
// in l and (l+1).

// 3. Now, the problem is to find the sum of values inside each triangle with vertices in points
// (a, b, b+1). If we fix a point A from the polygon, it will form (n-2) disjoint triangles such that
// their bases are formed by two consecutive points. Thus, any factory point will belong to exactly one of
// these triangles, so we can find in which of them factory P resides using Binary Search and them sum
// P's value to said triangle:

// (Suppose the point A is fixed)
// If the points in the base of a triangle are B and C, we can check if (A-P) x (B-P) has a different sign
// than (A-P) x (C-P). If so, P resides in triangle (A, B, C).
// Otherwise, if the sign of those cross products are equal, search in the left/right if the sign
// is negative/positive, respectively.
// NOTE: We need to handle an edge case where a factory is in a segment of a triangle. Check the code
// for details.

// Thus, we can find the sum in each triangle in O(nm * log n), calculate S[l][r] in O(n^2) and
// brute force all possible triangles to find the answer in O(n^3). Final complexity is then
// O(nm * log n + n^3).

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 610;
const int maxm = 1e4+10;
const int inf = 1e9+10;

int n, m;

int T[maxn][maxn], S[maxn][maxn];

int val[maxm];

pii V[maxn], pt[maxm];

ll cross(pii a, pii b)
{
	return (1ll*a.ff*b.ss - 1ll*a.ss*b.ff);
}

int sign(ll v)
{
	if (v == 0) return 0;
	return (v < 0 ? -1 : 1);
}

int test(int A, int B, int C, pii P)
{
	pii pa = V[A], pb = V[B], pc = V[C];

	pa.ff -= P.ff, pa.ss -= P.ss;
	pb.ff -= P.ff, pb.ss -= P.ss;
	pc.ff -= P.ff, pc.ss -= P.ss;
	
	// if a factory is in this segment, consider it inside the triangle in the left
	if (!cross(pa, pc)) return -1;

	if (sign(cross(pa, pb)) != sign(cross(pa, pc))) return 2;
	
	return sign(cross(pa, pb));
}

int busca(int A, pii P)
{
	int ini = 1, fim = n-2;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		int p1 = (A+mid)%n, p2 = (A+mid+1)%n;

		int x = test(A, p1, p2, P);

		if (x == 2) return p1;
		else if (x == -1) ini = mid+1;
		else fim = mid-1;
	}

	return -1;
}

void calc_T(void)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int x = busca(i, pt[j]);

			if (x != -1)
				T[i][x] += val[j];
		}
	}
}

void calc_S(void)
{
	for (int l = 0; l < n; l++)
	{
		S[l][(l+2)%n] = T[l][(l+1)%n];

		for (int r = l+3; r < n; r++)
			S[l][r] = S[l][r-1] + T[l][r-1];

		for (int r = 0; r < l; r++)
			S[l][r] = S[l][(r-1+n)%n] + T[l][(r-1+n)%n];
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d %d", &V[i].ff, &V[i].ss);

	scanf("%d", &m);

	int soma = 0;

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &pt[i].ff, &pt[i].ss, &val[i]);

		soma += val[i];
	}

	calc_T(); calc_S();

	int ans = -inf;

	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			for (int k = j+1; k < n; k++)
			{
				int cost = soma - S[i][j] - S[j][k] - S[k][i];

				ans = max(ans, cost);
			}
		}
	}

	printf("%d\n", ans);
}

/*
	* bounds (maxn)
	* long long
	* all variables reset?
	* check if indexing is ok
	* off by one? (n-i+1) or (n-i)?
	* edge cases (n=0, n=1, n < 0, n=maxn)
*/
