#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct passeport_s
{
    char planete[40];

    bool jedi;
}passeport_t;

typedef struct maillon_s
{
  int age;

  char* nom;

  passeport_t* pass;

  struct maillon_s* vdd;

}maillon_t;

typedef struct ensemble_s
{
  maillon_t* premierElement;
}ensemble_t;

ensemble_t* creer_liste(maillon_t* m);
maillon_t* creer_maillon(int a);
passeport_t* creer_passeport();
void ajouter_valeur_maillon_utilisateur(maillon_t* m);
void selection_modification_maillon_utilisateur(ensemble_t* liste);
maillon_t* rechercher_premier_maillon_par_valeur(ensemble_t* liste,int a);
void ajouter_append_maillon_a_la_liste(ensemble_t* liste, maillon_t* m);
void ajouter_prepend_maillon_a_la_liste(ensemble_t* liste, maillon_t* m);
void ajouter_nieme_maillon_a_la_liste(ensemble_t* liste,int pos, maillon_t* m);
void supprimer_append_maillon_a_la_liste(ensemble_t* liste);
void supprimer_prepend_maillon_a_la_liste(ensemble_t* liste);
void supprimer_nieme_maillon_a_la_liste(ensemble_t* liste,int pos);
int valeur_du_nieme_maillon(ensemble_t* liste, int nm_maillon);
void affichage_maillon(maillon_t* m);
void affichage_liste(ensemble_t* liste);
int main()
{

  maillon_t* nouveau = creer_maillon(1);
  ensemble_t* liste = creer_liste(nouveau);

  maillon_t* deuxieme = creer_maillon(1);
  deuxieme->age = 2;
  ajouter_append_maillon_a_la_liste(liste,deuxieme);



//liste->premierElement->vdd
  affichage_liste(liste);
  return EXIT_SUCCESS;

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
      printf("| Il/elle a un sabre laser |\n");
  }
  else
  {
      printf("| Il/elle n a pas de sabre laser |\n");
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
