// IOI 2007 - Pairs
// Lúcio Cardoso

// Solution:

// 1. Sort points by their x coordinate. While iterating through all points in order
// (suppose the current index is i), keep a pointer ptr that indicates the leftmost point such that
// P[i].x - P[ptr].x <= D.

// 2. Let i >= j. Since we ordered the points by the x-coordinate, there are four cases:

//	* P[i].y >= P[j].y and P[i].z >= P[j].z
//	* P[i].y >= P[j].y and P[i].z < P[j].z
//	* P[i].y < P[j].y and P[i].z >= P[j].z
//	* P[i].y < P[j].y and P[i].z < P[j].z

// Let's find all pairs conrresponding to the first cases (the other cases are analogous).
// If the pair (i, j) is a solution, then:

// d(i, j) = (P[i].x - P[j].x) + (P[i].y - P[j].y) + (P[i].z - P[j].z) <= D ->
// P[j].x + P[j].y + P[j].z >= P[i].x + P[i].y + P[i].z - D (*).

// 3. Notice that we can keep a 2D-BIT
// which stores points of the form (P[j].y, P[j].x + P[j].y + P[j].z) to query the amount of points
// such that (*) is true and that P[j].y <= P[i].y. However, we would overcount the cases where
// P[j].y <= P[i].y, P[j].z > P[i].z and (*) applies.

// So, let's keep another 2D BIT to store points of the form (P[j].z, P[j].x + P[j].y + P[j].z).
// This allows us to remove the overcounted part above. However, we would be undercounting the pairs
// such that P[j].y >= P[i].y and P[j].z >= P[i].z.

// 4. Going back to (*), the condition is the same as:
// (P[i].x-P[j].x) <= D - (P[i].y - P[j].y) - (P[i].z - P[j].z).

// Since by (1) P[i].x-P[j].x <= D, the condition that P[j].y >= P[i].y and P[j].z >= P[i].z is enough
// to satisfy (*). So, to remove the undercounted part in (3), we can keep another 2D BIT that stores points
// of the form (P[j].y, P[j].z). This allows us to remove the undercounted parts, and therefore,
// we've counted all points j such that the first case above is true and d(P[i]-P[j]) <= D.

// The other 3 cases are very similar. The overall complexity is O(N log^2 M).

#include <bits/stdc++.h>
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 4e5+10;
const int add1 = 2e5+10;

const int maxn2 = 455;
const int add2 = 230;

struct Pt
{
	int x, y, z;
} p[maxn];

bool comp(Pt a, Pt b)
{
	return a.x < b.x;
}
 
pii a[maxn];
 
int bit_1d[2][maxn];
int bit_2d[3][455][455];
 
void upd_1d(int x, int v, int q)
{
	if (!x) return;
 
	for (; x < maxn; x += (x&-x))
		bit_1d[q][x] += v;
}
 
int soma_1d(int x, int q)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit_1d[q][x];
	return ans;
}

void upd_2d(int x, int y, int v, int q)
{
	for (int i = x; i < maxn2; i += (i&-i))
		for (int j = y; j < maxn2; j += (j&-j))
			bit_2d[q][i][j] += v;
}

int soma_2d(int x, int y, int q)
{
	int ans = 0;
	for (int i = x; i > 0; i -= (i&-i))
		for (int j = y; j > 0; j -= (j&-j))
			ans += bit_2d[q][i][j];
	return ans;
}
 
long long solve_1(void)
{
	int n, d, m;
	scanf("%d %d %d", &n, &d, &m);
 
	int x[n+1];
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &x[i]);
 
	sort(x+1, x+n+1);
 
	long long ans = 0;
 
	int l = 1, r = 2;
	while (l <= n && r <= n)
	{
		if (l != r && x[r]-x[l] <= d)
			ans += 1ll*(r-l);
 
		if (x[r]-x[l] <= d) r++;
		else l++;
	}
 
	return ans;
}
 
long long solve_2(void)
{
	int n, D, m;
	scanf("%d %d %d", &n, &D, &m);
 
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i].first, &a[i].second);
 
	sort(a+1, a+n+1);
 
	long long ans = 0;
	int ptr = 1;
 
	upd_1d(a[1].first+a[1].second+add1, 1, 0);
	upd_1d(a[1].second+add1, 1, 1);
 
	for (int i = 2; i <= n; i++)
	{
		while (ptr < i && a[i].first-a[ptr].first > D)
		{
			upd_1d(a[ptr].first+a[ptr].second+add1, -1, 0);
			upd_1d(a[ptr].second+add1, -1, 1);
 
			ptr++;
		}
 
		if (i != ptr)
		{
			ans += 1ll*(soma_1d(maxn-1, 0)-soma_1d(a[i].first+a[i].second-D-1+add1, 0));
			ans -= 1ll*(soma_1d(maxn-1, 1)-soma_1d(a[i].second+add1, 1));
		}
 
		upd_1d(a[i].first+a[i].second+add1, 1, 0);
		upd_1d(a[i].second+add1, 1, 1);
	}
 
	memset(bit_1d, 0, sizeof bit_1d);
 
	ptr = 1;
 
	upd_1d(a[1].first-a[1].second+add1, 1, 0);
	upd_1d(a[1].second+add1, 1, 1);
 
	for (int i = 2; i <= n; i++)
	{
		while (ptr < i && a[i].first-a[ptr].first > D)
		{
			upd_1d(a[ptr].first-a[ptr].second+add1, -1, 0);
			upd_1d(a[ptr].second+add1, -1, 1);
 
			ptr++;
		}
 
		if (i != ptr)
		{
			ans += 1ll*(soma_1d(maxn-1, 0)-soma_1d(a[i].first-a[i].second-D-1+add1, 0));
			ans -= 1ll*soma_1d(a[i].second+add1, 1);
		}
 
		upd_1d(a[i].first-a[i].second+add1, 1, 0);
		upd_1d(a[i].second+add1, 1, 1);
	}
 
	return ans;
}

int get_rect(int x1, int y1, int x2, int y2, int q)
{
	return (soma_2d(x2, y2, q)-soma_2d(x1-1, y2, q)-soma_2d(x2, y1-1, q)+soma_2d(x1-1, y1-1, q));
}

long long solve_3(void)
{
	int n, D, m;
	scanf("%d %d %d", &n, &D, &m);
 
	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);

	sort(p+1, p+n+1, comp);

	long long ans = 0;
	int ptr = 1;

	upd_2d(p[1].y+add2, p[1].x+p[1].y+p[1].z+add2, 1, 0);
	upd_2d(p[1].z+add2, p[1].x+p[1].y+p[1].z+add2, 1, 1);
	upd_2d(p[1].y+add2, p[1].z+add2, 1, 2);

	for (int i = 2; i <= n; i++)
	{
		while (ptr < i && p[i].x-p[ptr].x > D)
		{
			upd_2d(p[ptr].y+add2, p[ptr].x+p[ptr].y+p[ptr].z+add2, -1, 0);
			upd_2d(p[ptr].z+add2, p[ptr].x+p[ptr].y+p[ptr].z+add2, -1, 1);
			upd_2d(p[ptr].y+add2, p[ptr].z+add2, -1, 2);
 
			ptr++;
		}

		if (i != ptr)
		{
			ans += 1ll*get_rect(1+add2, p[i].x+p[i].y+p[i].z-D+add2, p[i].y+add2, maxn2-1, 0);
			ans -= 1ll*get_rect(p[i].z+1+add2, p[i].x+p[i].y+p[i].z-D+add2, maxn2-1, maxn2-1, 1);
			ans += 1ll*get_rect(p[i].y+1+add2, p[i].z+1+add2, maxn2-1, maxn2-1, 2);
		}

		upd_2d(p[i].y+add2, p[i].x+p[i].y+p[i].z+add2, 1, 0);
		upd_2d(p[i].z+add2, p[i].x+p[i].y+p[i].z+add2, 1, 1);
		upd_2d(p[i].y+add2, p[i].z+add2, 1, 2);
	}

	memset(bit_2d, 0, sizeof bit_2d);

	ptr = 1;

	upd_2d(p[1].y+add2, p[1].x+p[1].y-p[1].z+add2, 1, 0);
	upd_2d(p[1].z+add2, p[1].x+p[1].y-p[1].z+add2, 1, 1);
	upd_2d(p[1].y+add2, p[1].z+add2, 1, 2);

	for (int i = 2; i <= n; i++)
	{
		while (ptr < i && p[i].x-p[ptr].x > D)
		{
			upd_2d(p[ptr].y+add2, p[ptr].x+p[ptr].y-p[ptr].z+add2, -1, 0);
			upd_2d(p[ptr].z+add2, p[ptr].x+p[ptr].y-p[ptr].z+add2, -1, 1);
			upd_2d(p[ptr].y+add2, p[ptr].z+add2, -1, 2);
 
			ptr++;
		}

		if (i != ptr)
		{
			ans += 1ll*get_rect(1+add2, p[i].x+p[i].y-p[i].z-D+add2, p[i].y+add2, maxn2-1, 0);
			ans -= 1ll*get_rect(1+add2, p[i].x+p[i].y-p[i].z-D+add2, p[i].z+add2, maxn2-1, 1);
			ans += 1ll*get_rect(p[i].y+1+add2, 1+add2, maxn2-1, p[i].z+add2, 2);
		}

		upd_2d(p[i].y+add2, p[i].x+p[i].y-p[i].z+add2, 1, 0);
		upd_2d(p[i].z+add2, p[i].x+p[i].y-p[i].z+add2, 1, 1);
		upd_2d(p[i].y+add2, p[i].z+add2, 1, 2);
	}

	memset(bit_2d, 0, sizeof bit_2d);

	ptr = 1;

	upd_2d(p[1].y+add2, p[1].x-p[1].y+p[1].z+add2, 1, 0);
	upd_2d(p[1].z+add2, p[1].x-p[1].y+p[1].z+add2, 1, 1);
	upd_2d(p[1].y+add2, p[1].z+add2, 1, 2);

	for (int i = 2; i <= n; i++)
	{
		while (ptr < i && p[i].x-p[ptr].x > D)
		{
			upd_2d(p[ptr].y+add2, p[ptr].x-p[ptr].y+p[ptr].z+add2, -1, 0);
			upd_2d(p[ptr].z+add2, p[ptr].x-p[ptr].y+p[ptr].z+add2, -1, 1);
			upd_2d(p[ptr].y+add2, p[ptr].z+add2, -1, 2);
 
			ptr++;
		}

		if (i != ptr)
		{
			ans += 1ll*get_rect(p[i].y+1+add2, p[i].x-p[i].y+p[i].z-D+add2, maxn2-1, maxn2-1, 0);
			ans -= 1ll*get_rect(p[i].z+1+add2, p[i].x-p[i].y+p[i].z-D+add2, maxn2-1, maxn2-1, 1);
			ans += 1ll*get_rect(1+add2, p[i].z+1+add2, p[i].y+add2, maxn2-1, 2);
		}

		upd_2d(p[i].y+add2, p[i].x-p[i].y+p[i].z+add2, 1, 0);
		upd_2d(p[i].z+add2, p[i].x-p[i].y+p[i].z+add2, 1, 1);
		upd_2d(p[i].y+add2, p[i].z+add2, 1, 2);
	}

	memset(bit_2d, 0, sizeof bit_2d);

	ptr = 1;

	upd_2d(p[1].y+add2, p[1].x-p[1].y-p[1].z+add2, 1, 0);
	upd_2d(p[1].z+add2, p[1].x-p[1].y-p[1].z+add2, 1, 1);
	upd_2d(p[1].y+add2, p[1].z+add2, 1, 2);

	for (int i = 2; i <= n; i++)
	{
		while (ptr < i && p[i].x-p[ptr].x > D)
		{
			upd_2d(p[ptr].y+add2, p[ptr].x-p[ptr].y-p[ptr].z+add2, -1, 0);
			upd_2d(p[ptr].z+add2, p[ptr].x-p[ptr].y-p[ptr].z+add2, -1, 1);
			upd_2d(p[ptr].y+add2, p[ptr].z+add2, -1, 2);
 
			ptr++;
		}

		if (i != ptr)
		{
			ans += 1ll*get_rect(p[i].y+1+add2, p[i].x-p[i].y-p[i].z-D+add2, maxn2-1, maxn2-1, 0);
			ans -= 1ll*get_rect(1+add2, p[i].x-p[i].y-p[i].z-D+add2, p[i].z+add2, maxn2-1, 1);
			ans += 1ll*get_rect(1+add2, 1+add2, p[i].y+add2, p[i].z+add2, 2);
		}

		upd_2d(p[i].y+add2, p[i].x-p[i].y-p[i].z+add2, 1, 0);
		upd_2d(p[i].z+add2, p[i].x-p[i].y-p[i].z+add2, 1, 1);
		upd_2d(p[i].y+add2, p[i].z+add2, 1, 2);
	}

	return ans;
}
 
int main(void)
{
	int b;
	scanf("%d", &b);
 
	if (b == 1) printf("%lld\n", solve_1());
	else if (b == 2) printf("%lld\n", solve_2());
	else printf("%lld\n", solve_3());
}
