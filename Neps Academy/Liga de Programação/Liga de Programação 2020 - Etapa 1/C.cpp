// Neps Academy - Liga de Programação 2020 - Etapa 1 - Construindo Triângulos
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	double mx = 0;
	int A, B, C;

	for (int i = 1; i < n-1; i++)
	{
		int ini = i+2, fim = n, ans = -1;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (a[i]+a[i+1] > a[mid]) ans = mid, ini = mid+1;
			else fim = mid-1;
		}

		if (ans != -1)
		{
			if (sqrt(1.00*a[i]*a[i+1]*a[ans]) > mx)
				A = a[i], B = a[i+1], C = a[ans], mx = sqrt(1.00*a[i]*a[i+1]*a[ans]);
		}
	}

	printf("%d %d %d\n", A, B, C);
}
