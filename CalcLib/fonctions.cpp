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
		nombre = (char*)realloc(nombre, i + 1); // Allocation d'un espace mŽmoire supllŽmentaire pour le caractre ˆ venir
	}
	nombre[i] = '\0';  // On ajoute le caractre de fin de cha”ne
}
*/

lentier dec2lentier(char* a, int tailleBase) {
	lentier s, base10, giga, x,y; //Variables utilisées

	int taille = getNumbersChar(a); //On récupère la taille de la chaîne passée en paramètre

    //Création du lentier pour le nombre en base 10
	base10.size = tailleBase;
	base10.p = new unsigned int[tailleBase]();

    //Création du lentier 10^9 pour changer de base
    giga.size = 1;
    giga.p = new unsigned int[giga.size]();
    giga.p[0] = powl(10,9);

    //Boucle qui transforme notre chaîne de caractère en lentier
	for (int i = 0; i < tailleBase; i++) {
		for (int y = i * 9; y < taille && y < (i + 1) * 9; y++) {
			base10.p[i] += (int)(a[taille - y - 1] - 48) * powl(10, y - i * 9);
		}
	}

    //Création de la variable x qui a comme première valeur la case de poids faible de base10
    x.size = 1;
    x.p = new unsigned int[x.size]();
    x.p[0] = base10.p[tailleBase-1];
    
    //Schéma de Horner
    for(int i = tailleBase - 1; i > 0; i--){
        y.size  = 1;

        y.p = new unsigned int[x.size]();

        y.p[0] = base10.p[i-1];
        
        s = mult_classique(x, giga);
        
        delete[] x.p;
        
        x = add_lentier(s, y);
        delete[] s.p;
    }
    
    //On supprime les 0 inutiles
    lAdjust(x);
    
	return x;
}

char cmp_lentier(lentier a, lentier b) //Renvoie 1 si a > b, 0 si a=b, -1 sinon
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

lentier add_lentier(lentier a, lentier b) {
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

lentier sub_lentier(lentier a, lentier b) {
    int c = 0;
    long long temp = 0;
	int tailleMax = 0;
	lentier s;	

	if (cmp_lentier(a, b) >= 0) {
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

lentier mult_classique(lentier a, lentier b) {
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

lentier div_eucl(lentier adiv, lentier bdiv) {

	lentier a, b;
	
	lentier q;
	lentier ctemp;
	
	lentier Atemp;//Ce sera le reste



	a = estEgal(adiv);
	b = estEgal(bdiv);
	lAdjust(a);
	lAdjust(b);

	unsigned int exp = 0; //exposant

	q.size = a.size - b.size + 1;
	q.p = new unsigned int[q.size]();


	exp = a.size - b.size;

	

	lentier multi;

	
	multi = decalage('1', exp, b);
	
	lentier atemp;

	while (cmp_lentier(a, multi) >= 0) {

		q.p[a.size - b.size]++;

		atemp = sub_lentier(a, multi);

		delete[] a.p;

		a = estEgal(atemp);

		lAdjust(a);

		delete[]atemp.p;

		

		delete[] multi.p;

		if ((int)a.size - b.size + 1> 0) {
			
			exp = a.size - b.size;
			multi = decalage('1', exp, b); //Br^n-t;
		}
	}

	atemp = estEgal(a);//permet de retourner a si on rentre pas dans le for suivant
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

		//b

		while ((unsigned long long)(q.p[i - b.size] * b.p[b.size - 1] > a.p[i] * pow(2, 32)) || (
			(unsigned long long)(q.p[i - b.size] * b.p[b.size - 1] == a.p[i] * pow(2, 32)) &&
			(unsigned long long)(q.p[i - b.size] * b.p[b.size - 2] > (a.p[i - 1] * pow(2, 32) + a.p[i - 2])))) {

			q.p[i - b.size]--;
		}

		//c

		
		ctemp.size = i - b.size + 1;

		exp = i - b.size;

		ctemp.p = new unsigned int[ctemp.size];

		ctemp = decalage('1', exp, q); //Qi-t*r^i-t
		delete[] multi.p;
		multi = mult_classique(ctemp, b);
		delete[]ctemp.p;

		if (cmp_lentier(a, multi) >= 0) {

			Atemp = sub_lentier(atemp, multi);

		}
		else {

		
			ctemp = decalage('1', exp, b); //Br^i-t

			Atemp = add_lentier(atemp, ctemp);
			q.p[i - b.size]--;

			delete[] ctemp.p;

		}

	
		delete[] atemp.p;
		
		atemp = estEgal(Atemp);
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
	a.size = i + 1;
}

void Affiche_lentier(lentier a) {
	for (unsigned int i = a.size ; i > 0; i--) {
		cout << a.p[i-1] << "  ";
	}
	cout << endl;
}

lentier decalage(char sens, unsigned int decal, lentier a) {
	lentier res;
	//1 gauche //2 droite
	if (sens == '1') {
		res.size = a.size + decal;
		res.p = new unsigned int[res.size]();
		for (unsigned int k = a.size; k > 0; k--) {

			res.p[k + decal-1] = a.p[k-1];

		}

	}
	else if (sens == '2') {
		res.size = a.size - decal;
		res.p = new unsigned int[res.size]();
		for (unsigned int k = 0; k < res.size; k++) {

			res.p[k] = a.p[k+decal];

		}
	}
	lAdjust(res);
	return res;
}
	
lentier estEgal(lentier a){
	lentier res;

	res.size = a.size;
	res.p = new unsigned int[res.size];

	for (unsigned int i = 0; i < a.size; i++) {
		res.p[i] = a.p[i];
	}

	return res;

}