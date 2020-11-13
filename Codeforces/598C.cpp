// Codeforces 598C - Nearest Vectors
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

struct pp
{
	ll x, y;
	int ind;
} pt[maxn];

ll cross(pp a, pp b)
{
	return a.x*b.y - a.y*b.x;
}

ll dot(pp a, pp b)
{
	return a.x*b.x + a.y*b.y;
}

ll mod(pp a)
{
	return a.x*a.x + a.y*a.y;
}

bool comp(pp a, pp b)
{
	if (a.y >= 0 && b.y < 0) return 1;
	if (a.y < 0 && b.y >= 0) return 0;

	if (a.y == 0 && b.y == 0)
	{
		if (a.x >= 0 && b.x < 0) return 1;
		if (a.x < 0 && b.x >= 0) return 0;

		return mod(a) < mod(b);
	}

	if (cross(a, b) == 0) return mod(a) < mod(b);

	return cross(a, b) > 0;
}

bool menor(pp a1, pp b1, pp a2, pp b2)
{
	pp p1 = {dot(a1, b1), abs(cross(a1, b1))};
	pp p2 = {dot(a2, b2), abs(cross(a2, b2))};

	return cross(p1, p2) > 0;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%lld %lld", &pt[i].x, &pt[i].y);

		pt[i].ind = i+1;
	}

	sort(pt, pt+n, comp);

	int p1 = 0, p2 = 1;

	for (int i = 0; i < n; i++)
		if (menor(pt[i], pt[(i+1)%n], pt[p1], pt[p2]))
			p1 = i, p2 = (i+1)%n;

	printf("%d %d\n", pt[p1].ind, pt[p2].ind);
}
