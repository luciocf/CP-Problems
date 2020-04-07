// USACO 2016/2017 - Lots of Triangles
// Lúcio Cardoso

#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pt;
typedef long long ll;

const int maxn = 310;

pt p[maxn];

int ans[maxn][maxn][maxn];

int final[maxn];

pt operator- (const pt &x, const pt &y)
{
	return {x.x-y.x, x.y-y.y};
}

ll cross(pt a, pt b)
{
	return 1ll*a.x*b.y - 1ll*a.y*b.x;
}

int sign(ll x)
{
	if (x > 0) return 1;
	if (x == 0) return 0;
	return -1;
}

bool inside(pt a, pt b, pt c, pt p)
{
	ll a1 = abs(cross(a-p, b-p));
	ll a2 = abs(cross(b-p, c-p));
	ll a3 = abs(cross(c-p, a-p));

	return (abs(cross(b-a, c-a)) == (a1+a2+a3));
}

bool intersect(pt a1, pt b1, pt a2, pt b2)
{
	int c1 = sign(cross(b1-a1, a2-a1))*sign(cross(b1-a1, b2-a1));
	int c2 = sign(cross(b2-a2, a1-a2))*sign(cross(b2-a2, b1-a2));

	return (c1 == -1 && c2 == -1);
}

int main(void)
{
	freopen("triangles.in", "r", stdin); freopen("triangles.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &p[i].x, &p[i].y);

	sort(p+1, p+n+1);

	pt pivot = p[1];

	for (int a = 2; a <= n; a++)
		for (int b = a+1; b <= n; b++)
			for (int c = 2; c <= n; c++)
				if (c != a && c != b && inside(pivot, p[a], p[b], p[c]))
					ans[1][a][b]++, ans[1][b][a]++;

	for (int a = 2; a <= n; a++)
	{
		for (int b = a+1; b <= n; b++)
		{
			for (int c = b+1; c <= n; c++)
			{
				if (intersect(pivot, p[a], p[b], p[c]))
					ans[a][b][c] = ans[1][b][a] + ans[1][c][a] - ans[1][b][c];
				else if (intersect(pivot, p[b], p[a], p[c]))
				{
					ans[a][b][c] = ans[1][a][b] + ans[1][c][b] - ans[1][a][c];
				}
				else if (intersect(pivot, p[c], p[a], p[b]))
				{
					ans[a][b][c] = ans[1][a][c] + ans[1][b][c] - ans[1][a][b];
				}
				else
				{
					ll a1 = abs(cross(p[a]-pivot, p[b]-pivot));
					ll a2 = abs(cross(p[b]-pivot, p[c]-pivot));
					ll a3 = abs(cross(p[c]-pivot, p[a]-pivot));

					if (max({a1, a2, a3}) == a1)
						ans[a][b][c] = ans[1][a][b] - ans[1][a][c] - ans[1][b][c] - 1;
					else if (max({a1, a2, a3}) == a2)
						ans[a][b][c] = ans[1][b][c] - ans[1][b][a] - ans[1][c][a] - 1;
					else
						ans[a][b][c] = ans[1][c][a] - ans[1][c][b] - ans[1][a][b] - 1;
				}

				final[ans[a][b][c]]++;
			}
		}
	}

	for (int a = 2; a <= n; a++)
		for (int b = a+1; b <= n; b++)
			final[ans[1][a][b]]++;

	for (int i = 0; i <= n-3; i++)
		printf("%d\n", final[i]);
}
