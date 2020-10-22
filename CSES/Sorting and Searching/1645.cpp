// CSES 1645 - Nearest Smaller Values
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second

using namespace std;
 
typedef pair<int, int> pii;
 
int main(void)
{
	int n;
	scanf("%d", &n);

	stack<pii> stk;

	for (int i = 1; i <= n; i++)
	{
		int v;
		scanf("%d", &v);

		while (stk.size() && stk.top().ff >= v)
			stk.pop();

		if (stk.size()) printf("%d ", stk.top().ss);
		else printf("0 ");

		stk.push({v, i});
	}

	printf("\n");
}
