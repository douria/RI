
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.h"
#include "cgiu.h"
#define TAILLE_MAX 580

float couleur[64];

void init_(){
	int i;
	for(i=0;i<64;i++){
		couleur[i]=0.0;
	}

}

void hist_ ( char * nom_image ){
int i;  
int j;
CIMAGE cim;
int indice_couleur=0;
int nb_pixel;


	read_cimage(nom_image, &cim);

	nb_pixel=cim.nx*cim.ny;
	init_();

	 for (i = 0; i < cim.nx; i++) {       /* ligne par ligne */
	   	 for (j = 0; j < cim.ny; j++) {   /* pixel par pixel */
			  indice_couleur=(cim.r[i][j]/64)+4*(cim.g[i][j]/64)+16*(cim.b[i][j]/64);
			  couleur[indice_couleur]=couleur[indice_couleur]+1.0;
	   	 }
	    
	    }
	
	for (j = 0; j < 64; j++) {   /* pixel par pixel */
		
		couleur[j]=couleur[j]/nb_pixel;
	 }

};

/********calcule la distance euclidienne entre deux couleur***************/

float distance_euclidienne_(float * couleur1 , float* couleur2){
float DE=0.0;
float racine;
int j;
	 for (j = 0; j < 64; j++) {   /* pixel par pixel */
  
			 DE=DE+ ((couleur1[j]-couleur2[j])*(couleur1[j]-couleur2[j]));
	   }
racine=sqrt(DE);
return racine;
}


int main(int argc, char *argv[])
{
char ligne[TAILLE_MAX];
//FILE* resultat;
FILE * hist;
KEY * classement;
char ** noms_images;
int nb_images;
 //le tableau des pixels
float couleur1[64];
CIMAGE cima;
//CIMAGE cim;
float DE;
int i,j,indice_couleur;

hist=fopen("hist.txt","r");
read_cimage(argv[1],&cima);

//on lit le contenu du fichier contenant les noms de toutes les images 
noms_images= readList(argv[2], &nb_images);

//on alloue la taille de memoire necessaire 
classement=malloc(sizeof(KEY)*nb_images);


//initialise the array
for (j = 0; j < 64; j++) {   /* pixel par pixel */		
	couleur1[j]=0.0;	
}
//on calcule l'histogramme de l'image 
 for (i = 0; i < cima.nx; i++) {       /* ligne par ligne */
   	 for (j = 0; j < cima.ny; j++) {   /* pixel par pixel */
		
		  indice_couleur=((cima.r[i][j]/64)+4*(cima.g[i][j]/64)+16*(cima.b[i][j]/64));
		  couleur1[indice_couleur]=couleur1[indice_couleur]+1.0;
		
   	 }
    
  }

 for (j = 0; j < 64; j++) {   
	 couleur1[j]=couleur1[j]/(cima.ny*cima.nx);		
}

/************partie ayant generé le fichire hist.txt*****************/

/*	resultat=fopen("hist.txt","w+");
//on calcule les distances euclidiennes de toutes les images par rapport a une image 

 for (i=0;i < nb_images;i++){
	//on ouvre le fichier 
	hist_ (noms_images[i]);
	for(int i=0;i<64;i++){
		fprintf(resultat,"%f ",couleur[i]);
	}
	fprintf(resultat,"\n");
 }
fclose(resultat);*/


int k=0;

/************La partie qui remplie la liste chgainée avec pour chasue image son DE ******************/
char * mot;
//on recupere l'hist de l'image en question
mot=malloc(sizeof(char)*100);
for(j=0;j<nb_images; j++){

	if(fgets(ligne, TAILLE_MAX, hist)!=NULL){
		for(i=0;i<64;i++){
			mot = strtok(&ligne[k]," ");
			couleur[i]=atof(mot);
			k=k+9;
		}
	k=0;

	DE=distance_euclidienne_( couleur ,couleur1);
	classement[j].k=j;
	classement[j].d=DE;
	}

}
print_html_head("resultat.html");
printf("<p> ");
printf("image query ");
printf("</p> ");
printf("<img src=\"");
printf("%s ",argv[1]);
printf("\">\n");


printf("<p> ");
printf("display results ");
printf("</p> ");
qsort (classement, nb_images, sizeof(KEY), keyCompare);

j=0;
while(j<10){
	//if(strcmp(noms_images[classement[j].k],argv[1])!=0 ){
		printf("<img src=\"");
		printf("%s ",noms_images[classement[j+1].k]); j++;
		printf("\">\n");
		printf("<p> ");
		printf("%s a pour DE : %f ",noms_images[classement[j+1].k],classement[j+1].d);
		printf("</p> ");
	//}
}
 print_html_tail();

return 0;
}
