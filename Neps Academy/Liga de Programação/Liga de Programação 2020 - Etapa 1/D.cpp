// Neps Academy - Liga de Programação 2020 - Etapa 1 - Divisão de Terras
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int n, K;

struct Rect
{
	int x_a, y_a;
	int x_b, y_b;
} rect[maxn];

bool ok(long long l)
{
	long long area = 0;

	for (int i = 1; i <= n; i++)
	{
		if (rect[i].y_a >= l) continue;

		int h = rect[i].x_b-rect[i].x_a;

		if (rect[i].y_b <= l) area += 1ll*h*(rect[i].y_b-rect[i].y_a);
		else area += 1ll*h*(l-rect[i].y_a);
	}

	return (area >= K);
}

int busca(void)
{
	int ini = -inf, fim = inf, ans = inf+1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(1ll*mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %d", &n, &K);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d %d", &rect[i].x_a, &rect[i].y_a, &rect[i].x_b, &rect[i].y_b);

	int ans = busca();

	if (ans == inf+1) printf("PERDAO MEU REI\n");
	else printf("%d\n", ans);
}
