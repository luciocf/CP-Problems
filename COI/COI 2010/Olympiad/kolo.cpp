// COI 2010 - Kolo
// Lúcio Cardoso

// Solution is the same as in: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COI/official/2010/solutions.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 7700000;

int n, k;

bool mark[maxn];
vector<int> P;

void sieve(void)
{
	mark[1] = 1;

	for (int i = 2; i < maxn; i++)
		if (!mark[i])
			for (int j = 2*i; j < maxn; j += i)
				mark[j] = 1;
}

int get_pos(int x)
{
	for (auto p: P)
	{
		if (!x) x = p%n;
		else
		{
			if (x <= p%(n-1)) x = (x+n-1)%n;
			x = ((x - p/(n-1))%n + n)%n;
		}
	}

	return x;
}

int get_val(int x)
{
	for (auto p: P)
	{
		if (x == p%n) x = 0;
		else
		{
			x = (x + p/(n-1))%n;
			if (x <= p%(n-1)) x = (x+1)%n;
		}
	}

	return x;
}

int main(void)
{
	sieve();

	int x;
	scanf("%d %d %d", &n, &k, &x);

	int at = 2;
	while (P.size() < k)
		if (!mark[at++])
			P.push_back(at-1);

	int posM = get_pos(x-1);

	reverse(P.begin(), P.end());

	int valR = get_val((posM+1)%n);
	int valL = get_val((posM+n-1)%n);

	printf("%d %d\n", valR+1, valL+1);
}
