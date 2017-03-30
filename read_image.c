#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

int main(int argc, char *argv[])
{

  FILE* res;
  char* nom;
  int indice_couleur=0;
  int i,j,n,nx,ny,nb;
  CIMAGE cim;
  int taille;
  //le tableau des pixels
  int couleur[64];
  /*taille=strlen(argv[1]);
  nom=malloc(sizeof(char)*taille+5);
  strcpy(nom,argv[1]);
  nom[taille+1]='.';
  nom[taille+2]='r';
  nom[taille+3]='e';
  nom[taille+4]='s';
  nom[taille+5]='\0';
*/
  res=fopen(argv[2],"w+");

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
 /* printf("Largeur de l'image : %d\n",cim.nx);
  printf("Hauteur de l'image : %d\n",cim.ny);
  printf("Plan rouge du premier bloc 8x8 :\n");*/
/*  for (j = 0; j < 8; j++) {      
    printf("  ");
    for (i = 0; i < 8; i++) {  
      printf("%4d",cim.r[i][j]);
    }
    printf("\n");
  }
  printf("Plan vert du premier bloc 8x8 :\n");
  for (j = 0; j < 8; j++) {     
    printf("  ");
    for (i = 0; i < 8; i++) {   
      printf("%4d",cim.g[i][j]);
    }
    printf("\n");
  }
  printf("Plan bleu du premier bloc 8x8 :\n");
  for (j = 0; j < 8; j++) {       
    printf("  ");
    for (i = 0; i < 8; i++) {   
      printf("%4d",cim.b[i][j]);
    }
    printf("\n");
  }*/
  /*------------------------------------------------*/
  /********On calcul l'indice RGB de chaque pixel************/

/*  On met le resultat dans le fichier */


   for (i = 0; i < cim.nx; i++) {       /* ligne par ligne */
   	 for (j = 0; j < cim.ny; j++) {   /* pixel par pixel */
		
		  indice_couleur=((cim.r[i][j]/64)+4*(cim.g[i][j]/64)+16*(cim.b[i][j]/64));
		  couleur[indice_couleur]=couleur[indice_couleur]+1;
   	 }
    
    }

/*****************affichage de couleur*************/
for (i = 0; i < 64; i++) {   /* pixel par pixel */
      fprintf(res,"%d\n",couleur[i]); 
}

fclose(res);
  exit(0);
}
