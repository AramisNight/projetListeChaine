#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

typedef struct passeport_s
{
    char planete[40];

    bool jedi;
}passeport_t;

typedef struct maillon_s
{
  int age;
  int identification;
  char* nom;

  passeport_t* pass;
  struct maillon_s* vdd;

}maillon_t;

typedef struct ensemble_s
{
  maillon_t* premierElement;
}ensemble_t;


void menu(ensemble_t* liste);



void recherche_affichage(ensemble_t* liste);
void recherche_affichage_jedi(ensemble_t* liste, bool jedi);
void recherche_affichage_planete(ensemble_t* liste, char planete[40]);
void recherche_affichage_identification(ensemble_t* liste, int identification);
void recherche_affichage_nom(ensemble_t* liste, char* nom);
void recherche_affichage_age(ensemble_t* liste, int age);

void attribution_id(ensemble_t* liste,maillon_t* m);

ensemble_t* creer_liste(maillon_t* m);
ensemble_t* creer_liste_null();

maillon_t* creer_maillon(int a);
passeport_t* creer_passeport();
void supprimer_maillon(ensemble_t* liste);
void free_maillon(maillon_t* m);
int comparer_maillon(maillon_t* m1,maillon_t* m2);
void supprimer_maillon_par_id(ensemble_t* liste,maillon_t* m);
void ajout_fiche(ensemble_t* liste);
void ajouter_valeur_maillon_utilisateur(maillon_t* m);
void selection_modification_maillon_utilisateur(ensemble_t* liste);
void supprimer_maillon_tableau_id(ensemble_t* liste,int* id,int nbElements);

maillon_t* rechercher_premier_maillon_par_valeur(ensemble_t* liste,int a);


void ajouter_append_maillon_a_la_liste(ensemble_t* liste, maillon_t* m);
void ajouter_prepend_maillon_a_la_liste(ensemble_t* liste, maillon_t* m);
void ajouter_nieme_maillon_a_la_liste(ensemble_t* liste,int pos, maillon_t* m);

void copier_maillon(maillon_t* addToList,maillon_t* temporaire);
void supprimer_append_maillon_a_la_liste(ensemble_t* liste);
void supprimer_prepend_maillon_a_la_liste(ensemble_t* liste);
void supprimer_nieme_maillon_a_la_liste(ensemble_t* liste,int pos);


int valeur_du_nieme_maillon(ensemble_t* liste, int nm_maillon);


void affichage_maillon(maillon_t* m);
void affichage_liste(ensemble_t* liste);


ensemble_t* lecture_collection();

void ecriture_fichier(ensemble_t* m);
void select_fiches(ensemble_t* liste);
void affichage_maillons_par_id(ensemble_t* liste, int* id,int nbElements);
#endif // MAIN_H_INCLUDED
