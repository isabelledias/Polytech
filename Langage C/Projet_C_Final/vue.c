/* cette vue fabrique lL'interface graphique est programme a l'aide libsx
 */

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "modele.h"
#include "callbacks.h"


//Variables gobables
Widget 
    BJouer, // bouton pour gerer la partie entre les deux joueurs
    BRejouer, //bouton pour démarrer un nouveau jeu
    BConsonne, //bouton pour choisir une consonne
    BVoyelle, // bouton pour choisir une voyelle
    BMot, //  bouton pour afficher le mot plus long
    ZoneSaisie1, ZoneSaisie2, //Zone pour saisir le mot de chaque joueur
    Message, //message pour annoncer qui a gagner
    AfficheMotLong, //Zone pour affichage du mot plus longue
    Zone[9]; //la zone d'affichage

//role: creation et assemblage des widgets
void init_display(int argc, char *argv[], void *d) {

  const int TailleZoneAffichage=100;

  Widget   
    Label1, Label2, // étiquettes pour la saisie de mots de chaque joueur
    BQuit; //bouton pour terminer le programme

    
  //Creation de la zone d'affichage
  Zone[0] = MakeLabel("       ");
  Zone[1] = MakeLabel("       ");
  Zone[2] = MakeLabel("       ");
  Zone[3] = MakeLabel("       ");
  Zone[4] = MakeLabel("       ");
  Zone[5] = MakeLabel("       ");
  Zone[6] = MakeLabel("       ");
  Zone[7] = MakeLabel("       ");
  Zone[8] = MakeLabel("       ");


  Label1 = MakeLabel("Mot joueur 1: ");
  Label2 = MakeLabel("Mot joueur 2: ");
  Message = MakeLabel("                                                      ");
  AfficheMotLong = MakeLabel("          ");

  ZoneSaisie1 = MakeStringEntry(NULL, TailleZoneAffichage, NULL, NULL);
  ZoneSaisie2 = MakeStringEntry(NULL, TailleZoneAffichage, NULL, NULL);
  

  //Creation des boutons Quit, BDollar, BEuros
  BQuit = MakeButton("  Quit  ", quit, NULL);
  BRejouer = MakeButton(" Rejouer", rejouerButton, d);
  BVoyelle = MakeButton(" Voyelle ", voyelle , d); //callback Voyelle
  BConsonne = MakeButton(" Consonne ", consonne, d);  //callback consonne
  BJouer = MakeButton(" Jouer ", jouerButton, d); //callback jouerButton
  BMot = MakeButton(" Mot Plus Long ", motLongueButton, d); //callback jouerButton
  

  //Placement des boutons dans la fenetre graphique
  SetWidgetPos(BVoyelle, PLACE_RIGHT, BConsonne, NO_CARE, NULL);
  SetWidgetPos(Zone[0], PLACE_UNDER, BConsonne, NO_CARE, NULL);
  SetWidgetPos(Zone[1], PLACE_RIGHT, Zone[0], PLACE_UNDER, BConsonne);
  SetWidgetPos(Zone[2], PLACE_RIGHT, Zone[1], PLACE_UNDER, BConsonne);
  SetWidgetPos(Zone[3], PLACE_RIGHT, Zone[2], PLACE_UNDER, BConsonne);
  SetWidgetPos(Zone[4], PLACE_RIGHT, Zone[3], PLACE_UNDER, BConsonne);
  SetWidgetPos(Zone[5], PLACE_RIGHT, Zone[4], PLACE_UNDER, BConsonne);
  SetWidgetPos(Zone[6], PLACE_RIGHT, Zone[5], PLACE_UNDER, BConsonne);
  SetWidgetPos(Zone[7], PLACE_RIGHT, Zone[6], PLACE_UNDER, BConsonne);
  SetWidgetPos(Zone[8], PLACE_RIGHT, Zone[7], PLACE_UNDER, BConsonne);

  SetWidgetPos(Label1, PLACE_UNDER, Zone[0], NO_CARE, NULL);
  SetWidgetPos(ZoneSaisie1, PLACE_RIGHT, Label1, PLACE_UNDER, Zone[0]);
  SetWidgetPos(Label2, PLACE_RIGHT, ZoneSaisie1, PLACE_UNDER, Zone[0]);
  SetWidgetPos(ZoneSaisie2, PLACE_RIGHT, Label2, PLACE_UNDER, Zone[0]);

  SetWidgetPos(BJouer, PLACE_UNDER, Label1, NO_CARE, NULL);
  SetWidgetPos(Message, PLACE_RIGHT, BJouer, PLACE_UNDER, Label1);
  SetWidgetPos(BMot, PLACE_UNDER, BJouer, NO_CARE, NULL);
  SetWidgetPos(AfficheMotLong, PLACE_RIGHT, BMot, PLACE_UNDER, BJouer);
  SetWidgetPos(BRejouer, PLACE_UNDER, Label1, ATTACH_RIGHT, Zone[7]);
  SetWidgetPos(BQuit, PLACE_UNDER, BJouer, ATTACH_RIGHT, Zone[7]);


 

  //pour geres les couleurs
  GetStandardColors();
  SetBgColor(Zone[0], GetRGBColor(225,192,200));
  SetBgColor(Zone[1], GetRGBColor(225,192,200));
  SetBgColor(Zone[2], GetRGBColor(225,192,200));
  SetBgColor(Zone[3], GetRGBColor(225,192,200));
  SetBgColor(Zone[4], GetRGBColor(225,192,200));
  SetBgColor(Zone[5], GetRGBColor(225,192,200));
  SetBgColor(Zone[6], GetRGBColor(225,192,200));
  SetBgColor(Zone[7], GetRGBColor(225,192,200));
  SetBgColor(Zone[8], GetRGBColor(225,192,200));

  SetBgColor(ZoneSaisie1, GetRGBColor(211,211,211));
  SetBgColor(ZoneSaisie2, GetRGBColor(211,211,211));

  //pour afficher l'interface
  SetWidgetState(BJouer, 0);
  SetWidgetState(BMot, 0);
  SetWidgetState(BRejouer, 0);
  ShowDisplay();
}
