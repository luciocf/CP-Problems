// Codeforces 1370E - Binary Subsequence Rotation
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int main(void)
{
	int m;
	cin >> m;
	string s, t;
	cin >> s >> t;

	string a;

	for (int i = 0; i < s.size(); i++)
		if (s[i] != t[i])
			a += s[i];

	int q0 = 0, q1 = 0;
	int n = a.size();

	for (int i = 0; i < n; i++)
	{
		if (a[i] == '0') q0++;
		else q1++;
	}

	if (q0 != q1)
	{
		cout << "-1\n";
		return 0;
	}

	int ans = 0;

	set<int> zero, um;

	for (int i = 0; i < n; i++)
	{
		if (a[i] == '0') zero.insert(i);
		else um.insert(i);
	}


	for (int i = 0; i < n; i++)
	{
		if (a[i] == '0' && zero.find(i) == zero.end()) continue;
		if (a[i] == '1' && um.find(i) == um.end()) continue;

		++ans;

		int last;

		if (a[i] == '0')
		{
			last = *um.rbegin();
			um.erase(last);
		}
		else
		{
			last = *zero.rbegin();
			zero.erase(last);
		}

		int at = (a[i] == '0' ? 0 : 1);
		int pos = i;

		while (true)
		{
			if (at == 0)
			{
				zero.erase(pos);

				if (um.lower_bound(pos) == um.end() || *um.lower_bound(pos) > last) break;
				else pos = *um.lower_bound(pos);
			}
			else
			{
				um.erase(pos);

				if (zero.lower_bound(pos) == zero.end() || *zero.lower_bound(pos) > last) break;
				else pos = *zero.lower_bound(pos);
			}

			at = !at;
		}

		if (at == 1 && a[last] == '1') um.insert(last);
		if (at == 0 && a[last] == '0') zero.insert(last);
	}

	cout << ans << "\n";
}
