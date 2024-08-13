#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
//////////////////////////
//Liste de structures
typedef struct noeud {
double info ;
struct noeud * suiv ;
} noeud ;
///////////////////////
typedef struct col
{
char nom[100] ;
noeud* liste ;
}
colonne ;


//////////////////////////
#define Colomne  19
//affiche le maximum de la liste
double maximum(noeud* liste){
    noeud *suivant;
	suivant=liste->suiv;
    	double max;
    	max=suivant->info;
	while(suivant!=NULL){
		if (suivant->info>max){
			max=suivant->info;}
		 suivant=suivant->suiv;}
	return max;}
//affiche le minimul de la liste
double minimum(noeud* listen){
	noeud *suivant;
    	suivant=listen->suiv;
    	double min;
    	min=suivant->info;
	while(suivant!=NULL){
		if (suivant->info<min){
			min=suivant->info;}
			suivant=suivant->suiv;}
	return min;
	}

//ajoute un noeud à la liste chainé
noeud* ajout_debut_chaine(noeud* liste,double nouvelle_info){
	noeud* nouveau;
	nouveau =(noeud *)malloc(sizeof(noeud));
	nouveau->info=nouvelle_info;
	nouveau->suiv = liste;
	return nouveau;}
//affiche les infos de la liste
void afficher_liste( noeud* nouveau , int n ){
	printf("{") ;
	while( nouveau != NULL && n > 0 ){
		printf(" %f ",nouveau->info) ;
		nouveau = nouveau->suiv ;
		n-- ;
		}
	if( nouveau == NULL ) printf("}\n") ;
	else printf("...\n") ;
}
//longeur de la liste pour les fionctions statistique
int taille_liste( noeud* suiv ){
	int colonne = 0 ;
	while ( suiv != NULL ){
		colonne++ ;
		suiv = suiv->suiv ;
		}
	return colonne ;
}
//inverse la liste
noeud* inverse_mirroir( noeud* suiv ){
	noeud* colonne = NULL ;
	while (suiv != NULL)
		{
		colonne = ajout_debut_chaine(colonne,suiv->info) ;
		suiv = suiv->suiv ;
		}
	return colonne ;
}
//définie l'ordre et fusionne les 2 liste 
noeud* fusion_liste( noeud* nouveau1 , noeud* nouveau2 ){
	noeud* colonne = NULL ;
	while ( nouveau1 != NULL && nouveau2 != NULL ){
		if ( nouveau1->info< nouveau2->info){ // test de l'inégalité , modifier si nécessaire{
			colonne = ajout_debut_chaine(colonne,nouveau1->info) ;
			nouveau1 = nouveau1->suiv ;
			}
		else{
			colonne = ajout_debut_chaine(colonne,nouveau2->info) ;
			nouveau2 = nouveau2->suiv ;
			}
		
	while ( nouveau1 != NULL || nouveau2 != NULL ){
	if ( nouveau1 != NULL ){
		colonne = ajout_debut_chaine(colonne,nouveau1->info) ;
		nouveau1 = nouveau1->suiv ;
		}
	else{
		colonne = ajout_debut_chaine(colonne,nouveau2->info) ;
		nouveau2 = nouveau2->suiv ;
		}
	}
return inverse_mirroir(colonne) ;
}
}


//renvoie le tri fusion d'une liste chainee ( pour définir l'ordre voir fusion_liste ). En O( n.log n )
noeud* tri_fusion( noeud* suivant ){
	noeud* list1 = NULL ;
	noeud* list2 = NULL ;
	int i = 0 ;
	if ( suivant == NULL ) 
		return NULL ;
	else if ( suivant->suiv == NULL ) 
		return suivant ;
	else
		{
		while ( suivant != NULL )
			{
			if ( i == 0 ){
				list1 = ajout_debut_chaine(list1,suivant->info) ;
				suivant = suivant->suiv ;
				i++ ;
				}
			else{
				list2 = ajout_debut_chaine(list2,suivant->info) ;
				suivant = suivant->suiv ;
				i = 0 ;
				}
			}
		return fusion_liste( tri_fusion(list1) , tri_fusion(list2) ) ;
		}

}
//définie la médiane
double mediane( noeud* suiv ){
	int len = taille_liste(suiv) ;
	suiv = tri_fusion(suiv) ;
	if (len>0){
		int mid = len/2 ;
		for ( int i = 0 ; i<mid ; i++ ){
			suiv = suiv->suiv;
		}
	return suiv->info;
	}

}


//donne la valeur du premier quartile
double quartiles1( noeud* suiv ){
	int len = taille_liste(suiv) ;
	suiv = tri_fusion(suiv) ;
	if (len>0){
		int mid = len/4 ;
		for ( int i = 0 ; i<mid ; i++ ){
			suiv = suiv->suiv;
		}
	return suiv->info;
	}

}
//donne la valuer du deuxieme quartiles
double quartiles3( noeud* suivant ){
	double suiv;
	int len = taille_liste(suivant) ;
	suivant = tri_fusion(suivant) ;
	if (len>0){
		int mid = 3*len/4 ;
		for ( int i = 0 ; i<mid ; i++ ){
			suiv = suivant->info;
		}
	return suiv ;
	}

}




/* renvoie la concatenation de deux listes chainees pour tenter de régler le rpobleme de segmentation fault
noeud* concat_list( noeud* suiv_debut , noeud* suiv_fin ){
	suiv_debut = inverse_mirroir(suiv_debut) ;
	while( suiv_debut != NULL ){
		suiv_fin = ajout_debut_chaine(suiv_fin,suiv_debut->info) ;
		suiv_debut = suiv_debut->suiv ;
	}
return suiv_fin ;
}
*/
//donne la moyenne de la liste

double moyenne(noeud* liste){
    double s=0;
    double n=0;
    noeud *suivant;
    suivant=liste->suiv;
    while(suivant!=NULL){
    	s=s+suivant->info;
    	suivant=suivant->suiv;
    	n++;}
    	return s/n;}
//donne l'ecart type de la liste 

double ecart_type(noeud* liste){
	double s=0;
	double m=0;
	m= moyenne(liste);
	double n=0;
	noeud *suivant;
    	suivant=liste->suiv;
	while(suivant!=NULL){
		s=s+pow(((suivant->info)-m),2);
		suivant=suivant->suiv;
		n=n+1;}
	return sqrt(s/n);}
	
//Stocke les valeur des fichiers dans des listes chainées

colonne* Stockage_valeur( char* fichier ){
char nom[100] ;
int j ;
FILE* file = fopen(fichier,"r") ;
colonne* colonne = (colonne*) malloc(19*sizeof(colonne)) ; 
for( int i = 1 ; i<=25 ; i++ ) // on parcourt la 1ere ligne et initialise les listes
    {
    fscanf(file,"%s ",nom) ; // les noms des colonnes sont au début du .csv
    if ( i > 6 ){ // condition qui donne les colonnes utiles uniquement ( Cols 7 à 25 -> i>6 )
        colonne[j].liste = NULL ;
        strcpy(colonne[j].nom,nom) ;
        j++ ;
        }
    }
float t ;
char poubelle ;
int compteur ; 
do
    {
    j = 0 ;
    for( int i = 1 ; i<=25; i++ ) // remplissage des listes
        {
        if ( i != 5 ) compteur = fscanf(file,"%f ",&t) ; // STAGE ( col 5 ) fait buguer
        else compteur = fscanf(file,"%c ",&poubelle) ;
        if ( i > 6 && compteur > 0 ){ // condition qui donne les colonnes utiles uniquement ( Cols 7 à 25 -> i>6 )
            
            colonne[j].liste = ajout_debut_chaine(colonne[j].liste,t) ;
            j++ ;
            }
        }
    } 
while( compteur > 0 ) ;
fclose(file) ;
return colonne ;
}


// affiche un apercu des données. 
void afficher_info_limite( colonne* tableau[19] , int n_max ){
	for ( int i = 0 ; i<19; i++ ){
    	printf("Colonne %d ( %s ) : ",i+1,tableau[i]->nom) ;
    	afficher_liste(tableau[i]->liste,n_max) ;
    }
}

////////////////////////////

void supprime_valeur(noeud* liste, int k, double sigma){

noeud* prec=NULL;
noeud* courant=liste->suiv;
while(courant!=NULL){
if((courant->info>(k*sigma))||(courant->info<(-1*k*sigma)))
{prec->suiv=courant->suiv;}
prec = courant;
courant=courant->suiv;
}}
//////////////////////////
noeud** histogramme(noeud* liste){
		noeud* suivant;
		suivant = liste->suiv;
		noeud* suivant1;
		noeud* nbr=NULL;
		noeud* val=NULL;
		suivant1 = suivant->suiv;
		while(suivant1 !=NULL){
			double s=0;
			while(suivant->info==suivant1->info){
			s+=1;}
			ajout_debut_chaine(nbr,s);
			ajout_debut_chaine(val,suivant->info);
		noeud* tableau[2]={val, nbr};
	return tableau;
		}
	}


//////////////////////////

//////////////////////////

colonne* main(){
	
    colonne* liste1=NULL;
	liste1=( colonne *) malloc(sizeof(colonne));
	colonne* liste2 =NULL;
	liste2=( colonne *) malloc(sizeof(colonne));
	colonne* liste3 =NULL;
	liste3=( colonne *) malloc(sizeof(colonne));
	colonne* liste4 =NULL;
	liste4=( colonne *) malloc(sizeof(colonne));
	colonne* liste5 =NULL;
	liste5=( colonne *) malloc(sizeof(colonne));
	colonne* liste6 =NULL;
	liste6=( colonne *) malloc(sizeof(colonne));
	colonne* liste7 =NULL;
	liste7=( colonne *) malloc(sizeof(colonne));
	colonne* liste8 =NULL;
	liste8=( colonne *) malloc(sizeof(colonne));
	colonne* liste9 =NULL;
	liste9=( colonne *) malloc(sizeof(colonne));
	colonne* liste10 =NULL;	
	liste10=( colonne *) malloc(sizeof(colonne));					//initialisation des 19 listes
	colonne* liste11 =NULL;
	liste11=( colonne *) malloc(sizeof(colonne));
	colonne* liste12 =NULL;
	liste12=( colonne *) malloc(sizeof(colonne));
	colonne* liste13 =NULL;
	liste13=( colonne *) malloc(sizeof(colonne));
	colonne* liste14 =NULL;
	liste14=( colonne *) malloc(sizeof(colonne));
	colonne* liste15 =NULL;
	liste15=( colonne *) malloc(sizeof(colonne));
	colonne* liste16 =NULL;
	liste16=( colonne *) malloc(sizeof(colonne));
	colonne* liste17 =NULL;
	liste17=( colonne *) malloc(sizeof(colonne));
	colonne* liste18 =NULL;
	liste18=( colonne *) malloc(sizeof(colonne));
	colonne* liste19 =NULL;
	liste19=( colonne *) malloc(sizeof(colonne));
	colonne* tableau[19]={liste1, liste2, liste3, liste4, liste5, liste6, liste7, liste8, liste9, liste10, liste11, liste12, liste13, liste14, liste15, liste16, liste17, liste18, liste19};
	/*for(int i=0;i<19;i++)
	tableau[i]=( colonne *) malloc(sizeof(colonne));*/
	
	
	
	for(int i=0;i<19;i++){
	tableau[i]->liste=Stockage_valeur("CMP-training-000.csv")[i].liste;
	/*tableau[i]->liste=Stockage_valeur("CMP-training-001.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-002.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-003.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-004.csv")[i].liste;		
	tableau[i]->liste=Stockage_valeur("CMP-training-005.csv")[i].liste;		
	tableau[i]->liste=Stockage_valeur("CMP-training-006.csv")[i].liste;		
	tableau[i]->liste=Stockage_valeur("CMP-training-007.csv")[i].liste;		
	tableau[i]->liste=Stockage_valeur("CMP-training-008.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-009.csv")[i].liste;	
	tableau[i]->liste=Stockage_valeur("CMP-training-010.csv")[i].liste;	
	tableau[i]->liste=Stockage_valeur("CMP-training-011.csv")[i].liste;	
	tableau[i]->liste=Stockage_valeur("CMP-training-012.csv")[i].liste;	
	tableau[i]->liste=Stockage_valeur("CMP-training-013.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-014.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-015.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-016.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-017.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-018.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-019.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-020.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-021.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-022.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-023.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-024.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-025.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-026.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-027.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-029.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-030.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-031.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-032.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-033.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-034.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-035.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-036.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-037.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-038.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-039.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-040.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-041.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-042.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-043.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-044.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-045.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-046.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-047.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-048.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-049.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-050.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-051.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-052.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-053.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-054.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-055.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-056.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-057.csv")[i].liste;
	tableau[i]->liste=Stockage_valeur("CMP-training-058.csv")[i].liste;
	}*/
	
	}
	
	for(int i=0;i<19;i++){
	tableau[i]->liste=tri_fusion(tableau[i]->liste);}
	double moy;
	double min;
	double max;
	double et;
	double med;
	double Q1;
	double Q3;
	/*FILE* files;
	files=fopen("texte.txt","w+");*/
	//fprintf(files,"MOYENNE\tMINIMUM\tMAXIMUM\tECART-TYPE\tMEDIANE\tQUARTILE1\tQUARTILE2")
	//for(int i=0;i<19;i++){
		//moy=moyenne(tableau[i]->liste);
	//min=minimum(tableau[i]->liste);
		/*max=maximum(tableau[i]->liste);
		et=ecart_type(tableau[i]->liste);
		med=mediane(tableau[i]->liste);
		Q1=quartiles1(tableau[i]->liste);
		Q3=quartiles3(tableau[i]->liste);*/
		//fprintf(files,"%.6lf\t|\t%.6lf\t|\t%.6lf\t|\t%.6lf\t|\t%.6lf\t|\t%.6lf\t|\t%.6lf\n",moy,min,max,et,med,Q1,Q3);
	
	
	afficher_info_limite(tableau,100);
	printf("cc");
	return(liste1);
	}




	/*
	//Q2//
	double k;
	printf("Donner la valeur de k");
	scanf("%lf",k);
	for(int i=0;i<19;i++){
	supprime_valeur(tableau[i])
	}
	//Q3//
	for(int i=0;i<19;i++){
		histogramme(liste[i]);
	}
	tri_fusion(nbr);
	tri_fusion(val);
	while(suivant1!=NULL){
	noeud* prec=NULL;
	while(suivant->info==suivant1->info){
		{prec->suiv=suivant->suiv;}
		prec = suivant;
		suivant=suivant->suiv;
	
	}
	}
	


	return(0);} */

