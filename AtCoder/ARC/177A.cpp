// ARC 177A - Exchange
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

int v[] = {1, 5, 10, 50, 100, 500};
int qtd[7];

int main(void)
{
	for (int i = 0; i < 6; i++)
		cin >> qtd[i];

	int n;
	cin >> n;

	bool ok = 1;
	while (n--)
	{
		int k;
		cin >> k;

		for (int i = 5; i >= 0; i--)
		{
			while (k >= v[i] and qtd[i] > 0)
			{
				k -= v[i];
				qtd[i]--;
			}
		}

		if (k)
		{
			ok = 0;
			break;
		}
	}

	if (ok) cout << "Yes\n";
	else cout << "No\n";
}
