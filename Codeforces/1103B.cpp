// Codeforces 1103B - Game with modulo
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>
 
using namespace std;
 
int at, k;
 
bool ask(int x, int y)
{
	cout << "? " << x << " " << y << endl;
 
	char c;
	cin >> c;
 
	return (c == 'x' ? 0 : 1);
}
 
int main(void)
{
	while (true)
	{
		string s;
		cin >> s;
 
		if (s[0] == 'e') break;
 
		at = k = 0;

		for (int i = 0; i <= 30; i++)
		{
			k = at+(1<<i);
 
			if (ask(at, at+(1<<i))) at += (1<<i);
			else break;
		}
 
		int ini = 1, fim = k-at, ans = at;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;
 
			if (ask(at, at+mid)) ans = at+mid, ini = mid+1;
			else fim = mid-1;
		}
 
		cout << "! " << ans+1 << endl;
	}
}
