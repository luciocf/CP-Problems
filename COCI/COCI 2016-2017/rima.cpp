// COCI 2016/2017 - Rima
// Lúcio Cardoso

// Solution is the same as in: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest4_solutions/solutions.pdf

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 3e6+10;
 
struct Node
{
	Node *b[26];
	int u;
	bool fim;
};
 
int cnt;
 
int dp[maxn], path[maxn];
 
void add(Node *t, string const s)
{
	Node *at = t;
 
	for (auto c: s)
	{
		if (!at->b[c-'a'])
		{
			at->b[c-'a'] = new Node();
			at->b[c-'a']->u = ++cnt;
		}
 
		at = at->b[c-'a'];
	}
 
	at->fim = true;
}
 
void dfs(Node *t)
{
	int mx1 = -1, mx2 = -1;
 
	int tot = (t->fim);
 
	for (int i = 0; i < 26; i++)
	{
		if (!t->b[i]) continue;
 
		dfs(t->b[i]);
 
		if (t->b[i]->fim)
		{
			tot++;
 
			int x = path[t->b[i]->u];
 
			if (x > mx1) mx2 = mx1, mx1 = x;
			else if (x > mx2) mx2 = x;
		}
	}
 
	dp[t->u] = path[t->u] = tot;
 
	if (mx2 != -1) 
	{
		dp[t->u] = mx1 + mx2 + tot-2;
		path[t->u] = mx1 + tot-1;
	}
	else if (mx1 != -1)
	{
		dp[t->u] = mx1 + tot-1;
		path[t->u] = mx1 + tot-1;
	}
}
 
int main(void)
{
	Node *root = new Node();
	root->u = 0;
 
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
 
		reverse(s.begin(), s.end());
 
		add(root, s);
	}
 
	dfs(root);
 
	int ans = 0;
	for (int i = 0; i < maxn; i++)
		ans = max(ans, dp[i]);
 
	printf("%d\n", ans);
}
