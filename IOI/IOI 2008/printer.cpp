// IOI 2008 - Type Printer
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

struct node
{
	node *b[26];
	int sz;
	bool end;
};

int n, qtd;
vector<char> ans;

void insert(node *at, string const &s)
{
	int add = -1;

	for (char a: s)
	{
		at->sz = max(at->sz, (int)s.size()-(++add));

		if (!at->b[a-'a']) at->b[a-'a'] = new node();

		at = at->b[a-'a'];
	}

	at->sz = max(at->sz, 1);
	at->end = true;
}

void dfs(node *at, char c)
{
	if (c != '*') ans.push_back(c);
	if (at->end) ans.push_back('P'), qtd++;

	set< pair<int, int> > S;

	for (int i = 0; i < 26; i++)
	{
		if (!at->b[i]) continue;

		S.insert({at->b[i]->sz, i});
	}

	for (auto p: S)
		dfs(at->b[p.second], (char)(p.second+'a'));

	if (qtd < n) ans.push_back('-');
}

int main(void)
{
	cin >> n;

	node *t = new node();

	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;

		insert(t, s);
	}

	dfs(t, '*');

	cout << ans.size() << "\n";
	for (auto c: ans) cout << c << "\n";
}
