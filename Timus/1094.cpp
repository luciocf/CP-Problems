// Timus 1094 - Not So Simple Years
// Lucio Figueiredo

// Same as OBI 2016 - Quase Primo!
// Numbers of primes < k whose product is less than A+B is small, so just recurse
// and use inclusion-exclusion

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

vector<int> primes;

int tot;
int n;

void solve(int ind, int prod, int qtd)
{
	if (ind == primes.size())
	{
		int sign = -1;
		if (qtd == 0) sign = 0;
		else if (qtd%2) sign = 1;
		tot += sign*(n/prod);
		return;
	}

	if (1ll*prod*primes[ind] <= 1ll*n) solve(ind+1, prod*primes[ind], qtd+1);
	solve(ind+1, prod, qtd);
}

bool prime(int x)
{
	for (int i = 2; i < x; i++)
		if (x%i == 0)
			return 0;
	return 1;
}

int main(void)
{
	int a, b, k;
	cin >> a >> b >> k;
	k++;

	for (int i = 2; i <= k; i++)
		if (prime(i))
			primes.push_back(i);

	n = a+b;
	solve(0, 1, 0);

	int ans = tot;
	tot = 0, n = a;
	solve(0, 1, 0);
	ans -= tot;

	for (auto p: primes)
		if (p > a and p <= a+b)
			ans--;

	cout << b-ans << "\n";
}
