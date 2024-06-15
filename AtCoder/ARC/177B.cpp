// ARC 177B - Puzzle of Lamps
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

int main(void)
{
	int n;
	string s;
	cin >> n >> s;

	vector<char> ans;

	for (int i = n-1; i >= 0; i--)
	{
		if (s[i] == '1')
		{
			for (int j = 0; j <= i; j++)
				ans.push_back('A');
			for (int j = 0; j < i; j++)
				ans.push_back('B');
		}
	}

	cout << ans.size() << "\n";
	for (auto c: ans)
		cout << c;
	cout << "\n";
}
