// CSES 1641 - Sum of Three Values
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 5e3+10;
 
pair<int, int> a[maxn];
 
int main(void)
{
	int n, x;
	scanf("%d %d", &n, &x);
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].first);
		a[i].second = i;
	}
 
	for (int i = 1; i <= n; i++)
	{
		int ptr1 = 1, ptr2 = i-1;
		int k = x-a[i].first;
 
		while (ptr1 < ptr2)
		{
			if (a[ptr1].first + a[ptr2].first == k)
			{
				printf("%d %d %d\n", a[ptr1].second, a[ptr2].second, a[i].second);
				return 0;
			}
 
			if (a[ptr1].first + a[ptr2].first > k) ptr2--;
			else ptr1++;
		}
 
		for (int j = i; j > 1; j--)
		{
			if (a[j].first > a[j-1].first) break;
 
			swap(a[j], a[j-1]);
		}
	}
 
	printf("IMPOSSIBLE\n");
}
