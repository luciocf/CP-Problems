// BOI 2009 - Subway Signalling Error
// Lúcio Cardoso

// Solution is the same as in: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2009_solutions/subway-sol.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn];

int main(void)
{
	int m, n;
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= n; i++)
	{
		char c;
		scanf("%d %c", &a[i], &c);
	}

	sort(a+1, a+n+1);

	for (int i = 1; i <= n; i++)
		if (i%2 == 0)
			a[i] = 2*m-a[i];

	sort(a+1, a+n+1);

	long double gap = 2.00*m/(1.00*n);
	long double at = a[1], mn = 0.00, mx = 0.00;

	for (int i = 2; i <= n; i++)
	{
		mn = min(mn, (at+gap)-1.00*a[i]);
		mx = max(mx, (at+gap)-1.00*a[i]);

		at += gap;
	}

	printf("%.12Lf\n", (mx-mn)/2.00);
}
