﻿#include <iostream>
#include <math.h>

using namespace std;

#include"fonctions.h"

int getNumbersChar(char* a) {
	return strlen(a);
}
/*
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
	while ((tmp = getchar()) != '\n' && tmp != EOF)
	{
		nombre[i++] = tmp;
		nombre = (char*)realloc(nombre, i + 1); // Allocation d'un espace mŽmoire supllŽmentaire pour le caractre ˆ venir
	}
	nombre[i] = '\0';  // On ajoute le caractre de fin de cha”ne
}
*/

lentier repartitionTab(char* a, int tailleBase) {
	lentier s;
	lentier temp;
	lentier temp2;
	lentier base10;
	float multi = 0;
	unsigned long long retenue = 0;
	int taille = getNumbersChar(a);

	s.size = tailleBase;
	temp.size = s.size;
	base10.size = s.size;
	temp.p = new unsigned int[tailleBase]();
	base10.p = new unsigned int[tailleBase]();
	s.p = new unsigned int[tailleBase]();

	for (int i = 0; i < tailleBase; i++) {
		for (int y = i * 9; y < taille && y < (i + 1) * 9; y++) {
			base10.p[i] += (int)(a[taille - y - 1] - 48) * pow(10, y - i * 9);
		}
		
	}
	for (int i = tailleBase - 1; i > 0; i--) {
		s.p[i] += (base10.p[base10.size-1] * pow(10, 9 * i)) / pow(2, 32 * i);
		base10.p[base10.size-1] += fmod(fmod(base10.p[base10.size - 1] * pow(10, 9 * i), pow(2, 32 * i)), pow(10,9*(i-1)));
		cout << "retenue" << retenue << endl;
		base10.p[base10.size-1] = fmod(base10.p[base10.size - 1] * pow(10, 9 * i), pow(2, 32 * i)) / pow(10, 9 * (i - 1));
		cout << s.p[0] << " = s" << endl;
		cout << "base10" << base10.p[base10.size-1] << endl;
	}
	retenue = fmod(s.p[2] * pow(2, 64) + s.p[1] * pow(2, 32), 1000000000);
	
	cout << "retenue" << retenue << endl;
	s.p[0] = base10.p[base10.size - 1] + retenue;
	/*s.p[i] = round(temp.p[i] * pow(10, 9 * i) / pow(2, 32 * i)) + retenue;
	retenue = 0;
	for (int y = tailleBase - 1; y >= i; y--) {
		retenue += ceil((temp.p[y] * pow(10, 9 * y) - s.p[y] * pow(2, 32 * y)) / pow(2, 32 * (i - 1)));
	}
	cout << "retenue = " << retenue << endl;
	s.p[0] = retenue + temp.p[0];*/
	return s;
}

char estSuperieur(lentier a, lentier b) //Renvoie 1 si a > b, 0 si a=b, -1 sinon
{
	if (a.size > b.size) {
		return 1;
	}
	else if (b.size > a.size) {
		return -1;
	}
	else {
		for (int i = a.size-1; i >=0; i--) {
			if (a.p[i] > b.p[i]) {
				return 1;
			}
			else if (b.p[i] > a.p[i]) {
				return -1;
			}
		}
		return 0;
	}
}

lentier addition(lentier a, lentier b) {
	bool c = 0;
	unsigned long long temp = 0;
	int tailleMax = 0;
	//Création du lentier s
	lentier s;
	if (a.size >= b.size) {
		s.size = a.size+1;
		tailleMax = b.size;
	}
	else {
		s.size = b.size + 1;
		tailleMax = a.size;
	}
	s.p = new unsigned int[s.size]();
    
    for(int i = 0; i < tailleMax; i++){
        temp = (unsigned long long)a.p[i] + b.p[i] + c;
        c = temp >> 32;
        s.p[i] = temp & 0xFFFFFFFF;
    }
    if(a.size > b.size){
        for(int i = b.size; i < a.size; i++){
            temp = (unsigned long long)a.p[i] + c;
            c = temp >> 32;
            s.p[i] = temp & 0xFFFFFFFF;
        }
    }
    else if(b.size > a.size){
        for(int i = a.size; i < b.size; i++){
            temp = (unsigned long long)b.p[i] + c;
            c = temp >> 32;
            s.p[i] = temp & 0xFFFFFFFF;
        }
    }
    s.p[s.size-1] = c;
	return s;
}

lentier soustraction(lentier a, lentier b) {
    int c = 0;
    long long temp = 0;
	int tailleMax = 0;
	lentier s;	

	if (estSuperieur(a, b) >= 0) {
		s.size = a.size;
		tailleMax = b.size;
		s.p = new unsigned int[s.size]();

		for (int i = 0; i < a.size && i < b.size; i++) {
			temp = a.p[i] - (unsigned long long)b.p[i] + c;
			c = temp >> 63;
			s.p[i] = temp & 0xFFFFFFFF;
		}
		if (a.size > b.size) {
			for (int i = b.size; i < a.size; i++)
			{
				temp = (unsigned long long)a.p[i] + c;
				c = temp >> 63;
				s.p[i] = temp & 0xFFFFFFFF;
			}
		}
	}
	else {
		s.size = b.size;
		tailleMax = a.size;
		s.p = new unsigned int[s.size]();
		for (int i = 0; i < tailleMax; i++) {
			temp = b.p[i] - (unsigned long long)a.p[i] + c;
			c = temp >> 63;
			s.p[i] = temp & 0xFFFFFFFF;
		}
		if (b.size > a.size) {
			for (int i = a.size; i < b.size; i++)
			{
				temp = (unsigned long long)b.p[i] + c;
				c = temp >> 63;
				s.p[i] = temp & 0xFFFFFFFF;
			}
		}
	}
   
    return s;
}

lentier multiplication(lentier a, lentier b) {
	lentier s;
	long long temp = 0;
	int c = 0;
	s.size = a.size + b.size;
	s.p = new unsigned int[s.size]();
	for (int i = 0; i < a.size; i++) {
		c = 0;
		for (int j = 0; j < b.size; j++) {
			temp = s.p[i + j] + (unsigned long long)a.p[i] * b.p[j] + c;
			s.p[i + j] = temp & 0xFFFFFFFF;
			c = temp >> 32;
		}
		s.p[i + b.size] = c;
	}

	return s;
}

lentier division(lentier a, lentier b) {

	lentier q;
	lentier h; //help
	lentier nul;
	lentier Atemp;//Ce sera le reste

	nul.size = 1;
	nul.p = new unsigned int[nul.size]();

	unsigned int exp = 0; //exposant

	q.size = a.size - b.size + 1;
	q.p = new unsigned int[q.size]();


	exp = a.size - b.size;

	h.size = exp + 1;
	h.p = new unsigned int[h.size]();


	h.p[exp] = 1; //h=r^n-t

	lentier multi;
	multi = multiplication(b, h); //Br^n-t;
	lAdjust(multi);
	for (unsigned int k = multi.size; k > 0; k--) {
		cout << multi.p[k - 1] << " ";
	} cout << endl;
	lentier atemp;

	while (estSuperieur(a, multi) >= 0) {
		cout << "a: ";
		for (unsigned int k = a.size; k >0; k--) {
			cout << a.p[k-1] ;
		} cout << endl;
		cout << "b: ";
		for (unsigned int k = b.size; k > 0; k--) {
			cout << b.p[k-1];
		} cout << endl;
		
		q.p[a.size - b.size]++;

		atemp = soustraction(a, multi);
		for (unsigned int k = atemp.size; k > 0; k--) {
			cout << atemp.p[k - 1] << " ";
		} cout << endl;

		delete[] a.p;

		a = addition(atemp, nul);

		lAdjust(a);
		for (unsigned int k = a.size; k > 0; k--) {
			cout << a.p[k - 1] << " ";
		} cout << endl;
		delete[]atemp.p;
	}
	atemp = addition(a, nul);//permet de retourner a si on rentre pas dans le for suivant
	lAdjust(atemp);
//ça marche jusque là

	for (unsigned int i = a.size - 1; i >= b.size; i--) {
		//a
		if (a.p[i] == b.p[b.size - 1]) {
			q.p[i - b.size] = 4294967295;
		}
		else {

			q.p[i - b.size] = (a.p[i] * pow(2, 32) + a.p[i - 1]) / b.p[b.size - 1];
		}

		delete[] h.p;
		//b

		while ((unsigned long long)(q.p[i - b.size] * b.p[b.size - 1] > a.p[i] * pow(2, 32)) || (
			(unsigned long long)(q.p[i - b.size] * b.p[b.size - 1] == a.p[i] * pow(2, 32)) &&
			(unsigned long long)(q.p[i - b.size] * b.p[b.size - 2] > (a.p[i - 1] * pow(2, 32) + a.p[i - 2])))) {

			q.p[i - b.size]--;
		}

		//c

		lentier ctemp;
		ctemp.size = i - b.size + 1;

		exp = i - b.size;

		ctemp.p = new unsigned int[ctemp.size];

		ctemp.p[exp] = q.p[i - b.size]; //Qi-t*r^i-t
		delete[] multi.p;
		multi = multiplication(ctemp, b);
		delete[]ctemp.p;

		if (estSuperieur(a, multi) >= 0) {

			Atemp = soustraction(atemp, multi);

		}
		else {
			ctemp.p = new unsigned int[ctemp.size];
			ctemp.p[exp] = 1; //r^i-t
			h = multiplication(b, ctemp); //Br^i-t

			Atemp = addition(atemp, h);
			q.p[i - b.size]--;

		}

		

		delete[] atemp.p;
		delete[] ctemp.p;
		delete[] h.p;
		atemp = addition(Atemp, nul);
		lAdjust(atemp);
		delete[] Atemp.p;
	}
	
	return atemp;
}

void lAdjust(lentier& a) {
	unsigned int i = a.size-1;
	while (a.p[i] == 0) {
		i--;
	}
	
	/*for (int y = a.size - 1; y > i; y--) {
		free(&a.p[y]);
	}*/
	a.size = i+1;
}