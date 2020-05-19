// CEOI 2018 - Toys
// Lúcio Cardoso

// Solution:

// Notice the problem asks for the possible values k such that there are numbers {a_1, a_2, ..., a_r}
// satisfying the properties:
//	* a_1 + a_2 + ... + a_r = k
//  * (a_1 + 1)*(a_2 + 1)*...*(a_r + 1) = n
//  * every (a_i+1) divides n

// To find this, store all the divisors of n in an array 'd' and use a recursive function f(ind, prod, sum)
// which iterates through all indices 'ind' in 'd' and tries to create a possible solution, storing
// the current product of chosen divisors in 'prod' and the sum of each (divisor-1) in 'sum'.

// To improve this backtracking solution, sort the divisors in decreasing order and only multiply 'prod'
// by a divisor d[ind] if the number prod*d[ind] is a divisor of n. This should get 100 pts.

#include <bits/stdc++.h>
 
using namespace std;
 
int n;
vector<int> d;
 
set<int> ans;
 
bool comp(int a, int b) {return a > b;}
 
void f(int ind, int prod, int soma)
{
	if (ind >= d.size()) return;
 
	if (prod == n)
	{
		ans.insert(soma);
		return;
	}
 
	if (1ll*prod*d[ind] <= 1ll*n && (n%(prod*d[ind]) == 0))
		f(ind, prod*d[ind], soma+d[ind]-1);
 
	f(ind+1, prod, soma);
}
 
int main(void)
{
	scanf("%d", &n);
 
	for (int i = 2; i*i <= n; i++)
	{
		if (n%i) continue;
 
		d.push_back(i);
		if (n/i != i) d.push_back(n/i);
	}
 
	d.push_back(n);
	sort(d.begin(), d.end(), comp);
 
	f(0, 1, 0);
 
	printf("%d\n", ans.size());
	for (auto x: ans)
		printf("%d ", x);
	printf("\n");
}
