// COI 2014 - Mostovi
// Lúcio Cardoso

// Solution is the same as in: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COI/official/2014/oi/solutions.pdf

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
set<int> st_up, st_down;
set<pii> bridge_up, bridge_down;
 
// u < v
bool reach_up(int u, int v)
{
	auto it = st_up.lower_bound(u);
 
	return (it == st_up.end() || *it >= v);
}
 
// u > v
bool reach_down(int u, int v)
{
	auto it = st_down.upper_bound(u);
 
	if (it == st_down.begin()) return true;
 
	--it;
	return (*it <= v);
}
 
bool reach_updown(int u, int v)
{
	auto it = bridge_up.lower_bound({u, -1});
 
	if (it == bridge_up.end()) return false;
 
	if (!reach_up(u, it->ff) || (it->ss > v && !reach_down(it->ss, v))) return false;
 
	if (it->ss >= v) return true;
 
	auto it2 = bridge_down.lower_bound({v, -1});
 
	if (it2 == bridge_down.end() || !reach_down(it2->ff, v)) return false;
 
	return (it2->ss >= u && reach_up(u, it2->ss));
}
 
bool reach_downup(int u, int v)
{
	auto it = bridge_down.upper_bound({u, 2e9+10});
 
	if (it == bridge_down.begin()) return false;
	--it;
 
	if (!reach_down(u, it->ff) || (it->ss < v && !reach_up(it->ss, v))) return false;
 
	if (it->ss <= v) return true;
 
	auto it2 = bridge_up.upper_bound({v, 2e9+10});
 
	if (it2 == bridge_up.begin()) return false;
	--it2;
 
	if (!reach_up(it2->ff, v)) return false;
 
	return (it2->ss <= u && reach_down(u, it2->ss));
}
 
int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
 
	while (m--)
	{
		char op;
		int u, v;
		scanf(" %c %d %d", &op, &u, &v);
 
		if (op == 'A')
		{
			if (u > v) swap(u, v);
 
			bridge_up.insert({u, v});
			bridge_down.insert({v, u});
		}
		else if (op == 'B')
		{
			if (u > v) swap(u, v);
 
			if (u <= n) st_up.insert(u);
			else st_down.insert(v);
		}
		else
		{
			bool ok;
 
			if (u <= n && v <= n)
			{
				if (u <= v) ok = reach_up(u, v);
				else
				{
					auto it = bridge_up.lower_bound({u, -1});
 
					if (it == bridge_up.end() || !reach_up(u, it->ff)) ok = false;
					else ok = reach_downup(it->ss, v);
				}
			}
			else if (u > n && v > n)
			{
				if (u >= v) ok = reach_down(u, v);
				else
				{
					auto it = bridge_down.upper_bound({u, 2e9+10});
 
					if (it == bridge_down.begin()) ok = false;
					else
					{
						--it;

						if (!reach_down(u, it->ff)) ok = false;
						else ok = reach_updown(it->ss, v);
					}
				}
			}
			else
			{
				if (u < v) ok = reach_updown(u, v);
				else ok = reach_downup(u, v);
			}
 
			if (ok) printf("DA\n");
			else printf("NE\n");
		}
	}
}
