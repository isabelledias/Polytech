#pragma once

#define VOYELLES_QUANT 45
#define CONSONNES_QUANT 55

typedef struct{
  char arrayLettres[10];
  int nb;
  char mot1[10], mot2[10];
} Lettres;

extern void initLettres(Lettres *);
extern int getNb(Lettres *);
extern void setMots(Lettres *, char *, char *);
extern void incArrayLettres(const char, Lettres *);
extern char tirerVoyelle();
extern char tirerConsonne();
extern int Mot_Existant(char *);
extern int Mot_Valide(char *, char *);
extern void Conv_minusc(char *);

extern int jouer(Lettres *);
extern char* message(int);

extern char* plus_Long_Mot(Lettres *);
