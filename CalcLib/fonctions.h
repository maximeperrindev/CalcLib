

typedef struct {
	unsigned int* p;
	unsigned int size;
}
lentier;

typedef struct {
	lentier q;
	lentier r;
}
res_div;

/*Role : Renvoie le nombre de caractère d'une chaine
Entrée : Un pointeur vers une chaîne de caractère
Sortie : Un entier positif*/

unsigned int getNumbersChar(char* ); 
/*Role : Renvoie une chaine de caractère correspondant à un int
Entrée : Un entier positif
Sortie : Un pointeur vers une chaine de caractère*/
char *int2char(unsigned int nbr); 

/*Role : Renvoie le resultat de l'addition de deux lentiers
Entrée : Deux lentiers
Sortie : Un lentier*/
lentier add_lentier(lentier, lentier);

/*Role : Renvoie le resultat de la soustraction de deux lentiers
Entrée : Deux lentiers
Sortie : Un lentier*/
lentier sub_lentier(lentier, lentier);

/*Role : Renvoie le resultat de la soustraction de deux lentiers
Entrée : Deux lentiers
Sortie : Un lentier*/
lentier mult_classique(lentier, lentier);

/*Role : Compare deux lentiers
Entrée : Deux lentiers
Sortie : Un char (compris entre -1 et 1)*/
char cmp_lentier(lentier, lentier);

/*Role : Renvoie le résultat de la division de deux lentiers (quotient et reste)
Entrée : Deux lentiers
Sortie : Un res_div */
res_div div_eucl(lentier, lentier);

/*Role : Renvoie un lentier(base 2^32) correspondant à un nombre dans une chaines de caractères (base 10)
Entrée : Un pointeur vers une chaîne de caractère
Sortie : Un lentier */
lentier dec2lentier(char*);

/*Role : Modifier la taille d'un lentier si ses cases de poids forts sont égales à 0
Entrée : Une référence vers un lentier
Sortie : vide*/
void lAdjust(lentier&);

/*Role : Formate la chaine de caractère du calcul rentré par l'utilisateur pour qu'elle soit dans le bon format
Entrée : Un pointeur vers une chaîne de caractère
Sortie : une pointeur vers un tableau de chaine de caractère */
char** parser(char*);

/*Role : Renvoie le resultat d'une multiplication modulaire
Entrée : 3 lentiers
Sortie : 1 lentier */
lentier mul_mod(lentier, lentier, lentier);

/*Role : Renvoie le résultat d'une exponentiation modulaire
Entrée : 3 lentiers
Sortie : 1 lentier */
lentier exp_mod(lentier, lentier, lentier);

/*Role : Renvoie la valeur d'un bit 
Entrée : Un entier positif et l'indice du bit que l'on souhaite récupérer
Sortie :  Un booléen*/
bool dec2bin(unsigned int,int);

/*Role : Afficher un lentier
Entrée : Un lentier
Sortie : vide */
void Affiche_lentier(lentier);

/*Role : Multiplie un lentier par 2^32 en faisant un décalage 
Entrée : Un char pour indiquer le sens (multplication ou division), un entier positif (le nombre de cases à décaler), un lentier
Sortie : Un lentier */
lentier decalage(char, unsigned int, lentier);

/*Role : Copier un lentier valeur par valeur dans un autre
Entrée : Un lentier
Sortie : Un lentier */
lentier estEgal(lentier);

/*Role : Ajouter un lentier avec un entier (gestion des dépassements)
Entrée : Un lentier et un entier positif
Sortie : Un lentier */
lentier add_lentier_entier(lentier, unsigned int);

/*Role : Ajoute deux entiers et le stock dans un lentier (gestion des dépassements)
Entrée : Deux entiers positifs
Sortie : Un lentier*/
lentier add_entier_entier(unsigned int, unsigned int);

/*Role : Renvoie le résultat d'une division euclidienne entre un lentier et un lentier de taille 1
Entrée : Deux lentiers
Sortie : Un res_div */
res_div div_eucl_1case(lentier adiv, lentier bdiv);

/*Role : Renvoie le résultat d'une multiplication entre un lentier et un entier positif
Entrée : Un lentier et un entier positif
Sortie : Un lentier */
lentier mult_lentier_entier(lentier, unsigned int);

/*Role : Renvoie une chaîne de caractère correspondant au nombre en base 10 égal au lentier en base 2^32
Entrée : Un lentier
Sortie : Un pointeur vers une chaîne de caractère */
char* lentier2dec(lentier);
