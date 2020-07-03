// POI 2011 - Lollipop
// Lúcio Cardoso

// Solution is the same as in: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2011/editorial/liz.pdf

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e6+10;

int a[maxn];
int pref[maxn];

int mx[2], l[2], r[2];

pii ans[maxn];

void get_0(int n)
{
	int mn[2], ind[2];

	mn[0] = 0, mn[1] = 1e9+10;
	ind[0] = 0, ind[1] = -1;

	for (int i = 1; i <= n; i++)
	{
		if (pref[i]%2 == 0)
		{
			if (pref[i]-mn[0] > mx[0])
			{
				mx[0] = pref[i]-mn[0];
				l[0] = ind[0]+1, r[0] = i;
			}

			if (pref[i] < mn[0])
			{
				mn[0] = pref[i];
				ind[0] = i;
			}
		}
		else
		{
			if (pref[i]-mn[1] > mx[0])
			{
				mx[0] = pref[i]-mn[1];
				l[0] = ind[1]+1, r[0] = i;
			}

			if (pref[i] < mn[1])
			{
				mn[1] = pref[i];
				ind[1] = i;
			}
		}
	}
}

void get_1(int n)
{
	int mn[2], ind[2];

	mn[0] = 0, mn[1] = 1e9+10;
	ind[0] = 0, ind[1] = -1;

	for (int i = 1; i <= n; i++)
	{
		if (pref[i]%2 == 0)
		{
			if (pref[i]-mn[1] > mx[1])
			{
				mx[1] = pref[i]-mn[1];
				l[1] = ind[1]+1, r[1] = i;
			}

			if (pref[i] < mn[0])
			{
				mn[0] = pref[i];
				ind[0] = i;
			}
		}
		else
		{
			if (pref[i]-mn[0] > mx[1])
			{
				mx[1] = pref[i]-mn[0];
				l[1] = ind[0]+1, r[1] = i;
			}

			if (pref[i] < mn[1])
			{
				mn[1] = pref[i];
				ind[1] = i;
			}
		}
	}
}

void gen_0(void)
{
	int L = l[0], R = r[0];
	int at = mx[0];

	while (at > 0)
	{
		ans[at] = {L, R};

		if (a[L] == 2)
			L++;
		else if (a[R] == 2)
			R--;
		else
			L++, R--;

		at -= 2;
	}
}

void gen_1(void)
{
	int L = l[1], R = r[1];
	int at = mx[1];

	while (at > 0)
	{
		ans[at] = {L, R};

		if (a[L] == 2)
			L++;
		else if (a[R] == 2)
			R--;
		else
			L++, R--;

		at -= 2;
	}
}


int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);


	for (int i = 1; i <= n; i++)
	{
		char c;
		scanf(" %c", &c);

		if (c == 'T') a[i] = 2, pref[i] = pref[i-1]+2;
		else a[i] = 1, pref[i] = pref[i-1]+1;
	}

	get_0(n); get_1(n);
	gen_0(); gen_1();

	while (m--)
	{
		int k;
		scanf("%d", &k);

		if (ans[k].first == 0) printf("NIE\n");
		else printf("%d %d\n", ans[k].first, ans[k].second);
	}
}
