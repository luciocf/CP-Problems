// USACO Gold Jan 2015 - Cow Rectangles
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 510;

struct Pt
{
	int x, y;
	int type;
} ptX[maxn], ptY[2][maxn];

bool comp1(Pt a, Pt b)
{
	if (a.x == b.x) return a.type < b.type;
	return a.x < b.x;
}

bool comp2(Pt a, Pt b)
{
	if (a.y == b.y) return a.type < b.type;
	return a.y < b.y;
}

bool comp3(Pt a, Pt b)
{
	if (a.y == b.y) return a.type > b.type;
	return a.y < b.y;
}

int main(void)
{
	freopen("cowrect.in", "r", stdin);
	freopen("cowrect.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int x, y;
		char c;

		scanf("%d %d %c", &x, &y, &c);

		ptX[i].x = x, ptX[i].y = y, ptX[i].type = (c == 'G' ? 0 : 1);
		ptY[0][i] = ptY[1][i] = ptX[i];
	}

	sort(ptX+1, ptX+n+1, comp1);
	sort(ptY[0]+1, ptY[0]+n+1, comp2);
	sort(ptY[1]+1, ptY[1]+n+1, comp3);


	int ans = 1, area = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j >= 1; j--)
		{
			int h1 = -1, tot = 0;
			int b = ptX[i].x, a = ptX[j].x;

			for (int l = 1; l <= n; l++)
			{
				if (ptY[0][l].y < min(ptX[i].y, ptX[j].y)) continue;
				if (ptY[0][l].x > b || ptY[0][l].x < a) continue;

				if (ptY[0][l].type == 0) break;

				h1 = max(h1, ptY[0][l].y);
				++tot;
			}

			if (h1 < max(ptX[i].y, ptX[j].y)) continue;

			int h2 = min(ptX[i].y, ptX[j].y);

			for (int l = n; l >= 1; l--)
			{
				if (ptY[1][l].y >= min(ptX[i].y, ptX[j].y)) continue;
				if (ptY[1][l].x > b || ptY[1][l].x < a) continue;

				if (ptY[1][l].type == 0) break;

				h2 = min(h2, ptY[1][l].y);
				++tot;
			}

			if (tot > ans || (tot == ans && (b-a)*(h1-h2) < area))
				ans = tot, area = (b-a)*(h1-h2);
		}
	}

	printf("%d\n%d\n", ans, area);
}
