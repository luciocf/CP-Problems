// ARC 174D - Digit vs Square Root
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		ll n;
		cin >> n;

		ll b = 10;
		ll ans = 1;

		for (int i = 1; i <= 9; i++)
		{
			if (b*b <= n) // 10
				ans += min(n-b*b+1, b);

			if ((b-1)*(b-1)+b-1 <= n) // 99
				ans += min(n-(b-1)*(b-1)-b+2, b);

			if ((b-1)*(b-1)-1 <= n) // 98
				ans++;

			b *= 10ll;
		}

		cout << ans << "\n";
	}	
}
