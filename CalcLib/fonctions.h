

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

int getNumbersChar(char* );

void checkCharLength(char*, char*);

void remplirTableau(int, int, char* , unsigned int* );

void dynamicChar(char*&);

lentier add_lentier(lentier, lentier);

lentier sub_lentier(lentier, lentier);

lentier mult_classique(lentier, lentier);

char cmp_lentier(lentier, lentier);

res_div div_eucl(lentier a, lentier b);

lentier dec2lentier(char*);

void lAdjust(lentier&);

char** parser(char*);

lentier mul_mod(lentier, lentier, lentier);

lentier exp_mod(lentier, lentier, lentier);

bool dec2bin(unsigned int,int);

void Affiche_lentier(lentier a);

lentier decalage(char sens, unsigned int decal, lentier a);

lentier estEgal(lentier a);

lentier add_lentier_entier(lentier, unsigned int);

lentier add_entier_entier(unsigned int, unsigned int);

res_div div_eucl_1case(lentier adiv, lentier bdiv);

lentier mult_lentier_entier(lentier, unsigned int);

char* lentier2dec(lentier);
