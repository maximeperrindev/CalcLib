

typedef struct {
	unsigned int* p;
	unsigned int size;
}
lentier;

int getNumbersChar(char* );

void checkCharLength(char*, char*);

void remplirTableau(int, int, char* , unsigned int* );

void dynamicChar(char*&);

lentier add_lentier(lentier, lentier);

lentier sub_lentier(lentier, lentier);

lentier mult_classique(lentier, lentier);

char cmp_lentier(lentier, lentier);

lentier div_eucl(lentier a, lentier b);

lentier dec2lentier(char*, int);

void lAdjust(lentier&);

void parser(char*);

lentier mul_mod(lentier, lentier, lentier);

lentier exp_mod(lentier, lentier, lentier);

bool dec2bin(unsigned int,int);

void Affiche_lentier(lentier a);
