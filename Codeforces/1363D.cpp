// Codeforces 1363D - Guess The Maximums
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e3+10;
 
vector<int> S[maxn];
 
bool mark[maxn];
 
int main(void)
{
	int t;
	cin >> t;
 
	while (t--)
	{
		int n, k;
		cin >> n >> k;
 
		for (int i = 1; i <= k; i++)
			S[i].clear();
		memset(mark, 0, sizeof mark);
 
		for (int i = 1; i <= k; i++)
		{
			int c;
			cin >> c;
 
			for (int j = 1; j <= c; j++)
			{
				int x;
				cin >> x;
 
				S[i].push_back(x);
				mark[x] = 1;
			}
		}
 
		cout << "? " << n;
		for (int i = 1; i <= n; i++)
			cout << " " << i;
		cout << "\n"; fflush(stdout);
 
		int mx;
		cin >> mx;
 
		int ini = 1, fim = k, ans = -1;
 
		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;
 
			int tot = 0;
			for (int i = 1; i <= mid; i++)
				tot += (int)S[i].size();
 
			cout << "? " << tot;
			for (int i = 1; i <= mid; i++)
			{
				for (auto l: S[i])
					cout << " " << l;
			}
			cout << "\n"; fflush(stdout);
 
			int aux;
			cin >> aux;
 
			if (aux == mx) ans = mid, fim = mid-1;
			else ini = mid+1;
		}
 
		if (ans == -1)
		{
			cout << "!";
			for (int i = 1; i <= k; i++)
				cout << " " << mx;
			cout << "\n"; fflush(stdout); 
		}
		else
		{
			int tot = n - S[ans].size();
 
			cout << "? " << tot;
 
			for (int i = 1; i <= n; i++)
				if (!mark[i])
					cout << " " << i;
				
			for (int i = 1; i <= k; i++)
			{
				if (i != ans)
				{
					for (auto l: S[i])
						cout << " " << l;
				}
			}
			cout << "\n"; fflush(stdout);
 
			int l;
			cin >> l;
 
			cout << "!";
			for (int i = 1; i <= k; i++)
			{
				if (i == ans) cout << " " << l;
				else cout << " " << mx;
 			}
 			cout << "\n"; fflush(stdout);
		}
 
		string final;
		cin >> final;
	}
}
