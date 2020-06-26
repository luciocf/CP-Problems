// CSAcademy - ROJS 2017 - Borland
// Lúcio Cardoso

// Solution is the same as in editorial, except I didn't use modular inverse to find each value.
// My method was: Calculate all the values in V[] in O(n) and store every 7 of them in an array. This
// way, the memory used is just under 3000kb and we can find the value of each V[i] with at most 7 iterations.

#include <bits/stdc++.h>

using namespace std;

const int bucket = 428575;
const int mod = 1e9+7;

int n, s, a, b, c;
int ans;

int B[bucket];

int get(int l)
{
	int id = l/7;

	if (id == 0)
	{
		int x = s;
		for (int i = 1; i <= l; i++)
			x = (1ll*a*x + 1ll*b)%c;

		return x;
	}

	int x = B[id-1];

	for (int i = id*7; i <= l; i++)
		x = (1ll*a*x + 1ll*b)%c;

	return x;
}

void solve(int l, int r)
{
	if (l > r) return;

	int mid = (l+r)>>1;

	int ptr_l = mid, ptr_r = mid;
	int mx_l = get(mid), mx_r = 0;

	while (ptr_r <= r)
	{
		mx_r = max(mx_r, get(ptr_r));

		while (ptr_l > l && max(mx_l, get(ptr_l-1)) <= mx_r)
		{
			mx_l = max(mx_l, get(ptr_l-1));
			ptr_l--;
		}

		if (mx_r >= mx_l) ans = (1ll*ans + 1ll*(mid-ptr_l+1)*mx_r)%mod;

		++ptr_r;
	}

	ptr_l = mid, ptr_r = mid;
	mx_l = 0, mx_r = get(mid);

	while (ptr_l >= l)
	{
		mx_l = max(mx_l, get(ptr_l));

		while (ptr_r < r && max(mx_r, get(ptr_r+1)) < mx_l)
		{
			mx_r = max(mx_r, get(ptr_r+1));
			ptr_r++;
		}

		if (mx_l > mx_r) ans = (1ll*ans + 1ll*(ptr_r-mid+1)*mx_l)%mod;

		--ptr_l;
	}

	solve(l, mid-1); solve(mid+1, r);

}

int main(void)
{
	scanf("%d %d %d %d %d", &n, &s, &a, &b, &c);

	int id = 0;
	int x = s;

	for (int i = 1; i < n; i++)
	{
		x = (1ll*a*x + 1ll*b)%c;

		if (i%7 == 6)
			B[id++] = x;
	}

	solve(0, n-1);

	printf("%d\n", ans);
}
