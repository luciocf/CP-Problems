// Codeforces 718C - Sasha and Array
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const int mod = 1e9+7;

int md(ll x)
{
	return (x - (x/mod)*mod);
}

struct Matrix
{
	int d[2][2];

	Matrix()
	{
		d[0][0] = d[0][1] = d[1][0] = d[1][1] = 0;
	}

	void make_id(void)
	{
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				d[i][j] = (i == j ? 1 : 0);
	}

	Matrix operator+(const Matrix &o)
	{
		Matrix ans;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				ans.d[i][j] = d[i][j] + o.d[i][j];
				if (ans.d[i][j] > mod) ans.d[i][j] -= mod;
			}
		}

		return ans;
	}

	Matrix operator*(const Matrix &o)
	{
		Matrix ans;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ans.d[i][j] = md(1ll*ans.d[i][j] + 1ll*d[i][k]*o.d[k][j]);

		return ans;
	}

	static Matrix pot(Matrix a, ll b)
	{
		Matrix ans;

		ans.make_id();

		for (; b; b /= 2, a = a*a)
			if (b%2)
				ans = ans * a;

		return ans;
	}
};

int a[maxn];

Matrix base;

Matrix fib(int n)
{
	Matrix f;
	f.d[0][0] = f.d[0][1] = 1;

	return (f * Matrix::pot(base, n-1));
}

struct SegmentTree
{
	Matrix tree[4*maxn], lazy[4*maxn];
	bool mark_lazy[4*maxn];

	void build(int node, int l, int r)
	{
		lazy[node].make_id();

		if (l == r)
		{
			tree[node] = fib(a[l]);
			return;
		}

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);

		tree[node] = tree[2*node] + tree[2*node+1];
	}

	void flush(int node, int l, int r)
	{
		if (!mark_lazy[node]) return;

		if (l != r)
		{
			lazy[2*node] = lazy[2*node] * lazy[node];
			lazy[2*node+1] = lazy[2*node+1] * lazy[node];

			mark_lazy[2*node] = mark_lazy[2*node+1] = 1;
		}

		tree[node] = tree[node] * lazy[node];
		lazy[node].make_id();
		mark_lazy[node] = 0;
	}

	void upd(int node, int l, int r, int a, int b, Matrix &M)
	{
		flush(node, l, r);
		if (l > b || r < a) return;

		if (l >= a && r <= b)
		{
			mark_lazy[node] = 1, lazy[node] = M;
			flush(node, l, r);
			return;
		}

		int mid = (l+r)>>1;

		upd(2*node, l, mid, a, b, M); upd(2*node+1, mid+1, r, a, b, M);

		tree[node] = tree[2*node] + tree[2*node+1];
	}

	int query(int node, int l, int r, int a, int b)
	{
		if (l > b || r < a) return 0;

		flush(node, l, r);

		if (l >= a && r <= b) return tree[node].d[0][0];

		int mid = (l+r)>>1;

		int ans = query(2*node, l, mid, a, b) + query(2*node+1, mid+1, r, a, b);
		
		if (ans > mod) ans -= mod;

		return ans;
	}
} seg;

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	base.d[0][0] = 0, base.d[0][1] = 1;
	base.d[1][0] = 1, base.d[1][1] = 1;

	seg.build(1, 1, n);

	while (m--)
	{
		int op, l, r;
		scanf("%d %d %d", &op, &l, &r);

		if (op == 1)
		{
			int v;
			scanf("%d", &v);

			Matrix M;
			M = Matrix::pot(base, v);

			seg.upd(1, 1, n, l, r, M);
		}
		else
		{
			printf("%d\n", seg.query(1, 1, n, l, r));
		}
	}
}
