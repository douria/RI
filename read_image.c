#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

int main(int argc, char *argv[])
{
  int i,j,n,nx,ny,nb;
  CIMAGE cim;
  //le tableau des pixels
  int couleur[64];
 /*-------------------------*/
 /*initialisation du tableau*/
 /*-------------------------*/
 for (i = 0; i < 64; i++) {   /* pixel par pixel */
      couleur[i]=0;
    }

  /*------------------------------------------------*/
  /* lecture d'une image requête                    */
  /*------------------------------------------------*/
  read_cimage(argv[1],&cim);
  /*------------------------------------------------*/
  /* affichage des valeurs pour le premier bloc 8x8 */
  /* comme exemple de traitement                    */
  /*------------------------------------------------*/
  printf("Largeur de l'image : %d\n",cim.nx);
  printf("Hauteur de l'image : %d\n",cim.ny);
  printf("Plan rouge du premier bloc 8x8 :\n");
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    printf("  ");
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      printf("%4d",cim.r[i][j]);
    }
    printf("\n");
  }
  printf("Plan vert du premier bloc 8x8 :\n");
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    printf("  ");
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      printf("%4d",cim.g[i][j]);
    }
    printf("\n");
  }
  printf("Plan bleu du premier bloc 8x8 :\n");
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    printf("  ");
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      printf("%4d",cim.b[i][j]);
    }
    printf("\n");
  }
  /*------------------------------------------------*/
  /********On calcul l'indice RGB de chaque pixel************/

int indice_couleur=0;

   for (i = 0; i < cim.nx; i++) {       /* ligne par ligne */
   	 for (j = 0; j < cim.ny; j++) {   /* pixel par pixel */
		  indice_couleur=((cim.r[i][j]/64)+4*(cim.g[i][j]/64)+16*(cim.b[i][j]/64));
		  couleur[indice_couleur]=couleur[indice_couleur]+1;
   	 }
    
    }

/*****************affichage de couleur*************/
for (i = 0; i < 64; i++) {   /* pixel par pixel */
      printf(" %d      ",couleur[i]);
}

  exit(0);
}
