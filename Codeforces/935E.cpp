// Codeforces 935E - Fafa and Ancient Mathematics
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int l[maxn], r[maxn];
int sz[maxn];

int dp[maxn][2][101];

int leaf[maxn];

int P, M;

void get_p(int u)
{
	for (int p = 0; p <= min(P, sz[u]); p++)
	{
		int m = sz[u]-p;

		for (int i = 0; i <= min(p, sz[l[u]]); i++)
		{
			int p_l = i, m_l = sz[l[u]]-p_l;
			int p_r = p-p_l-1, m_r = m-m_l;

			if (min({p_l, m_l, p_r, m_r}) >= 0 && p_l+m_l == sz[l[u]] && p_r+m_r == sz[r[u]] && p_l+p_r+1 == p && m_l+m_r == m)
			{			
				dp[u][0][p] = max(dp[u][0][p], dp[l[u]][0][p_l] + dp[r[u]][0][p_r]);
				dp[u][1][p] = min(dp[u][1][p], dp[l[u]][1][p_l] + dp[r[u]][1][p_r]);
			}

			p_l = i, m_l = sz[l[u]]-p_l;
			p_r = p-p_l, m_r = m-m_l-1;


			if (min({p_l, m_l, p_r, m_r}) >= 0 && p_l+m_l == sz[l[u]] && p_r+m_r == sz[r[u]] && p_l+p_r == p && m_l+m_r+1 == m)
			{			
				dp[u][0][p] = max(dp[u][0][p], dp[l[u]][0][p_l] - dp[r[u]][1][p_r]);
				dp[u][1][p] = min(dp[u][1][p], dp[l[u]][1][p_l] - dp[r[u]][0][p_r]);
			}
		}
	}
}

void get_m(int u)
{
	for (int m = 0; m <= min(M, sz[u]); m++)
	{
		int p = sz[u]-m;

		for (int i = 0; i <= min(m, sz[l[u]]); i++)
		{
			int m_l = i, p_l = sz[l[u]]-m_l;
			int p_r = p-p_l-1, m_r = m-m_l;

			if (min({p_l, m_l, p_r, m_r}) >= 0 && p_l+m_l == sz[l[u]] && p_r+m_r == sz[r[u]] && p_l+p_r+1 == p && m_l+m_r == m)
			{			
				dp[u][0][m] = max(dp[u][0][m], dp[l[u]][0][m_l] + dp[r[u]][0][m_r]);
				dp[u][1][m] = min(dp[u][1][m], dp[l[u]][1][m_l] + dp[r[u]][1][m_r]);
			}

			m_l = i, p_l = sz[l[u]]-m_l;
			p_r = p-p_l, m_r = m-m_l-1;

			if (min({p_l, m_l, p_r, m_r}) >= 0 && p_l+m_l == sz[l[u]] && p_r+m_r == sz[r[u]] && p_l+p_r == p && m_l+m_r+1 == m)
			{			
				dp[u][0][m] = max(dp[u][0][m], dp[l[u]][0][m_l] - dp[r[u]][1][m_r]);
				dp[u][1][m] = min(dp[u][1][m], dp[l[u]][1][m_l] - dp[r[u]][0][m_r]);
			}
		}
	}
}

bool num(int x)
{
	if (x > (int)max('(', ')')) return true;
	return ((char)x != '(' && (char)x != ')');
}

void solve(int u)
{
	for (int i = 0; i < 101; i++)
		dp[u][0][i] = -inf, dp[u][1][i] = inf;

	if (leaf[u] != -1)
	{
		dp[u][0][0] = dp[u][1][0] = leaf[u];
		return;
	}
	
	solve(l[u]); solve(r[u]);

	sz[u] = 1+sz[l[u]]+sz[r[u]];

	if (P < M) get_p(u);
	else get_m(u);
}

int main(void)
{
	string s;
	cin >> s;

	cin >> P >> M;

	int nd = 50;

	memset(leaf, -1, sizeof leaf);

	vector<int> V;

	for (int i = 0; i < s.size(); i++)
	{
		V.push_back((int)s[i]);

		if (s[i] >= '0' && s[i] <= '9')
		{
			leaf[++nd] = (int)(s[i]-'0');
			V.back() = nd;
		}
	}

	while (true)
	{
		int pos = -1;

		for (int i = 0; i < V.size(); i++)
		{
			if (V[i] <= (int)'?')
			{
				if ((char)V[i] == '?' && num(V[i-1]) && num(V[i+1]))
				{
					pos = i;
					break;
				}
			}
		}

		if (pos == -1) break;

		vector<int> aux;

		for (int i = 0; i < pos-2; i++)
			aux.push_back(V[i]);

		++nd;
		l[nd] = V[pos-1], r[nd] = V[pos+1];

		aux.push_back(nd);

		for (int i = pos+3; i < V.size(); i++)
			aux.push_back(V[i]);

		V = aux;
	}

	solve(nd);

	cout << dp[nd][0][min(P, M)] << "\n";
}
