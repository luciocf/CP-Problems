// CSES 1077 - Sliding Cost
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e5+10;
 
int a[maxn];

multiset<int> menor, maior;
ll soma_maior, soma_menor;

void add(int v)
{
	int tot = menor.size() + maior.size();

	if (tot % 2)
	{
		if (v >= *maior.begin())
		{
			menor.insert(*maior.begin()); soma_menor += 1ll*(*maior.begin());
			soma_maior -= 1ll*(*maior.begin()); maior.erase(maior.begin());
			maior.insert(v); soma_maior += 1ll*v;
		}
		else
		{
			menor.insert(v); soma_menor += 1ll*v;
		}
	}
	else
	{
		if (maior.size() == 0 || v >= *menor.rbegin())
		{
			maior.insert(v); soma_maior += 1ll*v;
		}
		else
		{
			maior.insert(*menor.rbegin()); soma_maior += 1ll*(*menor.rbegin());
			soma_menor -= 1ll*(*menor.rbegin()); menor.erase(menor.find(*menor.rbegin()));
			menor.insert(v); soma_menor += 1ll*v;
		}
	}
}

void remove(int v)
{
	int tot = menor.size() + maior.size();

	if (tot % 2)
	{
		if (maior.find(v) != maior.end())
		{
			soma_maior -= 1ll*v; maior.erase(maior.find(v));
		}
		else
		{
			soma_menor -= 1ll*v; menor.erase(menor.find(v));
			menor.insert(*maior.begin()); soma_menor += 1ll*(*maior.begin());
			soma_maior -= 1ll*(*maior.begin()); maior.erase(maior.begin());
		}
	}
	else
	{
		if (menor.find(v) != menor.end())
		{
			soma_menor -= 1ll*v; menor.erase(menor.find(v));
		}
		else
		{
			soma_maior -= 1ll*v; maior.erase(maior.find(v));
			maior.insert(*menor.rbegin()); soma_maior += 1ll*(*menor.rbegin());
			soma_menor -= 1ll*(*menor.rbegin()); menor.erase(menor.find(*menor.rbegin()));
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

	printf("%lld ", 1ll*menor.size()*get() + soma_maior - soma_menor - 1ll*maior.size()*get());

	for (int i = k+1; i <= n; i++)
	{
		remove(a[i-k]);
		add(a[i]);

		printf("%lld ", 1ll*menor.size()*get() + soma_maior - soma_menor - 1ll*maior.size()*get());
	}

	printf("\n");
}
