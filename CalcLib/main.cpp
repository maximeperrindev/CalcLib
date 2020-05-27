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

typedef struct {
    unsigned int* p;
    unsigned int size;
}
lentier;

int getNumbersChar(char* a) {
    return strlen(a);
}

int tailleBase(int taille, char *a) {
    unsigned long int nombre = 0;
    int indice = 0;
    int nombreCase = 0;
    int indicePuissance = 0;
    while (indice<taille) {
        nombre = 0;
        for (; indice < taille; indice++) {
            nombre = 0;
            for (int y = indicePuissance; y <= indice; y++) {
                nombre += ((int)a[taille-y-1]-48) * pow(10, y-indicePuissance);
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
void checkCharLength(char* nombre1, char* nombre2){
    int nb1 = getNumbersChar(nombre1);
    int nb2 = getNumbersChar(nombre2);
    if(nb1 > nb2){
        nombre2 = (char*)realloc(nombre2, nb1+1); // Add space for another character to be read.
        int diff = nb1 - nb2;
        for(int i = 0; i <= nb1; i++){
            nombre2[nb1 - i] = nombre2[nb2-i];
        }
        for(int i=0; i<diff; i++){
            nombre2[i] = '0';
        }
    }else if(nb2 > nb1){
        nombre1 = (char*)realloc(nombre1, nb2+1); // Add space for another character to be read.
        int diff = nb2 - nb1;
        for(int i = 0; i <= nb2; i++){
            nombre1[nb2 - i] = nombre1[nb1-i];
        }
        for(int i=0; i<diff; i++){
            nombre1[i] = '0';
        }
    }
}
void remplirTableau(int taille, int tailleBase, char* a, unsigned int* nb) {
    unsigned long int nombre = 0;
    int indicePuissance = 0;
    int indice = 0;
    int caseRempli = 0;
    for (int i = 0; i < tailleBase; i++) {
        nombre = 0;
        for (; indice < taille; indice++) {       
            nombre = 0;
            for (int y = indicePuissance; y <= indice; y++) {
                nombre += ((int)a[taille-y-1] - 48) * pow(10, y - indicePuissance);
            }
            if (nombre >= pow(2, 32) - 1) {
                indicePuissance = indice;
                break;
            }
            nb[caseRempli] = nombre;
        }
        caseRempli++;
    }
}
void dynamicChar(char*& nombre){
    nombre = (char*)malloc(1);
    int tmp;
    int i = 0;
    // Read characters until found an EOF or newline character. */
    while((tmp = getchar()) != '\n' && tmp != EOF)
    {
        nombre[i++] = tmp;
        nombre = (char*)realloc(nombre, i+1); // Add space for another character to be read.
    }
    nombre[i] = '\0';  // Null terminate the string
}
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
        s.size = b.size + 1;
    }
    else {
        s.size = a.size + 1;
    }
    s.p = new unsigned int[s.size]();

    unsigned int c = 0;
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

    delete[] a.p;
    delete[] b.p;
    delete[] s.p;
    delete[] nombre1;
    delete[] nombre2;
    return 0;
}



