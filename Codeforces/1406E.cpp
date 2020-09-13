// Codeforces 1406E - Deleting Numbers
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;

bool mark[maxn], mark2[maxn];

void sieve(void)
{
	for (int i = 2; i < maxn; i++)
		if (!mark[i])
			for (int j = 2*i; j < maxn; j += i)
				mark[j] = 1;
}

void solve_primo(void)
{
	for (int i = 2; i <= min(n, 317); i++)
	{
		if (mark[i]) continue;

		cout << "A " << i << endl;
		int x;
		cin >> x;

		if (x == 1)
		{
			cout << "C " << i << endl;
			return; 
		}
	}

	vector<int> primo;
	for (int i = 318; i <= n; i++)
		if (!mark[i])
			primo.push_back(i);

	int sobra = primo.size()+1;

	for (int i = 0; i < primo.size(); i += 100)
	{
		vector<int> aux;

		int tot = 0;

		for (int j = i; j < min((int)primo.size(), i+100); j++)
		{
			cout << "B " << primo[j] << endl;
			int x;
			cin >> x;
			++tot;
		}

		int x;
		cout << "A 1" << endl;
		cin >> x;

		if (x != sobra-tot)
		{
			for (int j = i; j < min((int)primo.size(), i+100); j++)
			{
				cout << "A " << primo[j] << endl;
				int x;
				cin >> x;

				if (x != 0)
				{
					cout << "C " << primo[j] << endl;
					return;
				}
			}
		}

		sobra -= tot;
	}

	cout << "C 1" << endl;
	return;
}

int main(void)
{
	sieve();
	cin >> n;

	vector<int> primo;
	for (int i = 2; i <= n; i++)
		if (!mark[i])
			primo.push_back(i);

	int last;
	for (int i = 0; i < primo.size() && primo[i] <= min(n, 317); i++)
	{
		last = primo[i];
		for (int j = primo[i]; j <= n; j += primo[i])
			mark2[j] = 1;
	}

	int tot = 0;
	for (int i = 2; i <= n; i++)
		if (mark2[i])
			++tot;

	for (int i = 0; i < primo.size() && primo[i] <= min(n, 317); i++)
	{
		cout << "B " << primo[i] << endl;
		int x;
		cin >> x;
	}

	int sobra;
	cout << "A 1" << endl;
	cin >> sobra;

	if (sobra == n-tot)
	{
		solve_primo();
		return 0;
	}

	vector<int> D;

	for (auto p: primo)
	{
		cout << "A " << p << endl;

		int x;
		cin >> x;

		if (p <= last)
		{
			if (x == 1) D.push_back(p);
		}
		else
		{
			if (x == 2) D.push_back(p);
		}
	}

	int ans = 1;

	for (auto p: D)
	{
		long long at = 1;

		for (int i = 1; i <= 40; i++)
		{
			at *= 1ll*p;
			if (at > n)
			{
				at /= p;
				break;
			}

			cout << "A " << at << endl;
			int x;
			cin >> x;

			if (x == 0)
			{
				at /= 1ll*p;
				break;
			}
		}

		ans *= at;
	}

	cout << "C " << ans << endl;
}
