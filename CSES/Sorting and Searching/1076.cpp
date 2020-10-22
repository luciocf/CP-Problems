// CSES 1076 - Sliding Median
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e5+10;
 
int a[maxn];

multiset<int> menor, maior;

void add(int v)
{
	int tot = menor.size() + maior.size();

	if (tot % 2)
	{
		if (v >= *maior.begin())
		{
			menor.insert(*maior.begin());
			maior.erase(maior.begin());
			maior.insert(v);
		}
		else menor.insert(v);
	}
	else
	{
		if (maior.size() == 0 || v >= *menor.rbegin()) maior.insert(v);
		else
		{
			maior.insert(*menor.rbegin());
			menor.erase(menor.find(*menor.rbegin()));
			menor.insert(v);
		}
	}
}

void remove(int v)
{
	int tot = menor.size() + maior.size();

	if (tot % 2)
	{
		if (maior.find(v) != maior.end()) maior.erase(maior.find(v));
		else
		{
			menor.erase(menor.find(v));
			menor.insert(*maior.begin());
			maior.erase(maior.begin());
		}
	}
	else
	{
		if (menor.find(v) != menor.end()) menor.erase(menor.find(v));
		else
		{
			maior.erase(maior.find(v));
			maior.insert(*menor.rbegin());
			menor.erase(menor.find(*menor.rbegin()));
		}
	}
}

int get(void)
{
	int tot = menor.size() + maior.size();

	if (tot % 2) return *maior.begin();
	return *menor.rbegin();
}

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= k; i++)
		add(a[i]);

	printf("%d ", get());

	for (int i = k+1; i <= n; i++)
	{
		remove(a[i-k]);
		add(a[i]);
		printf("%d ", get());
	}

	printf("\n");
}
