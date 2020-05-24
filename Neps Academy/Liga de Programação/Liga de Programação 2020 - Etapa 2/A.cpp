// Neps Academy - Liga de Programação 2020 - Etapa 2 - Grupo de Estudos
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int n;
	scanf("%d", &n);

	set<int> st;
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		st.insert(x);
	}

	printf("%d\n", st.size());
}
