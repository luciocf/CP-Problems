// CCO 2018 - Boring Lectures
// Lúcio Cardoso

// Solution:

// 1. Divide the queries in sqrt(q) blocks. For every block of queries, mark the
// positions that were updated in one of the queries inside the block. We can
// find the maximum answer using only unmarked positions in O(n) using a monotonic
// queue. Also, with the same queue, we can find the maximum unmarked value that
// a marked value can use.

// 2. The answers we found using only unmarked positions are valid for all queries
// in the block (i.e the answer for all positions in the block is at least that).
// Also, we've already found the maximum unmarked value for every marked position.
// Thus, we now only need to find the answer using two marked positions. This can be done
// using another monotic queue in the marked positions, by sorting them beforehand.

// Complexity for calculating answer with unmarked positions: O(N * sqrt(Q))
// Complexity for calculating answer with marked positions: O(N*sqrt(Q) + Q*sqrt(Q))

#include <bits/stdc++.h>

#define gc getchar_unlocked

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e6+10;
const int maxq = 1e5+10;
const int bucket = 1000;

int n, k, q;
int val[maxn];

int maximo[maxn];

int ans[maxq];

bool mark[maxn];

pii qry[maxq];

inline int get_resp(void)
{
	int resp = 0;

	deque<pii> dq;

	for (int i = 1; i <= n; i++)
	{
		while (dq.size() && i-dq.back().ss >= k)
			dq.pop_back();

		if (mark[i])
		{
			if (dq.size())
				maximo[i] = max(maximo[i], dq.back().ff);
			continue;
		}

		if (dq.size())
			resp = max(resp, val[i]+dq.back().ff);

		while (dq.size() && dq.front().ff <= val[i])
			dq.pop_front();

		dq.push_front({val[i], i});
	}

	dq.clear();

	for (int i = n; i >= 1; i--)
	{
		while (dq.size() && dq.back().ss-i >= k)
			dq.pop_back();

		if (mark[i])
		{
			if (dq.size())
				maximo[i] = max(maximo[i], dq.back().ff);
			continue;
		}

		if (dq.size())
			resp = max(resp, val[i]+dq.back().ff);

		while (dq.size() && dq.front().ff <= val[i])
			dq.pop_front();

		dq.push_front({val[i], i});
	}

	return resp;
}

void scan(int &x)
{
    int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

inline void print(int n)
{
	if (n == 0)
	{
		putchar_unlocked('0');
		putchar_unlocked('\n');
	}
	else
	{
		char buf[11];
		buf[10] = '\n';
		int i = 9;
		while (n)
		{
			buf[i--] = n % 10 + '0';
			n /= 10;
		}
		while (buf[i] != '\n') putchar_unlocked(buf[++i]);
	}
}

int main(void)
{
	scan(n), scan(k), scan(q);

	for (int i = 1; i <= n; i++)
		scan(val[i]);

	qry[0] = {1, val[1]};
	for (int i = 1; i <= q; i++)
		scan(qry[i].ff), scan(qry[i].ss);

	for (int i = 0; i <= q; i += bucket)
	{
		int b = i/bucket;
		int last = min((b+1)*bucket, q+1);

		vector<int> fora;

		for (int j = i; j < last; j++)
		{
			if (!mark[qry[j].ff])
				fora.push_back(qry[j].ff);

			mark[qry[j].ff] = true;
		}

		sort(fora.begin(), fora.end());

		int resp = get_resp();

		for (int j = i; j < last; j++)
		{
			ans[j] = resp;
			val[qry[j].ff] = qry[j].ss;

			mark[qry[j].ff] = false;

			deque<pii> dq;

			for (auto p: fora)
			{
				while (dq.size() && p-dq.back().ss >= k)
					dq.pop_back();

				if (dq.size())
					ans[j] = max(ans[j], val[p]+dq.back().ff);

				while (dq.size() && dq.front().ff <= val[p])
					dq.pop_front();

				dq.push_front({val[p], p});
			}

			dq.clear();

			for (int l = fora.size()-1; l >= 0; l--)
			{
				int p = fora[l];

				while (dq.size() && dq.back().ss-p >= k)
					dq.pop_back();

				if (dq.size())
					ans[j] = max(ans[j], val[p]+dq.back().ff);

				while (dq.size() && dq.front().ff <= val[p])
					dq.pop_front();

				dq.push_front({val[p], p});
			}

			for (int l = i; l < last; l++)
				ans[j] = max(ans[j], val[qry[l].ff] + maximo[qry[l].ff]);
		}

		for (int j = i; j < last; j++)
			maximo[qry[j].ff] = 0;
	}

	for (int i = 0; i <= q; i++)
		print(ans[i]);
}
