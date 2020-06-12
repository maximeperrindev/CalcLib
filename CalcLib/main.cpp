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

	// char* nombre1 = new char[100];

	/* char* nombre1 = new char[100];
	 char* nombre2 = new char[100]; */

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
	  /*
	  a.size = 6;
	  b.size = 5;

	  a.p = new unsigned int[6]();
	  b.p = new unsigned int[5]();

	  a.p[4] = 1;

	  lAdjust(a);

	  for (int i = 0; i < a.size; i++) {
		  cout << a.p[i] << endl;
	  }

	  s.size = a.size;
	  s = multiplication(a, b);

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
	  */

	  /*cin >> nombre1;
	  parser(nombre1);*/


	  //cout << log2(19) / log2(2);
	unsigned int tab[4] = { 2, 0, 48488, 154518 };
	unsigned int tab2[2] = { 0, 48488 };
	unsigned int tab3[1] = { 2 };
	lentier n;
	a.size = 4;
	b.size = 2;
	
	a.p = tab;
	b.p = tab2;
	
	n = decalage('1', 1, b);
	Affiche_lentier(n);


	/*a.size = 4;
	b.size = 2;
	a.p = new unsigned int[a.size];
	b.p = new unsigned int[b.size];

	a.p[3] = 1;
	a.p[2] = 2;
	a.p[1] = 3;
	a.p[0] = 4;

	b.p[1] = 1;
	b.p[0] = 4;*/

	res_div res;

	//// res = exp_mod(a,b,n);

	res = div_eucl(a, b);
	cout << "q  ";
	Affiche_lentier(res.q); cout << endl;
	cout << "r ";
	Affiche_lentier(res.r);

	delete[]res.q.p;
	delete[]res.r.p;



	/*a.size = 4;
	char * tab = new char[30];
	cin>>tab;
	lentier x = dec2lentier(tab, floor(((getNumbersChar(tab) * log(10))/(32*log(2)))) + 1);
	cout<<"Conversion décimal => lentier: ";
	for (int i = x.size; i >0 ; i--) {
		cout << x.p[i-1] << " ";
	}
	cout << endl;
	a.size = 4;
	b.size = 2;
	a.p = new unsigned int[a.size]();
	b.p = new unsigned int[b.size]();

	a.p[3] = 1;
	a.p[2] = 2;
	a.p[1] = 3;
	a.p[0] = 4;

	b.p[1] = 1;
	b.p[0] = 0;

	Affiche_lentier(a);
	Affiche_lentier(b);

	s = div_eucl(a, b);

	//Résultat opération

	Affiche_lentier(s);

	delete[] s.p;*/


	return 0;
}