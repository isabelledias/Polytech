#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "modele.h"

/*
 *Rôle : initialise la valeur courante de le taux de change
 */
void initLettres(Lettres *d) {
  d->nb =0;
}

/*
 *Rôle : vérifier le nombre total de lettres sélectionnées au 
 *       hasard et ainsi aider à l'affichage dans l'interface
 */
int getNb(Lettres *d) {
  return d->nb;
}

/*
 *Rôle : enregistrer les mots proposés par chaque joueur dans le type Lettres
 */
void setMots(Lettres *d, char *mot1, char *mot2){
  strcpy(d->mot1, mot1);
  strcpy(d->mot2, mot2);
}

//Rôle : Enregistrer dans le type Lettres un caractère issu de tirer_Voyelle ou tirer_Consonne
void incArrayLettres(const char c, Lettres *d){
    d->arrayLettres[d->nb] = c;
    d->nb = d->nb +1;
}

/*
 *Rôle: renvoie une voyelle tirée au hasard dans l’ensemble des voyelles disponibles;
 */
char tirerVoyelle(){
    static const char voyelles[] = "AAAAAAAAAEEEEEEEEEEEEEEEIIIIIIIIOOOOOOUUUUUUY";
    srand(time(NULL));
 
    const int random_index = rand() % VOYELLES_QUANT;
 
    return voyelles[random_index];
}

//Rôle: renvoie une consonne tirée au hasard dans l’ensemble des consonnes disponibles;
char tirerConsonne(){
    static const char consonnes[] = "BBCCDDDFFGGHHJKLLLLLMMMNNNNNNPPQRRRRRRSSSSSSTTTTTTVVWXZ";
    srand(time(NULL));
 
    const int random_index = rand() % CONSONNES_QUANT;
 
    return consonnes[random_index];
}


/*
 * Rôle : La fonction Mot_Valide prend en entrée un mot et une array e renvoit
 * 1 si ce mot a jusqu'à 9 caracteres et utilise le chaîne de caracteres donnée par l'array
 * 0 sinon
 */
int Mot_Valide(char *mot, char *lettres){
  int taille_mot = strlen(mot); //Calcul de la taille du mot
  if (taille_mot > 9) return 0; //max de 9 lettres
  
  int alpha[26];
  //Initialisation de alpha à 0
  for(int i=0; i<26;i++) alpha[i]=0;
  
  for(int i=0;i<9;i++) alpha[lettres[i]-'A']++;

  //Invariant de boucle: taille_mot et mot
  for(int i=0;i<taille_mot;i++){
    alpha[mot[i]-'a']--;
    if(alpha[mot[i]-'a'] < 0){
      return 0;
    }
  }
  return 1;
}



/*
 * Rôle : La fonction Mot_Valide prend en entrée un mot et renvoit 
 *        1 si ce mot est dans le fichier "liste_francais.txt"
 *        0 sinon
 */
int Mot_Existant(char *mot){
  FILE *fliste;
  int n=0;
  char car[11];

  //Ouverture du fichier contenant les mots
  if((fliste=fopen("liste_francais.txt", "r"))==NULL){
    return 0;
  }

  //La procédure suivante effectue la recherche du mot
  //Invariant de boucle: fliste, car et mot
  while(fgets(car,10,fliste)!=NULL){
    while(car[n]==mot[n]){
      if(car[n]=='\0') return 1;
      n++;
    }
    if(mot[n]=='\0' && !isalpha(car[n])) return 1;
    n=0;
    strcpy(car, "\0");
  }

  fclose(fliste);
  return 0;
}


/*
 *Rôle : convertir les letter majuscules à minuscule pour le cas de avoir un jouer que faire un input
 *avec les lettres majuscules.
 */
void Conv_minusc(char *mot){
  int taille_mot=strlen(mot);
  for(int i=0; i<taille_mot;i++){
    if(mot[i]<='Z' && mot[i]>='A') mot[i]=(char)((int)mot[i]+32);
  }
}



//Rôle : comparer les mots donnés par les joueurs et dire quel est le mot le plus long entre le deux
int jouer(Lettres *d){
  int nbcar1=0, nbcar2=0;
  Conv_minusc(d->mot1);
  Conv_minusc(d->mot2);
  if(Mot_Valide(d->mot1, d->arrayLettres))
    if(Mot_Existant(d->mot1)) nbcar1=strlen(d->mot1);

  if(Mot_Valide(d->mot2, d->arrayLettres))
    if(Mot_Existant(d->mot2)) nbcar2=strlen(d->mot2);


  if (nbcar1==nbcar2){
    if (nbcar1==0) return 0;   //aucun mot valide
    else return 3;             //égalité
  }
  if (nbcar1>nbcar2) return 1; //jouer 1 a gagne
  else return 2;               //jouer 2 a gagne
}


//Rôle : envoi le message annonçant le vainqueur
char* message(int i){
  switch (i){
  case 1: return "Le joueur 1 a gagne.\n"; break;
  case 2: return "Le joueur 2 a gagne.\n"; break;
  case 3: return "Les 2 joueurs ont des mots de meme longueur : egalite.\n"; break;
  default: return "Aucun joueur n'a donne de mot valide\n"; break; //cas 0, on le mis dans default pour ne donner pas  une warning
  }
}


/*
 * Rôle : parcours la liste complète des mots français dans le 
 *        fichier et conserve le mot valide le plus long.
 *        
 */

char* plus_Long_Mot(Lettres *d){
  FILE *fliste;
  int n=0, taille_mot=0;               //n a la longueur du mot temporaire valide, 
                                       //et taille_mot a la longeur du mot le plus long trouvé jusqu'à présent
  char  temp[11];                      //temp conserve temporairement le mot qu'on verifie                   
  char *mot = malloc(sizeof(char)*10); //mot conserve le mot le plus long trouvé jusqu'à présent

  if((fliste=fopen("liste_francais.txt", "r"))==NULL){
    exit(1);
  }

  while(fgets(temp, 10, fliste)!=NULL){   //parcourir tous les mots du fichier
    if(Mot_Valide(temp, d->arrayLettres)) {
      n = strlen(temp);  
      if (n> taille_mot){
	taille_mot = n;
	strcpy(mot, temp);
      }
    }
  }
  fclose(fliste);
  if(taille_mot==0) return "________"; //Cas où aucun mot ne peut être formé
  return mot;
}

