
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.h"

#define TAILLE_MAX_C 580
#define TAILLE_MAX 5
#define TAILLE_MAX_LINE 2400

float couleur[64];
float sift[256];
void init_(){
	int i;
	for(i=0;i<64;i++){
		couleur[i]=0.0;
	}

}

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





void init_Sift(){
	int i;
	for(i=0;i<256;i++){
		sift[i]=0.0;
	}

}


/********calcule la distance euclidienne entre deux couleur***************/

float distance_euclidienne_Sift(float * sift1 , float* sift){
float DE=0.0;
float racine;
int j;
	 for (j = 0; j < 256; j++) {  
  
			 DE=DE+ ((sift1[j]-sift[j])*(sift1[j]-sift[j]));
	   }
racine=sqrt(DE);
return racine;
}


int main(int argc, char *argv[])
{
char line[TAILLE_MAX_C];
char ligne[TAILLE_MAX_LINE];

FILE * hist_couleur;
FILE* hist_sift;
FILE* hist_sift_ref;
KEY * classement;
KEY * classement_mean;
KEY * classement_sift;
char ** noms_images;
int nb_images;
 //le tableau des pixels
float couleur1[64];
char cluster[TAILLE_MAX];
float nb_cluster=0;
float sift1[256];
CIMAGE cima;
float DE,DE_Sift;
int i,j,indice_couleur, in;
char chemin[15]="sift/test/1nn/";
char final[5]=".sift";
char nom_requete[50];
char nom_requete2[50];
/*strcpy(nom_requete,argv[4]);
nom_requete2=strtok(nom_requete,".");
strcat(nom_requete2,final);*/
//les histogrammes de sift
hist_sift=fopen(argv[2],"r");
//la liste des histogrammes de couleurs 
hist_couleur=fopen(argv[3],"r");
//l'image requete 
read_cimage(argv[4],&cima);

//les histogrammes de sift
hist_sift_ref=fopen(argv[5],"r");

//on lit le contenu du fichier contenant les noms de toutes les images 
noms_images= readList(argv[1], &nb_images);

//on alloue la taille de memoire necessaire 
classement=malloc(sizeof(KEY)*nb_images);
classement_mean=malloc(sizeof(KEY)*nb_images);
classement_sift=malloc(sizeof(KEY)*nb_images);

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

//initialise the array
for (j = 0; j < 256; j++) {   /* pixel par pixel */		
	sift1[j]=0.0;	
}
//on calcule l'histogramme de l'image 


 if(hist_sift_ref)
	{
		while (fgets(cluster, TAILLE_MAX, hist_sift_ref) != NULL)
		{
			
			in = atoi(cluster);
			sift1[in]++;
			nb_cluster++;
		}
			
	}

int k=0;

/************La partie qui remplie la liste chainée avec pour chasue image son DE ******************/
char * mot;
//on recupere l'hist de l'image en question
mot=malloc(sizeof(char)*100);


for(j=0;j<nb_images; j++){

	if(fgets(line, TAILLE_MAX_C, hist_couleur)!=NULL){
		for(i=0;i<64;i++){
			mot = strtok(&line[k]," ");
			couleur[i]=atof(mot);
			k=k+9;
		}
	k=0;

	DE=distance_euclidienne_( couleur ,couleur1);
	classement[j].k=j;
	classement[j].d=DE;
	
	  }

}

k=0;
for(j=0;j<nb_images; j++){

	if(fgets(ligne, TAILLE_MAX_LINE, hist_sift)!=NULL){
		for(i=0;i<256;i++){
			mot = strtok(&ligne[k]," ");
			sift[i]=atof(mot);
			k=k+9;
		}
	k=0;

	DE_Sift=distance_euclidienne_Sift( sift1 ,sift);
	classement_sift[j].k=j;
	classement_sift[j].d=DE_Sift;
	
	  }

}

for(j=0;j<nb_images; j++){

	classement_mean[j].k=classement[j].k;
	classement_mean[j].d=((classement[j].d + classement_sift[j].d)/2) ;

	
}


print_html_head("resultat.html");
printf("<p> ");
printf("image query ");
printf("</p> ");
printf("<img src=\"");
printf("%s ",argv[4]);
printf("\">\n");


printf("<p> ");
printf("display results ");
printf("</p> ");
  qsort (classement_mean, nb_images, sizeof(KEY), keyCompare);

j=0;
while(j<10){
printf("<img src=\"");
		printf("%s ",noms_images[classement[j+1].k]); j++;
		printf("\">\n");
		printf("<p> ");
		printf("%s a pour DE : %f ",noms_images[classement[j+1].k],classement[j+1].d);
		printf("</p> ");
	
}
print_html_tail();
	
return 0;
}
