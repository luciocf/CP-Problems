// Timus 1091 - Tmutarakan Exams
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 51;
const int maxv = 10000;

int k, S, ans;
vector<int> primes;

int gcd(int a, int b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

bool ok(int qtd, int x, int g)
{
	for (auto p: primes)
		if (g%p == 0 and S/p - (x-1)/p >= qtd)
			return true;
	return false;
}

void solve(int qtd, int x, int g)
{
	if (ans >= maxv) return;
	if (qtd == 0)
	{
		ans++;
		return;
	}

	for (int y = x+1; y <= S; y++)
	{
		int gp = gcd(g, y);

		if (gp > 1 and ok(qtd, y, gp))
			solve(qtd-1, y, gp);
	}
}

int main(void)
{
	cin >> k >> S;
	for (int i = 2; i <= S; i++)
	{
		bool ok = 1;
		for (int j = 2; j < i; j++)
			if (i%j == 0)
				ok = 0;

		if (ok) primes.push_back(i);
	}

	for (int i = 2; i <= S-k+1; i++)
		solve(k-1, i, i);

	cout << min(ans, maxv) << "\n";
}
