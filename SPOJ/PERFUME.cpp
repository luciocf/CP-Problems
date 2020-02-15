// SPOJ - Perfume
// Lúcio Cardoso

#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<double, double> pt;

const int maxn = 210;
const double eps = 1e-9;

pt a[maxn];

vector<pt> env;

double cross(pt a, pt b)
{
	return a.x*b.y-a.y*b.x;
}

bool ccw(pt a, pt b, pt c)
{
	b.x -= a.x, b.y -= a.y;
	c.x -= a.x, c.y -= a.y;

	return cross(b, c) > 0;
}

bool cw(pt a, pt b, pt c)
{
	b.x -= a.x, b.y -= a.y;
	c.x -= a.x, c.y -= a.y;

	return cross(b, c) < 0;
}

void get_ch(int n)
{
	pt p1 = a[1], p2 = a[n];

	vector<pt> lower, upper;
	lower.push_back(p1); upper.push_back(p1);

	for (int i = 2; i <= n; i++)
	{
		if (i == n || cw(p1, a[i], p2))
		{
			while (upper.size() >= 2 && !cw(upper[upper.size()-2], upper.back(), a[i]))
				upper.pop_back();

			upper.push_back(a[i]);
		}

		if (i == n || ccw(p1, a[i], p2))
		{
			while (lower.size() >= 2 && !ccw(lower[lower.size()-2], lower.back(), a[i]))
				lower.pop_back();

			lower.push_back(a[i]);
		}
	}

	env.clear();

	for (int i = 0; i < (int)upper.size(); i++)
		env.push_back(upper[i]);
	for (int i = (int)lower.size()-2; i > 0; i--)
		env.push_back(lower[i]);
}

double area(pt a, pt b, pt c)
{
	b.x -= a.x, b.y -= a.y;
	c.x -= a.x, c.y -= a.y;

	return abs(cross(b, c));
}

bool in_triangle(pt a, pt b, pt c, pt p)
{
	double A = area(a, b, c);

	double a1 = area(p, a, b), a2 = area(p, b, c), a3 = area(p, c, a);

	return (fabs(a1+a2+a3-A) < eps);
}

bool in_segment(pt a, pt b, pt c)
{
	double dist1 = sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
	double dist2 = sqrt((b.x-c.x)*(b.x-c.x) + (b.y-c.y)*(b.y-c.y));
	double dist3 = sqrt((a.x-c.x)*(a.x-c.x) + (a.y-c.y)*(a.y-c.y));

	return (fabs(dist1+dist2-dist3) < eps);
}

bool inside(pt p)
{
	if (env.size() == 1) return (fabs(p.x-env[0].x) < eps && fabs(p.y-env[0].y) < eps);
	if (env.size() == 2) return in_segment(env[0], p, env[1]);

	for (int i = 1; i < env.size()-1; i++)
		if (in_triangle(env[0], env[i], env[i+1], p))
			return true;

	return false;
}

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			scanf("%lf %lf", &a[i].x, &a[i].y);

		sort(a+1, a+n+1);

		get_ch(n);

		int q;
		scanf("%d", &q);

		for (int i = 1; i <= q; i++)
		{
			pt p;
			scanf("%lf %lf", &p.x, &p.y);

			if (inside(p)) printf("Yes\n");
			else printf("No\n");
		}

		if (t >= 1) printf("\n");
	}
}
