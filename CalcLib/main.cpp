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

    char* nombre1 = NULL;
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
    for (int i = 0; i < a.size; i++) {
        cout << a.p[i] << endl;
    }

    b.size = tailleBase(getNumbersChar(nombre2), nombre2);
    b.p = new unsigned int[b.size]();

    remplirTableau(getNumbersChar(nombre2), b.size, nombre2, b.p);
    for (int i = 0; i < b.size; i++) {
        cout << b.p[i] << endl;
    }
    
    if (a.size < b.size) {
        s.size = b.size;
    }
    else {
        s.size = a.size;
    }
    s.p = new unsigned int[s.size]();

   /* unsigned int c = 0;
    for (int i = s.size-2; i >= 0; i--) {

        if (a.size > b.size && i >= b.size) {
            s.p[s.size-1-i] = (a.p[i] + c) % 4294967296;
        }
        else if (b.size > a.size&& i >= a.size) {
            s.p[s.size-1-i] = (b.p[i] + c) % 4294967296;
        }
        else {
            s.p[s.size-1-i] = (a.p[i] + b.p[i] + c) % 4294967296;
        }

        if (a.p[i] + b.p[i] + c < 4294967296) {

            c = 0;
        }
        else
        {
            c = 1;
        }
    }
    s.p[0] = c;
    for (int i = 0; i < s.size; i++) {
        cout << s.p[i];
    }
    */
    int c = 0;
    for (int i = s.size - 1; i >= 0; i--) {

        s.p[i] = (a.p[i] - b.p[i] + c) % 4294967296;

        if (a.p[i] + b.p[i] + c >= 0) {

            c = 0;
        }
        else
        {
            c = -1;
        }
    }

    for (int i = 0; i < s.size; i++) {
        cout << s.p[i];
    }

    delete[] a.p;
    delete[] b.p;
    delete[] s.p;
    delete[] nombre1;
    delete[] nombre2;
    return 0;
}
 


