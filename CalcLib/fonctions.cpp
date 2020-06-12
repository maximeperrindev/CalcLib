#include <iostream>
#include <math.h>

using namespace std;

#include"fonctions.h"

int getNumbersChar(char* a) {
	return strlen(a);
}

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
	lentier h; //help
	lentier nul;
	lentier Atemp;//Ce sera le reste

	nul.size = 1;
	nul.p = new unsigned int[nul.size]();

	a = add_lentier(adiv, nul);
	b = add_lentier(bdiv, nul);
	lAdjust(a);
	lAdjust(b);

	unsigned int exp = 0; //exposant

	q.size = a.size - b.size + 1;
	q.p = new unsigned int[q.size]();


	exp = a.size - b.size;

	h.size = exp + 1;
	h.p = new unsigned int[h.size]();


	h.p[exp] = 1; //h=r^n-t

	lentier multi;
	multi = mult_classique(b, h); //Br^n-t;
	
	/*multi.p = new unsigned int[b.size + h.size];
	for (unsigned int k = b.size - 1; k >= 0; k--) {
		multi.p[k + exp] = multi.p[k];
		
	}*/
	lAdjust(multi);
	lentier atemp;

	while (cmp_lentier(a, multi) >= 0) {

		q.p[a.size - b.size]++;

		atemp = sub_lentier(a, multi);

		delete[] a.p;

		a = add_lentier(atemp, nul);

		lAdjust(a);

		delete[]atemp.p;

		delete[] h.p;

		delete[] multi.p;

		if ((int)a.size - b.size + 1> 0) {
			h.size = a.size - b.size + 1;
			h.p = new unsigned int[h.size]();

			h.p[a.size - b.size] = 1;

			multi = mult_classique(b, h); //Br^n-t;

			lAdjust(multi);
			delete[] h.p;
		}
	}

	atemp = add_lentier(a, nul);//permet de retourner a si on rentre pas dans le for suivant
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

		lentier ctemp;
		ctemp.size = i - b.size + 1;

		exp = i - b.size;

		ctemp.p = new unsigned int[ctemp.size];

		ctemp.p[exp] = q.p[i - b.size]; //Qi-t*r^i-t
		delete[] multi.p;
		multi = mult_classique(ctemp, b);
		delete[]ctemp.p;

		if (cmp_lentier(a, multi) >= 0) {

			Atemp = sub_lentier(atemp, multi);

		}
		else {

			ctemp.p = new unsigned int[ctemp.size];
			ctemp.p[exp] = 1; //r^i-t
			h = mult_classique(b, ctemp); //Br^i-t

			Atemp = add_lentier(atemp, h);
			q.p[i - b.size]--;

			delete[] ctemp.p;
			delete[] h.p;

			delete[] h.p;

		}

	
		delete[] atemp.p;
		

		atemp = add_lentier(Atemp, nul);
		lAdjust(atemp);
		delete[] Atemp.p;
	}

	delete[] nul.p;
	return atemp;
}

void lAdjust(lentier& a) {
	unsigned int i = a.size-1;
	while (a.p[i] == 0) {
		i--;
	}
	a.size = i + 1;
}

void parser(char* chaine) {
	int taille = strlen(chaine);
	char** chaineSep;
	chaineSep = new char*[5];
	int arret = 0;
	int separation = 0;
	int boucle = 1;
	int caseRempli = 0;
	while (boucle == 1) {
		for (int i = arret; i <= taille+1; i++) {
			if (chaine[i] == '\0') {
				separation = i-1;
				boucle = 0;
				break;
			}
			else if (chaine[i] <= 48 || chaine[i] >= 57) {
				separation = i;
				break;
			}		
		}
		chaineSep[caseRempli] = new char[separation-arret+1];
		for (int i = arret; i < separation; i++) {
				chaineSep[caseRempli][i] = chaine[i];
				cout << chaineSep[caseRempli][i];
		}
		
		chaineSep[caseRempli + 1] = new char[1];
		chaineSep[caseRempli + 1][0] = chaine[separation];
		cout << chaineSep[caseRempli + 1][0];
		caseRempli += 2;
		arret = separation + 1;
	}
}

//multiplication modulaire
lentier mul_mod(lentier a, lentier b, lentier n) {
	lentier t;
	lentier res;
	t = mult_classique(a, b);
	res = div_eucl(t, n);
	delete[] t.p;
	return res;
}
lentier exp_mod(lentier a, lentier b, lentier n) {
	lentier p;
	lentier e;
	p = a;
	unsigned long long nbBit;
	nbBit = (32 * (n.size - 1) + log2(n.p[n.size - 1]) / log2(2));
	for (int i =nbBit ; i >=0; i--) {
		p = mul_mod(p, p, n);
		if (dec2bin(n.p[i/32],i%32)== 1) {
			p = mul_mod(p, a, n);
		}
	}
	return p;
}

bool dec2bin(unsigned int a,int decalage) {
	bool binaire;
	a = a >> decalage;
	binaire = a & 0b1;
	return binaire;


}

void Affiche_lentier(lentier a) {
	for (unsigned int i = a.size ; i > 0; i--) {
		cout << a.p[i-1] << "  ";
	}
	cout << endl;
}

