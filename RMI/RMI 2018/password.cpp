// RMI 2018 - Password
// Lúcio Cardoso

// Solution:

// Precalculate the frequencies of each letter in O(sigma). Next, iterate through each character from a to z.
// Suppose we're at character c. We will maintain the substring of the answer formed by characters from 'a' to (c-1).
// Call this string S.

// Maintain a variable tot which keeps the amount of letters c inserted so far (at first, tot = 0). Binary search
// the last index i in S such that the query of the concatenation of (S[0..i] + ccc..cc (freq[c] times)) is > (i+1 + tot).
// That means that between the indices i and i+1 there is a positive amount of letters c. After finding this i,
// increase tot by the amount of letters c between i and i+1. Repeat the algorithm until tot = freq[c] or until
// the remaining letters c are before position 0 in S.

// After executing the algorithm for the character c, update S by inserting c in every position found in the binary search.
// The complexity of queries is O(n * log n), but in practice, the amount is smaller and is even smaller if we memorize the
// answer of queries (S[0..i] + ccc.ccc (freq[c] times)) for every i while executing the algorithm in character c (i.e we don't
// ask a query more than once for each c, we ask it once and then memorize it in an array). This is sufficient for 100 points.

#include <bits/stdc++.h>

using namespace std;

int query(string str);

int freq[27];
int nxt[5010];
int mark[5010];

string ans = "";

int qtd(int pos, char c)
{
	if (mark[pos] != -1) return mark[pos];

	string aux = "";

	for (int i = 0; i <= pos; i++)
		aux += ans[i];

	for (int i = 0; i < freq[(int)(c-'a')]; i++)
		aux += c;

	return mark[pos] = (query(aux) - (pos+1));
}

string guess(int n, int s)
{
	freq[s-1] = n;

	for (int i = 0; i < s-1; i++)
	{
		char c = (char)('a'+i);
		string aux = "";

		for (int j = 0; j < n; j++)
			aux += c;

		freq[i] = query(aux);
		freq[s-1] -= freq[i];
	}

	for (int i = 0; i < s; i++)
	{
		if (!freq[i]) continue;

		memset(nxt, 0, sizeof nxt);
		memset(mark, -1, sizeof mark);

		char c = (char)('a'+i);
		int tot = 0;

		if (ans.empty())
		{
			for (int j = 0; j < freq[i]; j++)
				ans += c;
			continue;
		}

		int last = ans.size()-1;

		while (true)
		{
			int ini = 0, fim = last, ind = -1;

			if (tot < freq[i] && qtd(0, c) > tot)
			{
				while (ini <= fim)
				{
					int mid = (ini+fim)>>1;

					if (qtd(mid, c) > tot) ind = mid, ini = mid+1;
					else fim = mid-1;
				}
			}

			if (ind == -1)
			{
				string aux = "";

				for (int j = 0; j < freq[i]-tot; j++)
					aux += c;

				for (int j = 0; j < ans.size(); j++)
				{
					aux += ans[j];

					for (int l = 0; l < nxt[j]; l++)
						aux += c;
				}
				swap(ans, aux);

				break;
			}

			nxt[ind] = qtd(ind, c)-tot;
			tot = qtd(ind, c);
			last = ind-1;
		}
	}

	return ans;
}
