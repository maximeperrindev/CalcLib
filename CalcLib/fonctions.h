

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

/*Role : Renvoie le nombre de caract�re d'une chaine
Entr�e : Un pointeur vers une cha�ne de caract�re
Sortie : Un entier positif*/

unsigned int getNumbersChar(char* ); 
/*Role : Renvoie une chaine de caract�re correspondant � un int
Entr�e : Un entier positif
Sortie : Un pointeur vers une chaine de caract�re*/
char *int2char(unsigned int nbr); 

/*Role : Renvoie le resultat de l'addition de deux lentiers
Entr�e : Deux lentiers
Sortie : Un lentier*/
lentier add_lentier(lentier, lentier);

/*Role : Renvoie le resultat de la soustraction de deux lentiers
Entr�e : Deux lentiers
Sortie : Un lentier*/
lentier sub_lentier(lentier, lentier);

/*Role : Renvoie le resultat de la soustraction de deux lentiers
Entr�e : Deux lentiers
Sortie : Un lentier*/
lentier mult_classique(lentier, lentier);

/*Role : Compare deux lentiers
Entr�e : Deux lentiers
Sortie : Un char (compris entre -1 et 1)*/
char cmp_lentier(lentier, lentier);

/*Role : Renvoie le r�sultat de la division de deux lentiers (quotient et reste)
Entr�e : Deux lentiers
Sortie : Un res_div */
res_div div_eucl(lentier, lentier);

/*Role : Renvoie un lentier(base 2^32) correspondant � un nombre dans une chaines de caract�res (base 10)
Entr�e : Un pointeur vers une cha�ne de caract�re
Sortie : Un lentier */
lentier dec2lentier(char*);

/*Role : Modifier la taille d'un lentier si ses cases de poids forts sont �gales � 0
Entr�e : Une r�f�rence vers un lentier
Sortie : vide*/
void lAdjust(lentier&);

/*Role : Formate la chaine de caract�re du calcul rentr� par l'utilisateur pour qu'elle soit dans le bon format
Entr�e : Un pointeur vers une cha�ne de caract�re
Sortie : une pointeur vers un tableau de chaine de caract�re */
char** parser(char*);

/*Role : Renvoie le resultat d'une multiplication modulaire
Entr�e : 3 lentiers
Sortie : 1 lentier */
lentier mul_mod(lentier, lentier, lentier);

/*Role : Renvoie le r�sultat d'une exponentiation modulaire
Entr�e : 3 lentiers
Sortie : 1 lentier */
lentier exp_mod(lentier, lentier, lentier);

/*Role : Renvoie la valeur d'un bit 
Entr�e : Un entier positif et l'indice du bit que l'on souhaite r�cup�rer
Sortie :  Un bool�en*/
bool dec2bin(unsigned int,int);

/*Role : Afficher un lentier
Entr�e : Un lentier
Sortie : vide */
void Affiche_lentier(lentier);

/*Role : Multiplie un lentier par 2^32 en faisant un d�calage 
Entr�e : Un char pour indiquer le sens (multplication ou division), un entier positif (le nombre de cases � d�caler), un lentier
Sortie : Un lentier */
lentier decalage(char, unsigned int, lentier);

/*Role : Copier un lentier valeur par valeur dans un autre
Entr�e : Un lentier
Sortie : Un lentier */
lentier estEgal(lentier);

/*Role : Ajouter un lentier avec un entier (gestion des d�passements)
Entr�e : Un lentier et un entier positif
Sortie : Un lentier */
lentier add_lentier_entier(lentier, unsigned int);

/*Role : Ajoute deux entiers et le stock dans un lentier (gestion des d�passements)
Entr�e : Deux entiers positifs
Sortie : Un lentier*/
lentier add_entier_entier(unsigned int, unsigned int);

/*Role : Renvoie le r�sultat d'une division euclidienne entre un lentier et un lentier de taille 1
Entr�e : Deux lentiers
Sortie : Un res_div */
res_div div_eucl_1case(lentier adiv, lentier bdiv);

/*Role : Renvoie le r�sultat d'une multiplication entre un lentier et un entier positif
Entr�e : Un lentier et un entier positif
Sortie : Un lentier */
lentier mult_lentier_entier(lentier, unsigned int);

/*Role : Renvoie une cha�ne de caract�re correspondant au nombre en base 10 �gal au lentier en base 2^32
Entr�e : Un lentier
Sortie : Un pointeur vers une cha�ne de caract�re */
char* lentier2dec(lentier);
