//
//  main.cpp
//  CalcLib
//
//  Created by Maxime Perrin on 26/05/2020.
//  Copyright © 2020 Maxime Perrin. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#include "fonctions.h"

int main(int argc, const char * argv[]) {
	

	lentier s;
	lentier a;
	lentier b;
	lentier n;

	res_div res;

	char* saisieUtilisateur = new char[200];
	char** chaineParse;
	

	start:cin >> saisieUtilisateur;

	chaineParse = parser(saisieUtilisateur);

	a = dec2lentier(chaineParse[0]);

	b = dec2lentier(chaineParse[2]);

	switch(chaineParse[1][0]){
		case '+':
			s = add_lentier(a,b);
			break;
		case '-':
			s = sub_lentier(a,b);
			break;
		case '*':
			if (chaineParse[3][0] == 'm')
			{
				s = mul_mod(a,b, dec2lentier(chaineParse[4]));
			}
			else {
				s = mult_classique(a,b);
			}
			break;
		case '/':
			if (b.size == 1) {
				res = div_eucl_1case(a, b);
				s = estEgal(res.q);
				delete[] res.r.p;
				delete[] res.q.p;
			}
			else {
				res = div_eucl(a, b);
				s = estEgal(res.q);
				delete[] res.r.p;
				delete[] res.q.p;
			}
			break;
		case 'm':
			res = div_eucl(a,b);
			s = estEgal(res.r);
			delete[] res.r.p;
			delete[] res.q.p;
			break;
		case '^' :
			s = exp_mod(a,b, dec2lentier(chaineParse[4]));
			break;
		default:
			std::cout << "Erreur: vous devez entrer une chaîne de forme correcte" << endl;
			goto start;
	}
	std::cout << endl;
	std::cout << "s = ";
	Affiche_lentier(s);


	return 0;
}

