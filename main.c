#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"


int main()
{
  ensemble_t* liste = lecture_collection();
  menu(liste);
  return EXIT_SUCCESS;

}
void menu(ensemble_t* liste){
  int a = 0;
  int rep = 0;
  while(a != -1){
    printf("Que voulez vous faire ? \n");
    printf("1 - Voir la liste \n");
    printf("2 - Voir un maillon\n");
    printf("3 - Affichage Spécifique \n");
    printf("4 - Ajout d'une fiche \n");
    printf("5 - Suppr d'une fiche \n");
    printf("6 - Selection de fiches \n");
    printf("7 - Quitter \n");
    scanf("%d",&rep);
    if(rep == 1){
      affichage_liste(liste);
    }else if(rep == 2){
      affichage_maillon(liste->premierElement);
    }else if(rep ==3){
      recherche_affichage(liste);
    }else if(rep==4){
      ajout_fiche(liste);
    }else if(rep==5){
      supprimer_maillon(liste);
    }else if (rep==6){
      select_fiches(liste);
    }else if(rep == 7){
      printf("Merci d'avoir participé !\n");
      printf("Sauvegarde en cours !\n");
      ecriture_fichier(liste);
      free(liste);
      a= -1;
    }
  }
}
ensemble_t* lecture_collection(){
  int ch;
  FILE *fp;
  fp = fopen("ident.txt", "r+");
  ensemble_t* maListe = creer_liste_null();
  maillon_t* temporaire = creer_maillon(1);
  int compteurVirgule = 0;
  char tempo[100]= {0};
  char prevChar=' ';
  int indiceTempo = 0;
  char identific[100] ={0};
  char age[10] ={0};
  int atoi1 = 0;
  int atoi2 = 0;
  if(fp == NULL)
  {
      printf("Error opening file\n");
      exit(EXIT_FAILURE);
  }
  while( (ch=fgetc(fp)) != EOF )
  {
      if(ch != ',' && ch != '\n'){
          tempo[indiceTempo] = ch;
          indiceTempo = indiceTempo + 1;
          prevChar = ch;
      }
      else if(ch == '\n'){
          compteurVirgule = 0;
          strncpy(identific, tempo,indiceTempo);
          identific[indiceTempo] = '\0';
          memset(tempo, 0, 100);
          indiceTempo=0;
          atoi1 = atoi(identific);
          temporaire->identification = atoi1;
          maillon_t* addToList = creer_maillon(1);
          copier_maillon(addToList,temporaire);
          ajouter_prepend_maillon_a_la_liste(maListe,addToList);
      }
      else{
        if(compteurVirgule == 0){
          strncpy(temporaire->pass->planete, tempo,indiceTempo);
          temporaire->pass->planete[indiceTempo] = '\0';
          memset(tempo, 0, 100);
          indiceTempo=0;
        }
        if(compteurVirgule == 1){
          if(prevChar =='n'){
            temporaire->pass->jedi = 0;
          }
          else{
            temporaire->pass->jedi = 1;
          }
          indiceTempo = 0;
        }
        if(compteurVirgule == 2){
          temporaire->nom = (char*)malloc(sizeof(indiceTempo));
          strncpy(temporaire->nom, tempo,indiceTempo);
          temporaire->nom[indiceTempo] = '\0';
          memset(tempo, 0, 100);
          indiceTempo=0;
        }
        if(compteurVirgule == 3){
         strncpy(age, tempo,indiceTempo);
         age[indiceTempo] = '\0';
         memset(tempo, 0, 100);
         indiceTempo=0;
         atoi2 = atoi(age);
         temporaire->age = atoi2;
        }
        if(ch == ','){
         compteurVirgule = compteurVirgule +1;
        }
      }
  }
  fclose(fp);
  return maListe;
}

void copier_maillon(maillon_t* addToList,maillon_t* temporaire){
  size_t destination_size = strlen(temporaire->nom) +1;
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
void ajout_fiche(ensemble_t* liste){
    maillon_t* m = creer_maillon(1);
    int age,jedi,pos;
    char planete[40];
    char nom[100];
    int nbElements = 0;
    maillon_t* temporaire =  liste->premierElement;
    while(temporaire->vdd != NULL){
      temporaire = temporaire->vdd;
      nbElements = nbElements + 1;
    }
    //Pas plus de 100 fiches
    if(nbElements >=100){
      printf("The force isn't with you, you can't add more people !\n Delete it first");
    }else{
    printf("Rentrez son age :\n");
    scanf("%d",&age);
    printf("Rentrez son nom :\n");
    fflush(stdin);
    fgetc(stdin);
    fgets(nom, 100, stdin);
    strtok(nom,"\n");
    printf("Rentrez sa planète :\n");
    fflush(stdin);
    fgetc(stdin);
    fgets(planete, 100, stdin);
    strtok(planete,"\n");
    printf("Est-ce un jedi (1=oui) (0=non)? :\n");
    scanf("%d",&jedi);
    m->age = age;
    strcpy(m->nom,nom);
    strcpy(m->pass->planete,planete);
    m->pass->jedi = jedi;
    attribution_id(liste,m);
    printf("A quelle position voulez vous l'ajouter ? \n");
    affichage_liste(liste);
    scanf("%d",&pos);
    ajouter_nieme_maillon_a_la_liste(liste,pos,m);
    }
}
void attribution_id(ensemble_t* liste,maillon_t* m){
  maillon_t* temporaire = liste->premierElement;
  int idTemp = 0;
  int idTempNext = 0;
  int max = 0;
  while(temporaire !=NULL){
    idTemp = temporaire->identification;
    if(temporaire->vdd !=NULL){
        idTempNext = temporaire->vdd->identification;
    }else{
      idTempNext = 0;
    }
    if(idTemp > idTempNext){
      if(idTemp > max){
        max = idTemp;
      }
    }
    if(idTempNext > idTemp){
      if(idTempNext > max){
        max = idTempNext;
      }
    }
    temporaire = temporaire->vdd;
  }
  m->identification = max +1;
}

void ajouter_nieme_maillon_a_la_liste(ensemble_t* liste,int pos, maillon_t* m){
  maillon_t* temporaire = liste->premierElement;
  int i = 1;
  int j = 1;
  for(i=1; i<pos;i++){
    temporaire = temporaire->vdd;
  }
  m->vdd = temporaire;
  temporaire = liste->premierElement;
  for(j=1; j<pos-1;j++){
  temporaire = temporaire->vdd;
  }
  temporaire->vdd = m;
}
void supprimer_maillon(ensemble_t* liste){
  int suppr;
  int controle = 0;
  maillon_t* temporaire = liste->premierElement;
  affichage_liste(liste);
  printf("Veuillez rentrer le numéro d'identification à supprimer\n");
  scanf("%d",&suppr);
  while(temporaire != NULL){
    if(suppr == temporaire->identification)
    {
        supprimer_maillon_par_id(liste,temporaire);
        controle = 1;
    }
    temporaire = temporaire->vdd;
  }
  if(controle == 0){
    printf("Le numéro demandé n'existe pas , please retry \n");
    supprimer_maillon(liste);
  }
}
void free_maillon(maillon_t* m){
  free(m->pass);
  free(m->nom);
  free(m);
}
int comparer_maillon(maillon_t* m1,maillon_t* m2){
  if(m1->age == m2->age){
    if(m1->identification == m2->identification){
      if(strcmp(m1->nom,m2->nom) == 0){
        if(strcmp(m1->pass->planete,m2->pass->planete) == 0){
          if(m1->pass->jedi == m2->pass->jedi){
            return 1;
          }
        }
      }
    }
  }
  return 0;

}
void supprimer_maillon_par_id(ensemble_t* liste,maillon_t* m){
  maillon_t* temporaire = liste->premierElement;
  maillon_t* temporaire2 = NULL;
  while(temporaire !=NULL){
    if(comparer_maillon(temporaire->vdd,m) == 1){
       temporaire2 = temporaire->vdd;
       temporaire->vdd = temporaire->vdd->vdd;
       free_maillon(temporaire2);
    }
    temporaire = temporaire->vdd;
  }

}
void supprimer_nieme_maillon_a_la_liste(ensemble_t* liste,int pos){
  maillon_t* temporaire = liste->premierElement;
  int j=1;
  int i =1;
  for(j=1; j<pos-1;j++){
  temporaire = temporaire->vdd;
  }
  temporaire->vdd = temporaire->vdd->vdd;
  temporaire = liste->premierElement;
  for(i=1; i<pos;i++){
    temporaire = temporaire->vdd;
  }
  free_maillon(temporaire);
}
void supprimer_append_maillon_a_la_liste(ensemble_t* liste){
  maillon_t* temporaire = liste->premierElement;
  while(temporaire->vdd->vdd != NULL){
    temporaire = temporaire->vdd;
  }
  free_maillon(temporaire->vdd->vdd);
  temporaire->vdd = NULL;
}
void supprimer_prepend_maillon_a_la_liste(ensemble_t* liste){
  maillon_t* temporaire = liste->premierElement;
  liste->premierElement = liste->premierElement->vdd;
  free_maillon(temporaire);
}
int valeur_du_nieme_maillon(ensemble_t* liste, int nm_maillon){
    maillon_t* temporaire = liste->premierElement;
    int a=liste->premierElement->age;
    int i = 1;
    for(i = 1; i<nm_maillon;i++){
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
  printf("| Fiche n° %d |\n",m->identification);
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
    fichier = fopen("ident2.txt","w+");

    if(fichier!=NULL)
    {
        while(temporaire !=NULL)
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
void recherche_affichage_age(ensemble_t* liste, int age)
{
    maillon_t* temporaire = liste->premierElement;
    while(temporaire != NULL){
      if(age == temporaire->age)
      {
          affichage_maillon(temporaire);
      }
      temporaire = temporaire->vdd;
    }
}

void recherche_affichage_nom(ensemble_t* liste, char* nom)
{
  maillon_t* temporaire = liste->premierElement;
  strtok(nom, "\n");
  while(temporaire != NULL){
    if(strcmp(nom,temporaire->nom) == 0)
    {
        affichage_maillon(temporaire);
    }
    temporaire = temporaire->vdd;
  }
}

void recherche_affichage_identification(ensemble_t* liste, int identification)
{
  maillon_t* temporaire = liste->premierElement;
  while(temporaire != NULL){
    if(temporaire->identification == identification)
    {
        affichage_maillon(temporaire);
    }
    temporaire = temporaire->vdd;
  }
}

void recherche_affichage_planete(ensemble_t* liste, char planete[40])
{
  maillon_t* temporaire = liste->premierElement;
  strtok(planete, "\n");
  while(temporaire != NULL){
    if(strcmp(planete,temporaire->pass->planete) == 0)
    {
        affichage_maillon(temporaire);
    }
    temporaire = temporaire->vdd;
  }
}

void recherche_affichage_jedi(ensemble_t* liste, bool jedi)
{
  maillon_t* temporaire = liste->premierElement;
  while(temporaire != NULL){
    if(temporaire->pass->jedi == jedi)
    {
        affichage_maillon(temporaire);
    }
    temporaire = temporaire->vdd;
  }
}


void recherche_affichage(ensemble_t* liste)
{
    int choix;
    int jedi;
    char planete[40];
    char nom[100];
    int age;
    int identification;

    printf("Saisissez votre choix : ");

    printf(" 1 - Planete\n");
    printf(" 2 - Si jedi ou pas\n");
    printf(" 3 - Nom\n");
    printf(" 4 - Age\n");
    printf(" 5 - Identification\n");
    printf(" 6 - Quitter\n");

    scanf("%d",&choix);
    switch (choix)
    {
    case 1:
        printf("Veuillez saisir la planete a rechercher\n");
        fflush(stdin);
        fgetc(stdin);
        fgets(planete, 40, stdin);
        printf("-----------------------\n");
        recherche_affichage_planete(liste, planete);
        printf("-----------------------\n");

        break;

    case 2:
        printf("Veuillez saisir si les personnages sont un jedi ou pas (oui = 1 ou non = 0)\n");
        scanf("%d", &jedi);
        printf("-----------------------\n");
        recherche_affichage_jedi(liste, jedi);
        printf("-----------------------\n");

        break;

    case 3:
        printf("Veuillez saisir le nom a rechercher\n");
        fflush(stdin);
        fgetc(stdin);
        fgets(nom, 100, stdin);
        printf("-----------------------\n");
        recherche_affichage_nom(liste, nom);
        printf("-----------------------\n");

        break;

   case 4:
        printf("Veuillez saisir l age a rechercher\n");
        scanf("%d", &age);
        printf("-----------------------\n");
        recherche_affichage_age(liste, age);
        printf("-----------------------\n");

        break;

   case 5:
        printf("Veuillez saisir l identification a rechercher\n");
        scanf("%d", &identification);
        printf("-----------------------\n");
        recherche_affichage_identification(liste, identification);
        printf("-----------------------\n");

        break;

    case 6:
        exit(EXIT_FAILURE);
        default:
            printf("-----------------------\n");
            printf("||-Choix non valide-||\n");
            printf("-----------------------\n");

    }

}
void select_fiches(ensemble_t* liste){
  maillon_t* temporaire = liste->premierElement;
  int nbElements = 0;
  int* idElements;
  int selection = 1;
  int i=0;
  int parcoursElements = 0;
  while(temporaire != NULL){
    nbElements = nbElements +1;
    temporaire = temporaire->vdd;
  }
  idElements = (int*)malloc(sizeof(int));
  affichage_liste(liste);
  printf("Veuillez rentrer le numéro des fiches sélectionnées \n");
  while(selection != 0 && parcoursElements < nbElements){
    printf("Rentrer le numéro de la fiche ? \n");
    scanf("%d",&selection);
    idElements[parcoursElements] = selection;
    printf("Voulez vous selectionner d'autres fiches ? (1=Oui) (O = Non) \n");
    scanf("%d",&selection);
    parcoursElements = parcoursElements + 1;
  }
  printf("Vous avez selectionner les fiches suivantes : \n");
  for(i=0;i<nbElements;i++){
    printf(" %d  ",idElements[i]);
  }
  printf("\n Que voulez vous faire ? \n");
  printf("1 - Voir le détail des fiches selectionnées \n");
  printf("2 - Supprimer les fiches selectionnées \n");
  scanf("%d",&selection);
  if(selection == 2){
    supprimer_maillon_tableau_id(liste,idElements,nbElements);
  }else{
    affichage_maillons_par_id(liste,idElements,nbElements);
  }
}
void supprimer_maillon_tableau_id(ensemble_t* liste,int* id,int nbElements){
  maillon_t* temporaire = liste->premierElement;
  int i;
  while(temporaire != NULL){
    for(i=0;i<nbElements;i++){
      if(temporaire->identification == id[i]){
        supprimer_maillon_par_id(liste,temporaire);
        i = nbElements;
      }
    }
    temporaire = temporaire->vdd;
  }
  printf("Voici la nouvelle liste : \n");
  affichage_liste(liste);
}
void affichage_maillons_par_id(ensemble_t* liste, int* id,int nbElements){
  maillon_t* temporaire = liste->premierElement;
  int i;
  while(temporaire != NULL){
    for(i=0;i<nbElements;i++){
      if(temporaire->identification == id[i]){
        affichage_maillon(temporaire);
        i = nbElements;
      }
    }
    temporaire = temporaire->vdd;
  }
}
