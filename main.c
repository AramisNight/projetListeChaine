#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"


int main()
{
  ensemble_t* liste = lecture_collection();
  affichage_liste(liste);
  ecriture_fichier(liste);
  return EXIT_SUCCESS;

}
ensemble_t* lecture_collection(){
  int ch;
  FILE *fp;
  fp = fopen("ident.txt", "r+");
  ensemble_t* maListe = creer_liste_null();
  maillon_t* temporaire = creer_maillon(1);
  int caractereActuel = 0;
  int compteurVirgule = 0;
  char tempo[100]= {0};
  char prevChar=' ';
  int indiceTempo = 0;
  if(fp == NULL)
  {
      printf("Error opening file\n");
      exit(EXIT_FAILURE);
  }

  printf("Reading contents of myfile.txt: \n\n");

  while( (ch=fgetc(fp)) != EOF )
  {
      if(ch != ',' && ch != '\n'){
          tempo[indiceTempo] = ch;
          indiceTempo = indiceTempo + 1;
          prevChar = ch;
      }
      else if(ch == '\n'){
          compteurVirgule = 0;
          char identific[10] ={0};
          strncpy(identific, tempo,indiceTempo);
          identific[indiceTempo] = '\0';
          memset(tempo, 0, 100);
          indiceTempo=0;
          int i = atoi(identific);
          temporaire->identification = i;
        //  printf("Fin de ligne : %d",temporaire->identification);
          maillon_t* addToList = creer_maillon(1);
          copier_maillon(addToList,temporaire);
        //  affichage_maillon(addToList);
          ajouter_prepend_maillon_a_la_liste(maListe,addToList);

      }
      else{
        //alors on arrive a un changement de ligne ou caracteristique du mec
        if(compteurVirgule == 0){
          strncpy(temporaire->pass->planete, tempo,indiceTempo);
          temporaire->pass->planete[indiceTempo] = '\0';
          memset(tempo, 0, 100);
          indiceTempo=0;
        //  printf("Passage a 0 de la virgule : %s \n",temporaire->pass->planete);


        }
        if(compteurVirgule == 1){

          if(prevChar =='n'){
            temporaire->pass->jedi = 0;
          }
          else{
            temporaire->pass->jedi = 1;
          }
          indiceTempo = 0;
    //        printf("Passage a 1 de la virgule  : %d \n",temporaire->pass->jedi);
        }
        if(compteurVirgule == 2){

          temporaire->nom = (char*)malloc(sizeof(indiceTempo));
          strncpy(temporaire->nom, tempo,indiceTempo);
          temporaire->nom[indiceTempo] = '\0';
          memset(tempo, 0, 100);
          indiceTempo=0;
  //        printf("Passage a 2 de la virgule : %s \n",temporaire->nom);

        }
        if(compteurVirgule == 3){
          //Tricks
          //Tricks
         char age[10] ={0};
         strncpy(age, tempo,indiceTempo);
         age[indiceTempo] = '\0';
         memset(tempo, 0, 100);
         indiceTempo=0;
         int i = atoi(age);
         temporaire->age = i;
  //       printf("Passage a 3 de la virgule  %d \n", temporaire->age);

        }
        if(ch == ','){

//printf("Je vois  de la virgule \n");
         compteurVirgule = compteurVirgule +1;
        }
      }

  }
  fclose(fp);
  return maListe;
}
void copier_maillon(maillon_t* addToList,maillon_t* temporaire){
  size_t destination_size = sizeof(temporaire->nom);
  addToList->nom = (char*)malloc(sizeof(destination_size));
  strncpy(addToList->nom,temporaire->nom, destination_size);
  addToList->nom[destination_size - 1] = '\0';
  addToList->age = temporaire->age;
  addToList->identification = temporaire->identification;
  addToList->pass = creer_passeport();
  strcpy(addToList->pass->planete,temporaire->pass->planete);
  addToList->pass->jedi = temporaire->pass->jedi;
}

ensemble_t* creer_liste_null(){
  ensemble_t* liste;
  liste = (ensemble_t *)malloc(sizeof(ensemble_t));
  liste->premierElement = NULL;
  return liste;
}
ensemble_t* creer_liste(maillon_t* m){
  ensemble_t* liste;
  liste = (ensemble_t *)malloc(sizeof(ensemble_t));
  liste->premierElement = m;
  return liste;
}
passeport_t* creer_passeport(){
  passeport_t* pass=NULL;
  pass=(passeport_t*)malloc(sizeof(passeport_t));
  return pass;
}
maillon_t* creer_maillon(int a){
  maillon_t* nouveau;
  nouveau = (maillon_t*)malloc(sizeof(maillon_t));
  nouveau->age = a;
  nouveau->pass=creer_passeport();
  nouveau->vdd = NULL;
  return nouveau;
}
void ajouter_valeur_maillon_utilisateur(maillon_t* m){
  int a = 0;
  printf("Veuillez rentrez une valeur pour l age \n");
  scanf("%d",&a);
  m->age = a;
  printf("La valeur du maillon est %d",m->age);
}
maillon_t* rechercher_premier_maillon_par_valeur(ensemble_t* liste, int a){
  maillon_t* temporaire =  liste->premierElement;
  while(temporaire->age != a){
    temporaire = temporaire->vdd;
  }
  return temporaire;
}

void selection_modification_maillon_utilisateur(ensemble_t* liste){
  int a=0;
  printf("Veuillez rentrer la valeur de l age du maillon que vous rechercher ?\n");
  scanf("%d",&a);
  maillon_t* temporaire = rechercher_premier_maillon_par_valeur(liste,a);
  ajouter_valeur_maillon_utilisateur(temporaire);
}
void ajouter_prepend_maillon_a_la_liste(ensemble_t* liste, maillon_t* m){
  m->vdd=liste->premierElement;
  liste->premierElement = m;
}
void ajouter_append_maillon_a_la_liste(ensemble_t* liste, maillon_t* m){
  maillon_t* temporaire =  liste->premierElement;
  while(temporaire->vdd != NULL){
    temporaire = temporaire->vdd;
  }
  temporaire->vdd = m;
}

void ajouter_nieme_maillon_a_la_liste(ensemble_t* liste,int pos, maillon_t* m){
  maillon_t* temporaire = liste->premierElement;
  for(int i=1; i<pos;i++){
    temporaire = temporaire->vdd;
  }
  m->vdd = temporaire;
  temporaire = liste->premierElement;
  for(int j=1; j<pos-1;j++){
  temporaire = temporaire->vdd;
  }
  temporaire->vdd = m;
}
void supprimer_nieme_maillon_a_la_liste(ensemble_t* liste,int pos){
  maillon_t* temporaire = liste->premierElement;
  for(int j=1; j<pos-1;j++){
  temporaire = temporaire->vdd;
  }
  temporaire->vdd = temporaire->vdd->vdd;
  temporaire = liste->premierElement;
  for(int i=1; i<pos;i++){
    temporaire = temporaire->vdd;
  }
  free(temporaire);
}
void supprimer_append_maillon_a_la_liste(ensemble_t* liste){
  maillon_t* temporaire = liste->premierElement;
  while(temporaire->vdd->vdd != NULL){
    temporaire = temporaire->vdd;
  }
  free(temporaire->vdd->vdd);
  temporaire->vdd = NULL;
}
void supprimer_prepend_maillon_a_la_liste(ensemble_t* liste){
  maillon_t* temporaire = liste->premierElement;
  liste->premierElement = liste->premierElement->vdd;
  free(temporaire);
}
int valeur_du_nieme_maillon(ensemble_t* liste, int nm_maillon){
    maillon_t* temporaire = liste->premierElement;
    int a=liste->premierElement->age;
    for(int i = 1; i<nm_maillon;i++){
      if(temporaire->vdd != NULL){
          temporaire = temporaire->vdd;
          a = temporaire->age;
      }
      else{
        a = -1;
        i = nm_maillon;
      }
    }
    return a;
}
void affichage_maillon(maillon_t* m){
  printf("-----------------------\n");
  printf("| %d |\n",m->age);
  printf("| %s |\n",m->nom);
  printf("| %s |\n",m->pass->planete);
  if(m->pass->jedi==true)
  {
      printf("| Il/elle est un jedi |\n");
  }
  else
  {
      printf("| Il/elle n'est pas un jedi |\n");
  }


  printf("-----------------------\n");
}
void affichage_liste(ensemble_t* liste){
  maillon_t* temporaire = liste->premierElement;
  while(temporaire->vdd !=NULL){
    affichage_maillon(temporaire);
    printf("| \n");
    printf("| \n");
    printf("V \n");
    temporaire = temporaire->vdd;
  }
    affichage_maillon(temporaire);
}


void ecriture_fichier(ensemble_t* m)
{
    maillon_t* temporaire = m->premierElement;

    FILE* fichier = NULL;
    fichier = fopen("ident.txt","rw+");

    if(fichier!=NULL)
    {
        while(temporaire->vdd !=NULL)
            {
                if(temporaire->pass->jedi == 1){
                  fprintf(fichier,"%s,o,%s,%d,%d\n",temporaire->pass->planete, temporaire->nom, temporaire->age, temporaire->identification);

                }
                else
                {
                  fprintf(fichier,"%s,n,%s,%d,%d\n",temporaire->pass->planete, temporaire->nom, temporaire->age, temporaire->identification);

                }
                temporaire = temporaire->vdd;
            }

        fclose(fichier);
    }
    else
    {
        printf("Erreur d ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

}
