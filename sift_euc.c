#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.h"
#include "cgiu.h"
#define TAILLE_MAX 5
#define TAILLE_MAX_LINE 2400

float sift[256];

void init_(){
	int i;
	for(i=0;i<256;i++){
		sift[i]=0.0;
	}

}


/********calcule la distance euclidienne entre deux couleur***************/

float distance_euclidienne_(float * sift1 , float* sift){
float DE=0.0;
float racine;
int j;
	 for (j = 0; j < 256; j++) {  
  
			 DE=DE+ ((sift1[j]-sift[j])*(sift1[j]-sift[j]));
	   }
racine=sqrt(DE);
return racine;
}



void hist_ ( char * nom_sift , FILE * resultat){

FILE * fich_sift;
char cluster[5];
int i,in,j=0;
float nb_cluster;
init_();
fich_sift=fopen(nom_sift,"r");

nb_cluster=0.0;
	if(fich_sift)
	{
		while (fgets(cluster, TAILLE_MAX, fich_sift) != NULL)
		{
			
			in = atoi(cluster);
			sift[in]++;
			nb_cluster++;
			
		}
			
	}
	for(int j=0;j<256;j++)
	{	
		sift[j]=sift [j]/nb_cluster;
		fprintf(resultat,"%f ",(sift[j]));
	}
	fprintf(resultat,"\n");

fclose(fich_sift);
//fprintf(stderr,"after close of file      " );
};

int main(int argc, char *argv[])
{
FILE* hist;
KEY * classement;
FILE* hist_ref;
//FILE* resultat;
char ** noms_images;
int nb_images;
int i,j;
float sift1[256];
noms_images= readList(argv[1], &nb_images);
char cluster[TAILLE_MAX];
float nb_cluster=0;
char ligne[TAILLE_MAX_LINE];
float DE;
int in;
char * nom_im;
char * nom_int;
 /*resultat=fopen("hist_sift.txt","w+");

for (i=0;i < nb_images;i++){
	//fprintf(stderr,"%s", noms_images[i]);
	hist_ (noms_images[i], resultat);
	
	//fprintf(stderr,"before second loop" );
 }
fclose(resultat);
*/

hist=fopen("hist_sift.txt","r");
hist_ref=fopen (argv[2],"r");
//initialise the array
for (j = 0; j < 256; j++) {   /* pixel par pixel */		
	sift1[j]=0.0;	
}
//on calcule l'histogramme de l'image 
   
 if(hist_ref)
	{
		while (fgets(cluster, TAILLE_MAX, hist_ref) != NULL)
		{
			
			in = atoi(cluster);
			sift1[in]++;
			nb_cluster++;
			
		}
			
	}
//fprintf(stderr,"apres fin de recup du hist de ref    ");
 // on normalise   
 for(i=0;i<256;i++)
{
	sift1[i]=sift1[in]/nb_cluster;
}



//on alloue la taille de memoire necessaire 
classement=malloc(sizeof(KEY)*nb_images);

int k=0;

/************La partie qui remplie la liste chainée avec pour chasue image son DE ******************/
char * mot;
//on recupere l'hist de l'image en question
mot=malloc(sizeof(char)*100);
for(j=0;j<nb_images; j++){

	if(fgets(ligne, TAILLE_MAX_LINE, hist)!=NULL){

		for(i=0;i<256;i++){

			mot = strtok(&ligne[k]," ");
			sift1[i]=atof(mot);
			k=k+9;
		}
	k=0;

	DE=distance_euclidienne_( sift1 ,sift);
	classement[j].k=j;
	classement[j].d=DE;
	//printf("\t image num : % d  a une dist de DE=%f\n",j,DE);
	}
  

}

// on prepare l'afffichage html

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
