
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.h"
#include "cgiu.h"
#define TAILLE_MAX 20


int sift[256];

void init_(){
	int i;
	for(i=0;i<64;i++){
		sift[i]=0;
	}

}

void hist_ ( char * nom_image ){
int i;  

FILE * fich_sift;
char sift[6]=".sift";

char nom_fich[20];
char cluster[20];
strcpy(nom_fich,nom_image);
strcat(nom_fich,sift);


	//read_cimage(nom_image, &cim);
	fich_sift=fopen(nom_fich,"r");
	init_();

	 while(fgets(cluster, TAILLE_MAX, fich_sift)!=NULL){
		for(i=0;i<64;i++){
			i=atoi(cluster);
			sift[i]=sift[i]++;	
		}
	}
fclose(fich_sift);
};

int main(int argc, char *argv[])
{
char ligne[TAILLE_MAX];
FILE* resultat;
FILE * hist;
char ** noms_images;
int nb_images;
int i,j;


//on lit le contenu du fichier contenant les noms de toutes les images 
noms_images= readList(argv[2], &nb_images);


/************partie ayant generé le fichire hist.txt*****************/

resultat=fopen("hist_sift.txt","w+");
//on calcule les distances euclidiennes de toutes les images par rapport a une image 

 for (i=0;i < nb_images;i++){
	//on ouvre le fichier 
	hist_ (noms_images[i]);
	for(int i=0;i<64;i++){
		fprintf(resultat,"%i ",sift[i]);
	}
	fprintf(resultat,"\n");
 }
fclose(resultat);


return 0;
}
