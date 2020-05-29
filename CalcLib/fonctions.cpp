#include <iostream>
#include <math.h>

using namespace std;

#include"fonctions.h"

int getNumbersChar(char* a) {
	return strlen(a);
}

int tailleBase(int taille, char *a) {
	unsigned long int nombre = 0;
	int indice = 0;
	int nombreCase = 0;
	int indicePuissance = 0;
	while (indice < taille) {
		nombre = 0;
		for (; indice < taille; indice++) {
			nombre = 0;
			for (int y = indicePuissance; y <= indice; y++) {
				nombre += ((int)a[taille - y - 1] - 48) * pow(10, y - indicePuissance);
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

void checkCharLength(char* nombre1, char* nombre2) {
	int nb1 = getNumbersChar(nombre1);
	int nb2 = getNumbersChar(nombre2);
	if (nb1 > nb2) {
		nombre2 = (char*)realloc(nombre2, nb1 + 1); // Add space for another character to be read.
		int diff = nb1 - nb2;
		for (int i = 0; i <= nb1; i++) {
			nombre2[nb1 - i] = nombre2[nb2 - i];
		}
		for (int i = 0; i < diff; i++) {
			nombre2[i] = '0';
		}
	}
	else if (nb2 > nb1) {
		nombre1 = (char*)realloc(nombre1, nb2 + 1); // Add space for another character to be read.
		int diff = nb2 - nb1;
		for (int i = 0; i <= nb2; i++) {
			nombre1[nb2 - i] = nombre1[nb1 - i];
		}
		for (int i = 0; i < diff; i++) {
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
				nombre += ((int)a[taille - y - 1] - 48) * pow(10, y - indicePuissance);
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

void dynamicChar(char*& nombre) {
	nombre = (char*)malloc(1);
	int tmp;
	int i = 0;
	// Read characters until found an EOF or newline character. */
	while ((tmp = getchar()) != '\n' && tmp != EOF)
	{
		nombre[i++] = tmp;
		nombre = (char*)realloc(nombre, i + 1); // Add space for another character to be read.
	}
	nombre[i] = '\0';  // Null terminate the string
}

lentier addition(lentier a, lentier b) {
	unsigned int c = 0;
	unsigned long long temp = 0;
	//Cr�ation du lentier s
	lentier s;
	if (a.size >= b.size) {
		s.size = a.size+1;
	}
	else {
		s.size = b.size + 1;
	}
	s.p = new unsigned int[s.size]();

	//Addition
	for (int i = 0; i < s.size-1; i++) {
		temp = 0;
		if (a.size > b.size && i >= b.size) {
			s.p[i] = a.p[i] + c;
			temp = a.p[i];
			temp += c;
		}
		else if (b.size > a.size && i >= a.size) {
			s.p[i] = b.p[i] + c;
			temp += b.p[i];
			temp += c;
		}
		else {
			s.p[i] = a.p[i] + b.p[i] + c;
			temp = a.p[i];
			temp += b.p[i];
			temp += c;
		}
		if (temp < 4294967296) {

			c = 0;
		}
		else
		{
			c = 1;
		}
	}
	s.p[s.size-1] = c;
	
	return s;
}

lentier soustraction(lentier a, lentier b) {
	int c = 0;
	long long temp = 0;
	//Cr�ation du lentier s
	lentier s;
	if (a.size >= b.size) {
		s.size = a.size;
	}
	else {
		s.size = b.size;
	}
	s.p = new unsigned int[s.size]();
	for (int i = 0; i < s.size; i++) {
		temp = 0;
		if (a.size > b.size&& i >= b.size) {
			s.p[i] = a.p[i] + c;
			temp = a.p[i];
			temp += c;
		}
		else {
			s.p[i] = a.p[i] - b.p[i] + c;
			temp = a.p[i];
			temp -= b.p[i];
			temp += c;
		}

		if (temp >= 0) {

			c = 0;
		}
		else
		{
			c = -1;
		}
	}
	return s;
}