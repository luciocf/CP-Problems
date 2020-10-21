// CSES 1141 - Playlist
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

int a[maxn];

map<int, int> fq;

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	int ptr = 1, ans = 1;
	fq[a[1]]++;

	for (int i = 1; i <= n; i++)
	{
		while (ptr < n && fq[a[ptr+1]] == 0)
			fq[a[++ptr]]++;

		ans = max(ans, ptr-i+1);

		fq[a[i]]--;
		
		if (ptr == i)
		{
			fq[a[i+1]]++;
			ptr++;
		}
	}

	printf("%d\n", ans);
}
