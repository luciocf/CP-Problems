// Codeforce 1182E - Product Oriented Recurrence
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9+7;

struct Matrix
{
	int n, m;
	vector<vector<int>> d;

	Matrix(int n, int m) : n(n), m(m)
	{
		d.assign(n, vector<int>(m));
	}

	Matrix operator * (const Matrix &o)
	{
		Matrix ans(n, o.m);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				for (int k = 0; k < m; k++)
					ans.d[i][j] = (1ll*ans.d[i][j] + 1ll*d[i][k]*o.d[k][j])%(mod-1);

		return ans;
	}

	static Matrix pot(Matrix a, ll b)
	{
		Matrix ans(a.n, a.m);

		for (int i = 0; i < a.n; i++)
			ans.d[i][i] = 1;

		for (; b; b /= 2, a = a * a)
			if (b&1)
				ans = ans * a;

		return ans;
	}
};

int pot(int a, int b)
{
	int ans = 1;

	for (; b; b /= 2, a = (1ll*a*a)%mod)
		if (b&1)
			ans = (1ll*ans*a)%mod;

	return ans;
}

int main(void)
{
	ll n;
	int f1, f2, f3, c;

	scanf("%lld %d %d %d %d", &n, &f1, &f2, &f3, &c);

	int ans = 1;

	Matrix f(1, 3), base_p(3, 3);
	base_p.d[1][0] = base_p.d[2][1] = base_p.d[0][2] = base_p.d[1][2] = base_p.d[2][2] = 1;

	f.d[0][0] = 1;
	int p = (f * Matrix::pot(base_p, n-3)).d[0][2];

	ans = (1ll*ans*pot(f1, p))%mod;

	f.d[0][0] = 0, f.d[0][1] = 1;
	p = (f * Matrix::pot(base_p, n-3)).d[0][2];

	ans = (1ll*ans*pot(f2, p))%mod;

	f.d[0][1] = 0, f.d[0][2] = 1;
	p = (f * Matrix::pot(base_p, n-3)).d[0][2];

	ans = (1ll*ans*pot(f3, p))%mod;

	Matrix t(1, 5), base_q(5, 5);
	base_q.d[1][0] = base_q.d[2][1] = base_q.d[0][2] = base_q.d[1][2] = base_q.d[2][2] = 1;
	base_q.d[3][3] = base_q.d[4][3] = base_q.d[4][4] = 1;
	base_q.d[3][2] = 2;

	t.d[0][3] = t.d[0][4] = 1;
	int q = (t * Matrix::pot(base_q, n-3)).d[0][2];

	ans = (1ll*ans*pot(c, q))%mod;

	printf("%d\n", ans);
}
