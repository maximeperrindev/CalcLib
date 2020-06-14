#include <iostream>
#include <math.h>

using namespace std;

#include"fonctions.h"

int getNumbersChar(char* a) {
	return strlen(a);
}

lentier dec2lentier(char* a) {
	lentier s, base10, giga, x, y; //Variables utilisées

	int taille = getNumbersChar(a); //On récupère la taille de la chaîne passée en paramètre

	//Création du lentier pour le nombre en base 10
	base10.size = floor(getNumbersChar(a)/9)+1;
	base10.p = new unsigned int[base10.size]();

	//Création du lentier 10^9 pour changer de base
	giga.size = 1;
	giga.p = new unsigned int[giga.size]();
	giga.p[0] = powl(10, 9);

	//Boucle qui transforme notre chaîne de caractère en lentier
	for (int i = 0; i < base10.size; i++) {
		for (int y = i * 9; y < taille && y < (i + 1) * 9; y++) {
			base10.p[i] += (int)(a[taille - y - 1] - 48) * powl(10, y - i * 9);
		}
	}
	

	//Création de la variable x qui a comme première valeur la case de poids faible de base10
	x.size = 1;
	x.p = new unsigned int[x.size]();
	x.p[0] = base10.p[base10.size - 1];

	y.size = 1;

	y.p = new unsigned int[x.size]();

	//Schéma de Horner
	for (int i = base10.size - 1; i > 0; i--) {
		
		y.p[0] = base10.p[i - 1];

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
		for (int i = a.size - 1; i >= 0; i--) {
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
		s.size = a.size + 1;
		tailleMax = b.size;
	}
	else {
		s.size = b.size + 1;
		tailleMax = a.size;
	}
	s.p = new unsigned int[s.size]();

	for (int i = 0; i < tailleMax; i++) {
		temp = (unsigned long long)a.p[i] + b.p[i] + c;
		c = temp >> 32;
		s.p[i] = temp & 0xFFFFFFFF;
	}
	if (a.size > b.size) {
		for (int i = b.size; i < a.size; i++) {
			temp = (unsigned long long)a.p[i] + c;
			c = temp >> 32;
			s.p[i] = temp & 0xFFFFFFFF;
		}
	}
	else if (b.size > a.size) {
		for (int i = a.size; i < b.size; i++) {
			temp = (unsigned long long)b.p[i] + c;
			c = temp >> 32;
			s.p[i] = temp & 0xFFFFFFFF;
		}
	}
	s.p[s.size - 1] = c;
	lAdjust(s);
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
	lAdjust(s);
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
	lAdjust(s);
	return s;
}

res_div div_eucl(lentier adiv, lentier bdiv) {

	lentier a, b, btemp;
	lentier q;
	lentier ctemp;
	res_div res;

	lentier Atemp;

	unsigned long long lambda = 0;

	a = estEgal(adiv);
	b = estEgal(bdiv);
	lAdjust(a);
	lAdjust(b);

	while (b.p[b.size - 1] < 2147483648) {	
		lambda++;
		btemp = mult_lentier_entier(b, 2);
		delete[] b.p;
		b = estEgal(btemp);
		delete[] btemp.p;
	}
	if (lambda > 0) {
		Atemp = mult_lentier_entier(a, pow(2, lambda));
		delete[] a.p;
		a = estEgal(Atemp);
		delete[] Atemp.p;
	}

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
		if ((long long int)(a.size) - b.size + 1 > 0) {

			exp = a.size - b.size;

			multi = decalage('1', exp, b); //Br^n-t;		

		}
		else {
			break;
		}

	}

	atemp = estEgal(a);//permet de retourner a si on rentre pas dans le for suivant
	lAdjust(atemp);
	lAdjust(a);
	//ça marche jusque là
	if (a.size >= 1) {

		for (unsigned int i = a.size - 1; i >= b.size; i--) {
			//a

			if (a.p[i] == b.p[b.size - 1]) {
				q.p[i - b.size] = 4294967295;
			}
			else {

				q.p[i - b.size] = (a.p[i] * pow(2, 32) + a.p[i - 1]) / b.p[b.size - 1];
			}

			//b

			/*while ((unsigned long long)(q.p[i - b.size] * b.p[b.size - 1] > a.p[i] * pow(2, 32)) || (
				(unsigned long long)(q.p[i - b.size] * b.p[b.size - 1] == a.p[i] * pow(2, 32)) &&
				(unsigned long long)(q.p[i - b.size] * b.p[b.size - 2] > (a.p[i - 1] * pow(2, 32) + a.p[i - 2])))) {
				q.p[i - b.size]--;
			}*/

			lentier x, bis, qbis, abis;

			bis.size = 2;
			bis.p = new unsigned int[bis.size];
			bis.p[1] = b.p[b.size - 1];
			bis.p[0] = b.p[b.size - 2];
			qbis.size = 1;
			qbis.p = new unsigned int[qbis.size];
			qbis.p[0] = q.p[i - b.size];

			x = mult_classique(qbis, bis);

			abis.size = 3;
			abis.p = new unsigned int[abis.size];
			abis.p[2] = a.p[i];
			abis.p[1] = a.p[i - 1];
			abis.p[0] = a.p[i - 2];

			while (cmp_lentier(x, abis) == 1) {
				q.p[i - b.size]--;

				qbis.p[0] = q.p[i - b.size];
				delete[]x.p;

				x = mult_classique(qbis, bis);
			}

			delete[]x.p;
			delete[]abis.p;
			delete[]qbis.p;
			delete[]bis.p;
			//c


			ctemp.size = i - b.size + 1;

			exp = i - b.size;

			ctemp.p = new unsigned int[ctemp.size];
			lentier q2;
			q2.size = 1;
			q2.p = new unsigned int[q.size];
			q2.p[0] = q.p[i - b.size];
			ctemp = decalage('1', exp, q2); //Qi-t*r^i-t

			multi = mult_classique(ctemp, b);
			lAdjust(multi);

			delete[]ctemp.p;//CEST TOUT BON

			if (cmp_lentier(atemp, multi) >= 0) {

				Atemp = sub_lentier(atemp, multi);

			}
			else {

				lentier z;
				z.size = 1;
				z.p = new unsigned int[z.size];

				z = add_entier_entier(q.p[i - b.size], 1);


				ctemp = decalage('1', exp, b); //Br^i-t
				delete[]multi.p;
				multi = mult_classique(z, ctemp);
				Atemp = add_lentier(atemp, multi);
				q.p[i - b.size]--;

				delete[] ctemp.p;

			}

			delete[] multi.p;
			delete[] atemp.p;

			atemp = estEgal(Atemp);
			lAdjust(atemp);
			delete[] Atemp.p;
			/////////////////////////////////////////////////////////////////////// pas sur
			if (cmp_lentier(atemp,b)<0) {
				break;
			}
		}
	}
	else {
		atemp.size = 1;
		atemp.p = new unsigned int[1];
		atemp.p[0] = 0;
	}
	if (lambda > 0) {
		lentier l;
		res_div res_temp;
		l.p = new unsigned int[1];
		l.size = 1;
		l.p[0] = pow(2,lambda);
		res_temp = div_eucl_1case(atemp, l);
		res.r = estEgal(res_temp.q);
		delete[] res_temp.q.p;
		delete[] res_temp.r.p;
	}
	else {
		res.r = estEgal(atemp);
	}
	res.q = estEgal(q);
	delete[] q.p;
	delete[] atemp.p;
	return res;
}

void lAdjust(lentier& a) {
	unsigned int i = a.size - 1;
	while (a.p[i] == 0) {
		i--;
	}
	a.size = i + 1;
}

char** parser(char* chaine) {
	int taille = strlen(chaine);
	char** chaineSep = new char* [6]();
	int arret = 0;
	int separation = 0;
	int boucle = 1;
	int caseRempli = 0;
	while (boucle == 1) {
		for (int i = arret; i <= taille + 1; i++) {
			if (chaine[i] < 48 || chaine[i] > 57) {
				chaineSep[caseRempli] = new char[i - arret + 1]();
				for (int y = arret; y < i; y++) {
					chaineSep[caseRempli][y - arret] = chaine[y];
				}
				chaineSep[caseRempli][i - arret] = '\0';
				if (chaine[i] != '\0') {
					chaineSep[caseRempli + 1] = new char[2]();
					chaineSep[caseRempli + 1][0] = (char)(chaine[i]);
					chaineSep[caseRempli + 1][1] = '\0';
					caseRempli += 2;
					arret = i + 1;
				}
				else {
					boucle = 0;
					break;
				}
				break;
			}
		}
	}
	chaineSep[caseRempli + 1] = new char[1]();
	return chaineSep;
}

//multiplication modulaire
lentier mul_mod(lentier a, lentier b, lentier n) {
	lentier t;
	res_div res;
	t = mult_classique(a, b);
	res = div_eucl(t, n);
	delete[] t.p;
	return res.r;
}
lentier exp_mod(lentier a, lentier b, lentier n) {
	lentier p;
	lentier e;
	p = estEgal(a);
	unsigned long long nbBit;
	nbBit = (32 * (n.size - 1) + log2(n.p[n.size - 1]) / log2(2));
	for (int i = nbBit; i >= 0; i--) {
		p = mul_mod(p, p, n);
		if (dec2bin(n.p[i / 32], i % 32) == 1) {
			p = mul_mod(p, a, n);
		}
	}
	return p;
}

bool dec2bin(unsigned int a, int decalage) {
	bool binaire;
	a = a >> decalage;
	binaire = a & 0b1;
	return binaire;


}

void Affiche_lentier(lentier a) {
	for (unsigned int i = a.size; i > 0; i--) {
		cout << a.p[i - 1] << "  ";
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

			res.p[k + decal - 1] = a.p[k - 1];

		}

	}
	else if (sens == '2') {
		res.size = a.size - decal;
		res.p = new unsigned int[res.size]();
		for (unsigned int k = 0; k < res.size; k++) {

			res.p[k] = a.p[k + decal];

		}
	}
	lAdjust(res);
	return res;
}

lentier estEgal(lentier a) {
	lentier res;

	res.size = a.size;
	res.p = new unsigned int[res.size];

	for (unsigned int i = 0; i < a.size; i++) {
		res.p[i] = a.p[i];
	}

	return res;

}
lentier add_lentier_entier(lentier l, unsigned int a) {
	bool c = 0;
	unsigned long long temp = 0;
	int tailleMax = 0;
	//Création du lentier s
	lentier s;
	s.size = l.size + 1;
	s.p = new unsigned int[s.size]();

	temp = (unsigned long long)l.p[0] + a;
	c = temp >> 32;
	s.p[0] = temp & 0xFFFFFFFF;
	
	for (int i = 1; i < l.size; i++) {
		temp = (unsigned long long)l.p[i] + c;
		c = temp >> 32;
		s.p[i] = temp & 0xFFFFFFFF;
	}
	s.p[s.size - 1] = c;
	lAdjust(s);
	return s;
}

lentier add_entier_entier(unsigned int a, unsigned int b) {

	lentier res, abis;
	res.size = 2;
	res.p = new unsigned int[res.size]();
	res.p[0] = a + b;

	if ((unsigned long long)a + b > 4294967295) {
		res.p[1] = 1;
	}

	lAdjust(res);
	return res;

}

res_div div_eucl_1case(lentier adiv, lentier bdiv) {
	lentier a, b, temp, multi, decale;
	a = estEgal(adiv);
	b = estEgal(bdiv);
	res_div res;
	res.q.size = a.size - b.size + 1;
	res.q.p = new unsigned int[res.q.size]();
	res.r.size = b.size;
	res.r.p = new unsigned int[res.r.size]();

	while (a.size > 1) {

		if (a.p[a.size - 1] >= b.p[0]) {

			res.q.p[a.size - b.size] = a.p[a.size - 1] / b.p[0];
			temp = estEgal(a);
			delete[]a.p;
			multi = mult_lentier_entier(b, res.q.p[a.size - b.size]);
			
			decale = decalage('1', a.size - 1, multi);
			
			a = sub_lentier(temp, decale);
			delete[]multi.p;
			delete[]temp.p;
			delete[]decale.p;
			
		}
		else {
			
			res.q.p[a.size - 1 - b.size] = ((unsigned long long)(a.p[a.size - 1]) * pow(2, 32) + a.p[a.size - 2]) / b.p[b.size - 1];

			temp = estEgal(a);
			delete[]a.p;
			multi = mult_lentier_entier(b, res.q.p[a.size - 1 - b.size]);
			
			decale = decalage('1', a.size - 2, multi);
			
			a = sub_lentier(temp, decale);
			delete[]multi.p;
			delete[]temp.p;
			delete[]decale.p;
		
		}

	}
	if (a.p[0] >= b.p[0]) {
		res.q.p[0] = a.p[a.size - 1] / b.p[0];
		temp = estEgal(a);
		delete[]a.p;
		multi = mult_lentier_entier(b, res.q.p[0]);
		
		a = sub_lentier(temp, multi);
		delete[]multi.p;
		delete[]temp.p;
		
	}
	res.r = estEgal(a);
	delete[]a.p;
	delete[]b.p;
	return res;
}

lentier mult_lentier_entier(lentier a, unsigned int b) {
	lentier s;
	long long temp = 0;
	int c = 0;
	s.size = a.size + 1;
	s.p = new unsigned int[s.size]();
	for (int i = 0; i < a.size; i++) {
		c = 0;
		for (int j = 0; j < 1; j++) {
			temp = s.p[i + j] + (unsigned long long)a.p[i] * b + c;
			s.p[i + j] = temp & 0xFFFFFFFF;
			c = temp >> 32;
		}
		s.p[i + 1] = c;
	}
	lAdjust(s);
	return s;
}
