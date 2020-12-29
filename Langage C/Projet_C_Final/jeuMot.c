/* ce programme est un convertisseur Euros <-> Dollars 
 * L'interface graphique est programme a l'aide libsx
 */

#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "modele.h"
#include "vue.h"

int main(int argc, char *argv[]) {
  Lettres d;
  if (OpenDisplay(argc, argv) == 0) {
    fprintf(stderr, "Can't open display\n");
    return EXIT_FAILURE;
  }
  //initialliser la donnee partagee entre le modele et le interphace graphique
  initLettres(&d);
  
  //creer l'IG et l'affcher a l'ecran
  init_display(argc, argv, &d);
  MainLoop();

  return EXIT_SUCCESS;
}
