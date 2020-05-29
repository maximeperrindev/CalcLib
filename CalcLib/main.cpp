//
//  main.cpp
//  CalcLib
//
//  Created by Maxime Perrin on 26/05/2020.
//  Copyright © 2020 Maxime Perrin. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;

#include "fonctions.h"

int main(int argc, const char * argv[]) {
    
    lentier a;
    lentier b;
    lentier s;

   /*char* nombre1 = NULL;
    printf("Entrez un nombre: "); // It can be of any length
    dynamicChar(nombre1);
    printf("Vous avez écrit: %s\n", nombre1);

    char* nombre2 = NULL;
    printf("Entrez un nombre: "); // It can be of any length
    dynamicChar(nombre2);
    printf("Vous avez écrit: %s\n", nombre2);

    checkCharLength(nombre1, nombre2);
    printf("Vous avez écrit: %s %s\n", nombre1, nombre2);
    a.size = tailleBase(getNumbersChar(nombre1), nombre1);
    a.p = new unsigned int[a.size]();

    remplirTableau(getNumbersChar(nombre1), a.size, nombre1, a.p);
    /*for (int i = 0; i < a.size; i++) {
        cout << a.p[i] << endl;
    } 

    b.size = tailleBase(getNumbersChar(nombre2), nombre2);
    

    //remplirTableau(getNumbersChar(nombre2), b.size, nombre2, b.p);
    for (int i = 0; i < b.size; i++) {
        cout << b.p[i] << endl;
    }*/
    unsigned int tab1[3] = { 0, 0, 3 };
    unsigned int tab2[3] = {0xFFFFFFFF, 0xFFFFFFFF, 2};
    a.size = 3;
    b.size = 3;
    a.p = tab1;
    b.p = tab2;
    
    if (a.size < b.size) {
        s.size = b.size + 1;
    }
    else {
        s.size = a.size + 1;
    }
    s.p = new unsigned int[s.size]();

	int choix_user = 0;
	int fini = 0;
	cout << endl;
	cout << "Voulez-vous additionner (entrez 1) ou les soutraire (entrez 2)?" << endl;
	cin >> choix_user;
	while (fini != 1) {
		if (choix_user == 1) {
			//Addition
			s = addition(a, b);
			
			fini = 1;

		}
		else if (choix_user == 2) {
			//Soustraction
            s = soustraction(a, b);

			fini = 1;
		}
		else {
			cout << "Erreur: vous devez entrer 1 ou 2" << endl;
		}
	}
	//Résultat opération
	for (int i = 0; i < s.size; i++) {
        cout << s.p[i] << endl;
	}

    delete[] a.p;
    delete[] b.p;
    delete[] s.p;
    return 0;
}
 


