// POI 2015 - Three
// Lúcio Cardoso

// The observation required is that if [i, j] is the best interval (in case there are many, choose
// the one with smallest i), then either i <= 3 or j >= n-2. After this observation, run an O(n)
// loop to find the largest interval starting from either one of the 6 possible i or j values.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int n;
int a[maxn];

int freq[3];

int get_pref(int l)
{
	memset(freq, 0, sizeof freq);
	int ans = 0;

	for (int i = l; i <= n; i++)
	{
		freq[a[i]]++;

		if (freq[0] != freq[1] && freq[0] != freq[2] && freq[1] != freq[2])
			ans = max(ans, i-l+1);

		if ((!freq[0] && !freq[1]) || (!freq[0] && !freq[2]) || (!freq[1] && !freq[2]))
			ans = max(ans, i-l+1);
	}

	return ans;
}

int get_suf(int r)
{
	memset(freq, 0, sizeof freq);
	int ans = 0;

	for (int i = r; i >= 1; i--)
	{
		freq[a[i]]++;

		if (freq[0] != freq[1] && freq[0] != freq[2] && freq[1] != freq[2])
			ans = max(ans, r-i+1);

		if ((!freq[0] && !freq[1]) || (!freq[0] && !freq[2]) || (!freq[1] && !freq[2]))
			ans = max(ans, r-i+1);	
	}

	return ans;
}

int main(void)
{
	scanf("%d", &n);

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		char c;
		scanf(" %c", &c);

		if (c == 'B') a[i] = 0;
		else if (c == 'C') a[i] = 1;
		else a[i] = 2;
	}

	ans = max({get_pref(1), get_pref(2), get_pref(3)});
	ans = max({ans, get_suf(n), get_suf(n-1), get_suf(n-2)});

	printf("%d\n", ans);
}

