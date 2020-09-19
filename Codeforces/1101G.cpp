// Codeforces 1101G - (Zero XOR Subset)-less
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n;
int a[maxn];
int p[maxn];

int tam_base;

int b[maxn];

void add(int v)
{
	for (int i = 0; i < 31; i++)
	{
		if (!(v&(1<<i))) continue;

		if (!b[i])
		{
			b[i] = v, ++tam_base;
			break;
		}

		v ^= b[i];
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		p[i] = p[i-1] ^ a[i];
	}

	if (!p[n])
	{
		printf("-1\n");
		return 0;
	}

	for (int i = 1; i <= n; i++)
		add(p[i]);
		
	printf("%d\n", tam_base);	
}
