// APIO 2018 - Circle Selection
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 3e5+10;
const int add = 1e9;
 
ll R;
 
struct Circle
{
	ll x, y, r;
	int ind;
 
	bool operator<(const ll &o) const
	{
		return y/R < o;
	}
} circle[maxn];
 
vector<vector<Circle>> V;
 
int ans[maxn];
 
bool comp1(Circle a, Circle b)
{
	if (a.x/R == b.x/R) return a.y < b.y;
	return a.x < b.x;
}
 
bool comp2(Circle a, Circle b)
{
	if (a.r == b.r) return a.ind < b.ind;
	return a.r > b.r;
}
 
bool intersect(Circle a, Circle b)
{
	ll dx = a.x-b.x, dy = a.y-b.y, dr = a.r+b.r;
 
	return dx*dx + dy*dy <= dr*dr;
}
 
void rescale(void)
{
	vector<vector<Circle>> aux;
 
	for (int i = 0; i < V.size(); i++)
	{
		ll mn = 1e18, mx = 0;
 
		for (auto c: V[i])
		{
			mn = min(mn, c.x/R);
			mx = max(mx, c.x/R);
		}
 
		ll med = mn;
		for (auto c: V[i])
			if (c.x/R != mn && c.x/R != mx)
				med = c.x/R;
 
		if (aux.size() == 0 || mn > aux.back()[0].x/R)
		{
			aux.push_back(vector<Circle>());
 
			for (auto c: V[i])
				if (c.x/R == mn)
					aux.back().push_back(c);
		}
		else
		{
			vector<Circle> aux1, aux2;

			for (auto c: V[i])
				if (c.x/R == mn)
					aux1.push_back(c);

			for (auto c: aux.back())
				aux2.push_back(c);

			aux.back().clear();

			int ptr1 = 0, ptr2 = 0;

			while (ptr1 < aux1.size() || ptr2 < aux2.size())
			{
				if (ptr1 == aux1.size()) aux.back().push_back(aux2[ptr2++]);
				else if (ptr2 == aux2.size()) aux.back().push_back(aux1[ptr1++]);
				else if (aux1[ptr1].y <= aux2[ptr2].y) aux.back().push_back(aux1[ptr1++]);
				else aux.back().push_back(aux2[ptr2++]);
			}
		}
 
		if (med > mn)
		{
			aux.push_back(vector<Circle>());
 
			for (auto c: V[i])
				if (c.x/R == med)
					aux.back().push_back(c);
		}
 
		if (mx > med)
		{
			aux.push_back(vector<Circle>());
 
			for (auto c: V[i])
				if (c.x/R == mx)
					aux.back().push_back(c);
		}
	}
 
	swap(aux, V);
}
 
void doit(int pos, int c)
{
	ll y = circle[c].y;
 
	ll l_y = y/R - 2, r_y = y/R + 3;
 
	auto it = lower_bound(V[pos].begin(), V[pos].end(), l_y);
	for (; it != V[pos].end() && it->y/R <= r_y; it++)
		if (intersect(circle[c], *it) && !ans[it->ind])
			ans[it->ind] = circle[c].ind;
}
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld %lld %lld", &circle[i].x, &circle[i].y, &circle[i].r);
		circle[i].x += add, circle[i].y += add;
		circle[i].ind = i;
 
		R = max(R, circle[i].r);
	}
 
	sort(circle+1, circle+n+1, comp1);
 
	for (int i = 1; i <= n; i++)
	{
		if (i == 1 || circle[i].x/R > circle[i-1].x/R)
			V.push_back(vector<Circle>());
 
		V.back().push_back(circle[i]);
	}
 
	sort(circle+1, circle+n+1, comp2);
 
	for (int i = 1; i <= n; i++)
	{
		if (ans[circle[i].ind]) continue;
 
		while (circle[i].r < R/2)
		{
			R /= 2;
			rescale();
		}
 
		ll x = circle[i].x;
 
		ll l_x = x/R - 2, r_x = x/R + 3;
 
		int p_l, p_r;
 
		int ini = 0, fim = (int)V.size()-1;
 
		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;
 
			if (V[mid][0].x/R >= l_x) p_l = mid, fim = mid-1;
			else ini = mid+1;
		}
 
		ini = 0, fim = (int)V.size()-1;
 
		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;
 
			if (V[mid][0].x/R <= r_x) p_r = mid, ini = mid+1;
			else fim = mid-1;
		}
 
		for (int j = p_l; j <= p_r; j++)
			doit(j, i);
	}
 
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
