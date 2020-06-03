#include <iostream>
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
		nombre = (char*)realloc(nombre, i + 1); // Allocation d'un espace m�moire supll�mentaire pour le caract�re � venir
	}
	nombre[i] = '\0';  // On ajoute le caract�re de fin de cha�ne
}
*/

lentier repartitionTab(char* a, int tailleBase) {
	lentier s;
	int taille = getNumbersChar(a);

	s.size = tailleBase;
	s.p = new unsigned int[tailleBase]();

	for (int i = 0; i < tailleBase; i++) {
		for (int y = i * 9; y < taille && y < (i + 1) * 9; y++) {
			s.p[i] += (int)(a[taille - y - 1] - 48) * pow(10, y - i * 9);
		}
	}
	return s;
}

char estSuperieur(lentier a, lentier b) //Renvoie 1 si a > b, 0 si a=b, -1 sinon
{
	if (a.size > b.size) {
		return 1;
	}
	else if (b.size < a.size) {
		return -1;
	}
	else {
		for (int i = 0; i < a.size; i++) {
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
	//Cr�ation du lentier s
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
	lentier r;

	q.size = a.size - b.size;
	q.p = new unsigned int[q.size]();
	r.size = b.size - 1;

	//0
	lentier nul;
	nul.size = 1;
	nul.p = new unsigned int[nul.size];
	nul.p[0] = 0;


	if (a.size < b.size) {
		//impossible
		cout << "a est inf�rieur � b" << endl;
	}
	else {

		lentier base1;
		lentier base2;
		base2.size = a.size - b.size + 1;
		base2.p = new unsigned int[base2.size];

		base1.size = 2;
		base1.p = new unsigned int[base1.size];
		base1.p[1] = 1;
		base1.p[0] = 0;

		base2.p[1] = 1;
		base2.p[0] = 0;

		for (unsigned int i = 1; i < a.size - b.size; i++) {

			base2 = multiplication(base2, base1);
		}

		base2 = multiplication(base2, b);

		while (estSuperieur(a, base2) >= 0) {

			q.p[a.size - b.size]++;
			a = soustraction(a, base2);
		}


		for (unsigned int i = a.size - 1; i <= b.size; i++) {

			if (a.p[i] == b.p[b.size - 1]) {
				q.p[i - b.size] = 0xFFFFFFFF;
			}
			else {
				q.p[i - b.size] = ((a.p[i] << 32) + a.p[i - 1]) / b.p[b.size - 1];
			}

			lentier temp1;
			lentier temp2;
			temp1.size = 3;
			temp2.size = 3;

			temp1.p = new unsigned int[temp1.size];
			temp2.p = new unsigned int[temp2.size];

			temp1.p[2] = (q.p[i - b.size] * b.p[b.size - 1]) >> 32;
			temp1.p[1] = (((unsigned long long)q.p[i - b.size] * b.p[b.size - 1]) & 0xFFFFFFFF + ((unsigned long long)
				q.p[i - b.size] * b.p[b.size - 2])) >> 32;
			temp1.p[0] = (q.p[i - b.size] * b.p[b.size - 2]) & 0xFFFFFFFF;
			temp2.p[2] = a.p[i];
			temp2.p[1] = a.p[i - 1];

			while (estSuperieur(temp1, temp2) >= 0)
			{
				q.p[i - b.size]--;

			}

			//c)

			temp1.p[2] = 0;
			temp1.p[1] = 0;
			temp1.p[0] = q.p[i - b.size];

			base2.p[1] = 1;
			base2.p[0] = 0;
			for (unsigned int k = 1; k < i - b.size; k++) {

				base2 = multiplication(base2, base1);
			}


			temp2 = multiplication(b, base2);
			a = soustraction(a, multiplication(temp1, temp2));

			//d)

			if (estSuperieur(a, nul) == 1) {
				a = addition(a, base2);
				q.p[i - b.size]--;
			}

		}
		r = addition(a, nul); //pour faire r=a;
		return r;
	}

}