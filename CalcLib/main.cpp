//
//  main.cpp
//  CalcLib
//
//  Created by Maxime Perrin on 26/05/2020.
//  Copyright © 2020 Maxime Perrin. All rights reserved.
//

#include <iostream>

using namespace std;

typedef struct {
    unsigned int* p;
    unsigned int size;
}
lentier;

int getNumbersChar(char* a) {
    return strlen(a);
}

int remplirTab(int taille, char *a) {
    int tailleNombre = taille;
    unsigned int nombre = 0;
    int indice = 0;
    int nombreCase = 0;
    int indicePuissance = 0;
    while (indice<tailleNombre) {
        nombre = 0;
        for (; indice < tailleNombre; indice++) {
            for (int y = indicePuissance; y <= indice; y++) {
                nombre += ((int)a[y]-48) * pow(10, y-indicePuissance);
            }  
            if (nombre >= pow(2, 32) - 1) {
                break;
            }
            
        }
        indicePuissance = indice;
        nombreCase++;
    }
    return nombreCase;
}

int main(int argc, const char * argv[]) {
    
    char* nombre1 = new char[100];
    cin >> nombre1;
    int size = getNumbersChar(nombre1);
    cout << size << endl;

    cout << remplirTab(size, nombre1) << endl;

    lentier a;
    lentier b;
    lentier s;

    a.size = 10;
    a.p = new unsigned int[a.size](); 

    b.size = 10;
    b.p = new unsigned int[b.size];

    for (int i = 0; i < 10; i++) {
        a.p[i] = 9;
        b.p[i] = 9;
        cout << a.p[i];
    }
    cout << endl;
    s.size = 11;
    s.p = new unsigned int[s.size];

    unsigned int c = 0;
    for (int i = s.size-2; i >= 0; i--) {

        s.p[i+1] = (a.p[i] + b.p[i] + c) % 10;

        if (a.p[i] + b.p[i] + c < 10) {

            c = 0;
        }
        else
        {
            c = 1;
        }
    }
    s.p[0] = c;
    for (int i = 0; i < 11; i++) {
        cout << s.p[i];
    }

    delete[] a.p;
    delete[] b.p;
    delete[] s.p;
    return 0;
}



