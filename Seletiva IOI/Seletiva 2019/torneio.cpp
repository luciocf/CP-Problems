// Seletiva IOI 2019 - Torneio
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

int vencedorPartida(int a, int b);
int numeroVitorias(int competidor);
void responde(int tamanho, int array[]);

int n;
int qtd[maxn];

bool mark[maxn];

int saida[maxn];

void solve_1(void)
{
	for (int i = 1; i <= n; i++)
		for (int j = i+1; j <= n; j++)
			saida[vencedorPartida(i, j)-1]++;

	responde(n, saida);
}

vector<int> solve(int l, int r)
{
	vector<int> ans;
 
	if (l == r) ans.push_back(l);
 
	if (l >= r) return ans;
 
	int mid = (l+r)>>1;
 
	vector<int> a = solve(l, mid);
	vector<int> b = solve(mid+1, r);
 
	int ptr_a = 0, ptr_b = 0;
 
	while (ptr_a < a.size() && ptr_b < b.size())
	{
		int x = vencedorPartida(a[ptr_a], b[ptr_b]);
 
		if (x == a[ptr_a])
			ans.push_back(b[ptr_b++]);
		else
			ans.push_back(a[ptr_a++]);
	}
 
	while (ptr_a < a.size())
		ans.push_back(a[ptr_a++]);
 
	while (ptr_b < b.size())
		ans.push_back(b[ptr_b++]);
 
	return ans;
}

void solve_2(void)
{
	vector<int> ans = solve(1, n);
 
	for (int i = 1; i <= n; i++)
		saida[ans[i-1]-1] = i-1;
 
	responde(n, saida);
}

void solve_3_4(void)
{
	int ind = 1;

	for (int i = 2; i <= n; i++)
		if (vencedorPartida(ind, i) == i)
			ind = i;

	for (int i = 1; i <= n; i++)
	{
		if (i == ind) continue;

		if (vencedorPartida(i, ind) == i)
		{
			responde(0, saida);
			return;
		}
	}

	saida[0] = ind;
	responde(1, saida);
}

void solve_5(void)
{
	for (int i = 1; i <= min(n, 10); i++)
	{
		for (int j = i+1; j <= min(n, 10); j++)
		{
			if (vencedorPartida(i, j) == i) qtd[j]++;
			else qtd[i]++;
		}
	}

	if (n < 10)
	{
		int ans = 0;
		for (int i = 1; i <= n; i++)
			if (qtd[i] <= 4)
				saida[ans++] = i;

		responde(ans, saida);
		return;
	}

	for (int i = 1; i <= 10; i++)
		if (qtd[i] > 4)
			mark[i] = 1;

	for (int i = 11; i <= n; i++)
	{
		vector<int> lista;

		for (int j = 1; j < i; j++)
			if (!mark[j])
				lista.push_back(j);

		for (int j = 0; j < lista.size(); j++)
		{
			if (vencedorPartida(i, lista[j]) == i) qtd[lista[j]]++;
			else qtd[i]++;
		}

		lista.push_back(i);

		for (int j = 0; j < lista.size(); j++)
			if (qtd[lista[j]] > 4)
				mark[lista[j]] = 1;
	}

	memset(qtd, 0, sizeof qtd);

	vector<int> lista;

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			lista.push_back(i);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < lista.size(); j++)
		{
			if (lista[j] == i) continue;

			if (vencedorPartida(i, lista[j]) == i)
				qtd[lista[j]]++;
		}
	}

	int ans = 0;
	for (int i = 0; i < lista.size(); i++)
		if (qtd[lista[i]] <= 4)
			saida[ans++] = lista[i];

	responde(ans, saida);
}

bool ganha[maxn];

void solve_6(void)
{
	for (int i = 1; i <= n; i++)
		qtd[i] = numeroVitorias(i);
 
	int at = n-1;
 
	while (true)
	{
		bool tem = 0;
 
		for (int i = 1; i <= n; i++)
		{
			if (!mark[i] && qtd[i] == at)
			{
				mark[i] = 1, qtd[i] = 0;
				tem = 1;
				break;
			}
		}
 
		if (!tem) break;
		at--;
	}
 
	int u = max_element(qtd+1, qtd+n+1)-qtd;
	int v, w;
 
	for (int i = 1; i <= n; i++)
	{
		if (mark[i] || u == i) continue;
 
		if (vencedorPartida(u, i) == i)
		{
			v = i;
			ganha[i] = 1;
		}
		else ganha[i] = 0;
	}
 
	for (int i = 1; i <= n; i++)
	{
		if (mark[i] || u == i || v == i) continue;
 
		if (!ganha[i] && vencedorPartida(v, i) == i)
		{
			w = i;
			break;
		}
	}
 
	saida[0] = v, saida[1] = u, saida[2] = w;
	responde(3, saida);
}

void processaTorneio(int S, int N)
{
	n = N;

	if (S == 1) solve_1();
	else if (S == 2) solve_2();
	else if (S == 3 || S == 4) solve_3_4();
	else if (S == 5) solve_5();
	else solve_6();
}
