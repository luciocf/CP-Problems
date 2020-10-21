// CSES 1163 - Traffic Lights
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
int main(void)
{
	int x, n;
	scanf("%d %d", &x, &n);
 
	multiset<int> st1, st2;
 
	st1.insert(0); st2.insert(x);
 
	for (int i = 1; i <= n; i++)
	{
		int p;
		scanf("%d", &p);
 
		int r = x, l = 0;
 
		auto it = st1.upper_bound(p);
 
		if (it != st1.end())
			r = *it;
 
		if (it != st1.begin())
		{
			--it;
			l = *it;
		}
 
		st1.insert(p);
 
		st2.erase(st2.find(r-l));
		st2.insert(r-p); st2.insert(p-l);
 
		printf("%d ", *st2.rbegin());
	}
	
	printf("\n");
}
