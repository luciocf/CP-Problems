// Balkan OI 2011 - Medians
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int a[maxn];

bool mark[maxn];

void print(int i)
{
	printf(" %d", i);
	mark[i] = 1;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	int l = 1, r = 2*n-1;

	printf("%d", a[1]);
	mark[a[1]] = 1;

	for (int i = 2; i <= n; i++)
	{
		if (a[i] == a[i-1])
		{
			while (mark[l]) l++;
			while (mark[r]) r--;

			print(l); print(r);
		}
		else if (a[i] < a[i-1])
		{
			if (mark[a[i]])
			{
				while (mark[l]) l++;
				print(l);

				while (mark[l]) l++;
				print(l);
			}
			else
			{
				print(a[i]);

				while (mark[l]) l++;
				print(l);
			}
		}
		else
		{
			if (mark[a[i]])
			{
				while (mark[r]) r--;
				print(r);

				while (mark[r]) r--;
				print(r);
			}
			else
			{
				print(a[i]);

				while (mark[r]) r--;
				print(r);
			}
		}
	}

	printf("\n");
}
