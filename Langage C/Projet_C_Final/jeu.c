#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "modele.h"

#define LIGNE printf("----------------------\n");

int main(){
    Lettres a;
    initLettres(&a);
    char c;
    for (int i=0; i<9; i++){
        if((i%2) == 0) printf("Le 1er joueur tire une lettre : voyelle ou consonne (v/c) ? :");
	else printf("Le 2ème joueur tire une lettre : voyelle ou consonne (v/c) ? : ");
        scanf("\n%c", &c);
        LIGNE
	      
        if (c == 'v') incArrayLettres(tirerVoyelle(), &a);
	else if(c == 'c') incArrayLettres(tirerConsonne(), &a);
	for(int d=0; d<=i; d++){
	  printf("%c", a.arrayLettres[d]);
	  printf(" ");
	}
	for(int d=i; d<8; d++){
	  printf("_");
	  printf(" ");
	}
	printf("\n");
	LIGNE
    }
    a.arrayLettres[9] = '\0';


    printf("\nJoueur 1 : proposez un mot :");
    scanf("%s", a.mot1);

    printf("Joueur 2 : proposez un mot :");
    scanf("%s", a.mot2);

    LIGNE
      
    printf("%s\n", message(jouer(&a)));
    printf("%s\n", plus_Long_Mot(&a));
    
    return EXIT_SUCCESS;
}
