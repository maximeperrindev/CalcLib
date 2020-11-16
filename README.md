# CalcLib
A library for multi-precision processing

# New structure
lentier:

	unsigned int* p;
	unsigned int size;
  
p is a pointer to 32 bits arrays of unsigned int ; size is the number of 32 bits arrays

# How to use it ?

* Operations with lentiers:

  - Add:
  
        lentier add_lentier(lentier, lentier);
        
  - Sub:
  
        lentier sub_lentier(lentier, lentier);

  - Multiply:
        
        lentier mult_classique(lentier, lentier);

  - Divide:
        
        res_div div_eucl(lentier, lentier);
        
        Wich returns a res_div composed of 2 lentiers : q is the quotient and r the remainder.

* Cryptographic computing:

   - Modular exponentiation:
   	
			lentier exp_mod(lentier, lentier, lentier);

   - Modular multiplication:
   	
			lentier mul_mod(lentier, lentier, lentier);

* Other features:

   - Display:
   	
			void Affiche_lentier(lentier);

