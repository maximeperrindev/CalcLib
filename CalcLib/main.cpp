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
    
    lentier a;
    lentier b;
    lentier s;

    char* nombre1 = new char[100];
    char* nombre2 = new char[100];

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
    a.p = new unsigned int[5];
    b.p = new unsigned int[3];

    b.size = 3;

    a.size = 5;

    a.p[0] = 0;
    a.p[1] = 0;
    a.p[2] = 0;
    a.p[3] = 0;
    a.p[4] = 1;

    b.p[0] = 0;
    b.p[1] = 0;
    b.p[2] = 1;

    s = division(a, b);

    for (int i = 0; i < s.size; i++) {
        cout << s.p[i] << endl;
    }

    cin >> nombre1;
    cin >> nombre2;

    a.size = floor((getNumbersChar(nombre1) * log(10)) / (32 * log(2))) + 1;
    b.size = floor((getNumbersChar(nombre2) * log(10)) / (32 * log(2))) + 1;

   

    a = repartitionTab(nombre1, a.size);
    b = repartitionTab(nombre2, b.size);

    for (int i = 0; i < a.size; i++) {
        cout << a.p[i] << endl;
    }

	int choix_user = 0;
	cout << endl;
	start:cout << "Voulez-vous additionner (entrez 1), les soutraire (entrez 2), une multiplication (entrez 3) ou une division (entrez 4)?" << endl;
	cin >> choix_user;
    switch(choix_user){
        case 1:
            s = addition(a, b);
            break;
        case 2:
            s = soustraction(a, b);
            break;
        case 3:
            s = multiplication(a, b);
            break;
        case 4: 
            s = division(a, b);
            break;
        default:
            cout << "Erreur: vous devez entrer 1 ou 2" << endl;
            goto start;
    }
    
	//Résultat opération
	for (int i = 0; i < s.size; i++) {
        cout << s.p[i] << endl;
	}

    delete[] s.p;
    return 0;
}
 


