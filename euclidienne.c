
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.h"

int couleur[64];

void init(){
	int i;
	for(i=0;i<64;i++){
		couleur[i]=0;
	}

}

int * hist ( char * nom_image){
int i;  
int j;
CIMAGE cim;
int indice_couleur=0;
	read_cimage(nom_image, &cim);
	init();
	 for (i = 0; i < cim.nx; i++) {       /* ligne par ligne */
	   	 for (j = 0; j < cim.ny; j++) {   /* pixel par pixel */
		
			  indice_couleur=((cim.r[i][j]/64)+4*(cim.g[i][j]/64)+16*(cim.b[i][j]/64));
			  couleur[indice_couleur]=couleur[indice_couleur]+1;
	   	 }
	    
	    }

return couleur;
};


float distance_euclidienne(int* couleur1 , int* couleur2){
float DE=0;
float racine;
int j;
	 for (j = 0; j < 64; j++) {   /* pixel par pixel */
  
			 DE= ((couleur1[j]-couleur2[j])*(couleur1[j]-couleur2[j]));
	   }
racine=sqrt(DE);
return racine;
}


int main(int argc, char *argv[])
{


KEY * classement;
char ** noms_images;
int nb_images;
 //le tableau des pixels
int couleur[64];
CIMAGE cima;
CIMAGE cim;
float DE;
int i,j,indice_couleur;

read_cimage(argv[1],&cima);

//on lit le contenu du fichier contenant les noms de toutes les images 
noms_images= readList(argv[2], &nb_images);

//on alloue la taille de memoire necessaire 
classement=malloc(sizeof(KEY)*nb_images);

//on calcule l'histogramme de l'image 
 for (i = 0; i < cim.nx; i++) {       /* ligne par ligne */
   	 for (j = 0; j < cim.ny; j++) {   /* pixel par pixel */
		
		  indice_couleur=((cim.r[i][j]/64)+4*(cim.g[i][j]/64)+16*(cim.b[i][j]/64));
		  couleur[indice_couleur]=couleur[indice_couleur]+1;
   	 }
    
    }

//on calcule les distances euclidiennes de toutes les images par rapport a une image 

 for (i=0;i < nb_images;i++){
	DE=distance_euclidienne(couleur , hist ( noms_images[i]));
	classement[0].k=i;
	classement[0].d=DE;
        printf("distance euclidienne=%f \t",DE);

 }

return 0;
}
