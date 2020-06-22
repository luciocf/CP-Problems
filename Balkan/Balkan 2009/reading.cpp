// Balkan OI 2009 - Reading
// Lúcio Cardoso

// Solution is the same as in: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Reading/main.cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 150;
const int mod = 1e9+7;

struct Mat
{
	int M[maxn][maxn];

	Mat() {memset(M, 0, sizeof M);}
};

int w[26][26];

Mat id;

Mat mult(Mat a, Mat b)
{
	Mat o;

	for (int i = 0; i < maxn; i++)
		for (int j = 0; j < maxn; j++)
			for (int l = 0; l < maxn; l++)
				o.M[i][j] = (o.M[i][j] + (1ll*a.M[i][l]*b.M[l][j])%mod)%mod;
	return o;
}

Mat pot(Mat a, int b)
{
	if (!b) return id;

	Mat t = pot(a, b/2);

	if (b%2) return (mult(mult(t, t), a));

	return mult(t, t);
}

void getid(void)
{
	for (int i = 0; i < maxn; i++)
		id.M[i][i] = 1;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			w[i][j] = 1;

	for (int i = 0; i < m; i++)
	{
		char u, v;
		int f;

		scanf(" %c %c %d", &u, &v, &f);

		int a = (int)(u-'a'), b = (int)(v-'a');

		w[a][b] = w[b][a] = f;
	}

	getid();

	Mat base, T;

	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
			base.M[5*i][5*j + w[i][j] - 1] = 1;

		base.M[5*i + 1][5*i] = 1;
		base.M[5*i + 2][5*i + 1] = 1;
		base.M[5*i + 3][5*i + 2] = 1;
		base.M[5*i + 4][5*i + 3] = 1;

		base.M[maxn-1][5*i] = 1;
	}

	base.M[maxn-1][maxn-1] = 1;

	for (int i = 0; i < 26; i++)
		T.M[5*i][0] = 1;

	int ans = mult(pot(base, n+1), T).M[maxn-1][0];

	printf("%d\n", ans);
}
