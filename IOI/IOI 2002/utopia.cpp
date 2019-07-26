// IOI 2002 - Utopia Divided
// Lúcio Cardoso

// Solution is the same as the one described here: 
// https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2002/utopia-handout.pdf

#include <bits/stdc++.h>

using namespace std;

typedef pair<char, int> pii;

const int maxn = 1e4+10;

int n;

int valX[maxn], valY[maxn];

int signX[maxn], signY[maxn];

int sign[maxn];

vector<pii> ansX, ansY;

void solve_x(void)
{
	sort(valX+1, valX+n+1);

	int change = 0;
	for (int i = 2; i <= n; i++)
		if (signX[i] != signX[i-1])
			change++;

	sign[n-change] = signX[1];
	ansX.push_back({(signX[1] == 1 ? '+' : '-'), valX[n-change]});

	for (int i = n-change+1; i <= n; i++)
		sign[i] = (sign[i-1] == -1 ? 1 : -1);

	for (int i = n-change-1; i >= 1; i--)
		sign[i] = (sign[i+1] == -1 ? 1 : -1);

	int l = n-change-1, r = n-change+1;
	int at = signX[1];

	for (int i = 2; i <= n; i++)
	{
		if (signX[i] != at)
		{
			ansX.push_back({(sign[r] == 1 ? '+' : '-'), valX[r]});
			at = signX[i], r++;
		}
		else
		{
			ansX.push_back({(sign[l] == 1 ? '+' : '-'), valX[l]});
			at = signX[i], l--;
		}
	}
}

void solve_y(void)
{
	sort(valY+1, valY+n+1);

	int change = 0;
	for (int i = 2; i <= n; i++)
		if (signY[i] != signY[i-1])
			change++;

	sign[n-change] = signY[1];
	ansY.push_back({(signY[1] == 1 ? '+' : '-'), valY[n-change]});

	for (int i = n-change+1; i <= n; i++)
		sign[i] = (sign[i-1] == -1 ? 1 : -1);

	for (int i = n-change-1; i >= 1; i--)
		sign[i] = (sign[i+1] == -1 ? 1 : -1);

	int l = n-change-1, r = n-change+1;
	int at = signY[1];

	for (int i = 2; i <= n; i++)
	{
		if (signY[i] != at)
		{
			ansY.push_back({(sign[r] == 1 ? '+' : '-'), valY[r]});
			at = signY[i], r++;
		}
		else
		{
			ansY.push_back({(sign[l] == 1 ? '+' : '-'), valY[l]});
			at = signY[i], l--;
		}
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &valX[i]);

	for (int i = 1; i <= n; i++)
		scanf("%d", &valY[i]);

	for (int i = 1; i <= n; i++)
	{
		int q;
		scanf("%d", &q);

		if (q == 1) signX[i] = signY[i] = 1;
		else if (q == 2) signX[i] = -1, signY[i] = 1;
		else if (q == 3) signX[i] = signY[i] = -1;
		else signX[i] = 1, signY[i] = -1; 
	}

	solve_x();
	solve_y();

	for (int i = 0; i < n; i++)
		printf("%c%d %c%d\n", ansX[i].first, ansX[i].second, ansY[i].first, ansY[i].second);
}
