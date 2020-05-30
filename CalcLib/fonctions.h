

typedef struct {
	unsigned int* p;
	unsigned int size;
}
lentier;

int getNumbersChar(char* );

int tailleBase(int, char *);

void checkCharLength(char*, char*);

void remplirTableau(int, int, char* , unsigned int* );

void dynamicChar(char*&);

lentier addition(lentier, lentier);

lentier soustraction(lentier, lentier);

lentier multiplication(lentier, lentier);