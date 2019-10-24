// BOI 2010 - Matching Bins
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e4+10;
const int maxv = 1e3+10;

int n;
int a[maxn];

int freq[2][maxn], aux[2][maxn];

int main(void)
{
	int fodase;
	scanf("%d %d", &fodase, &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	if (n == 1)
	{
		printf("0\n");
		return 0;
	}

	int ans = 0;
	if (a[1] < a[2]) ans = 1;

	freq[0][a[1]]++, freq[1][a[2]]++;
	aux[0][a[1]]++, aux[1][a[2]]++;

	for (int k = 2; 2*k <= n; k++)
	{
		freq[0][a[k]]++;
		freq[1][a[k]]--;
		freq[1][a[2*k-1]]++;
		freq[1][a[2*k]]++;

		aux[0][a[k]]++;
		aux[1][a[k]]--;
		aux[1][a[2*k-1]]++;
		aux[1][a[2*k]]++;

		int l = 1, r = 1;
		bool ok = 1;

		while (l < maxn && r < maxv)
		{
			if (freq[0][l] == 0)
				l++;
			else if (freq[1][r] == 0)
				r++;
			else
			{
				if (l >= r)
				{
					ok = 0;
					break;
				}

				if (freq[0][l] > freq[1][r])
					freq[0][l] -= freq[1][r], freq[1][r] = 0;
				else
					freq[1][r] -= freq[0][l], freq[0][l] = 0;
			}
		}

		for (int i = 1; i < maxv; i++)
			freq[0][i] = aux[0][i], freq[1][i] = aux[1][i];

		if (ok) ans = k;
	}

	printf("%d\n", ans);
}
