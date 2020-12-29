#include <stdlib.h>
#include <stdio.h>
#include<libsx.h>
#include "modele.h"
#include "callbacks.h"


extern Widget Zone[9], BConsonne, BVoyelle, BJouer, BRejouer, BMot, ZoneSaisie1, ZoneSaisie2, Message, AfficheMotLong;
//callback bouton quit
//role: terminer l'application
void quit(Widget w, void *d)  {
  exit(EXIT_SUCCESS);
}

//Role: convertir et affiche le char b dans la zone d'affichage i
static void afficher(char b, int i){
  SetLabel(Zone[i], &b);
  if (i==8){
    SetWidgetState(BConsonne, 0); //apres affichage de 9 lettres le button Consonne ne marche plus
    SetWidgetState(BVoyelle, 0); //apres affichage de 9 lettres le button Voyelle ne marche plus
    SetWidgetState(BJouer, 1); //apres affichage de 9 lettres le button commecnce a marcher
  }
}

//Role: Callback bouton voyelles.
void voyelle(Widget w, void *d) {
   int i = getNb(d);
   char b = tirerVoyelle(d);
   incArrayLettres(b, d);
   afficher(b, i);  
}

//Role: Callback bouton consonnes.
void consonne(Widget w, void *d) {
   int i = getNb(d);
   char b =tirerConsonne(d);
   incArrayLettres(b, d);
   afficher(b, i);  
}

//Role: Callback bouton jouer.
void jouerButton(Widget w, void *d) {
   setMots(d, GetStringEntry(ZoneSaisie1), GetStringEntry(ZoneSaisie2));
   SetLabel(Message, message(jouer(d)));
   SetWidgetState(BMot, 1);
   SetWidgetState(BRejouer, 1);  
   SetWidgetState(BJouer, 0); //désactiver son propre bouton après utilisation
}

//Role: Callback bouton mot plus long.
void motLongueButton(Widget w, void *d) {
   SetLabel(AfficheMotLong, plus_Long_Mot(d));
 
}

//Role: Callback bouton rejouer.
void rejouerButton(Widget w, void *d) {
   initLettres(d);
   for(int i=0; i<9; i++)   //pour effacer les lettres déjà affichées
     SetLabel(Zone[i], " ");
   SetWidgetState(BConsonne, 1); //réactiver les boutons de Consonne et Voyelle
   SetWidgetState(BVoyelle, 1); 
   SetWidgetState(BMot, 0);  //désactiver mot plus longue
   SetWidgetState(BRejouer, 0); //désactiver son propre bouton après utilisation
}
