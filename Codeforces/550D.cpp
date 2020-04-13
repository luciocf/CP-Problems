// Codeforces 550D - Regular Bridge
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e6+10;
 
typedef pair<int, int> pii;
 
int main(void)
{
	int k;
	scanf("%d", &k);
 
	if (k%2 == 0)
	{
		printf("NO\n");
		return 0;
	}
 
	vector<pii> edge;
 
	int n = 1;
	for (int i = 1; i <= k-1; i++)
		edge.push_back({1, ++n});
 
	vector<int> grupo[k+1];
 
	for (int i = 2; i <= k; i++)
	{
		for (int j = 1; j <= k-1; j++)
		{
			edge.push_back({i, ++n});
			grupo[i-1].push_back(n);
		}
	}
 
	for (int i = 1; i <= k-1; i++)
	{
		for (int j = i+1; j <= k-1; j++)
			for (int l = 0; l < k-1; l++)
				edge.push_back({grupo[i][l], grupo[j][l]});
		
		for (int l = 0; l < k-2; l += 2)
			edge.push_back({grupo[i][l], grupo[i][l+1]});
	}
 
	++n;
	edge.push_back({1, n});
 
	int x = n;
 
	for (int i = 1; i <= k-1; i++)
		edge.push_back({x, ++n});
 
	vector<int> grupo2[120];
 
	for (int i = 1; i < k; i++)
	{
		for (int j = 1; j <= k-1; j++)
		{
			edge.push_back({i+x, ++n});
			grupo2[i].push_back(n);
		}
	}
 
	for (int i = 1; i <= k-1; i++)
	{
		for (int j = i+1; j <= k-1; j++)
			for (int l = 0; l < k-1; l++)
				edge.push_back({grupo2[i][l], grupo2[j][l]});
		
		for (int l = 0; l < k-2; l += 2)
			edge.push_back({grupo2[i][l], grupo2[i][l+1]});
	}
 
	printf("YES\n");
	printf("%d %d\n", n, (int)edge.size());
 
	for (auto e: edge)
		printf("%d %d\n", e.first, e.second);
}
