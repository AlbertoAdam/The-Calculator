#include <iostream>
#include <string>
#include <iomanip>
#include "Evaluator.h"

using namespace std;

// 5/(4-16/4)
// ((32+2*2)/4#2)/4^2
// ((5+2]*3)
// [1.15+(((13+1)*0.5)+3)]-100
// [40+(5-1)]*2
// 5/0
// [(2*3)^2]/4-(6+2)#3
// 2 * 3.2
// 24342343.0002-3
// 2 *    3 - 8

int main()
{
	string ecuatie;
	while (1)
	{
		getline(cin, ecuatie);
		if (ecuatie == "exit") {
			break;
		}
		Evaluator l(ecuatie.c_str());
		l.CreazaListe();
		double ans = l.Evalueaza();

		if (!l)
		{
			cout << (const char*) l << "\n\n";
			continue;
		}

		cout << fixed << setprecision(6) << "Rezultatul este: " << ans << "\n\n";
	}
}

