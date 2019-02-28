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



ensemble_t* creer_liste(maillon_t* m);
ensemble_t* creer_liste_null();

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


ensemble_t* lecture_collection();

#endif // MAIN_H_INCLUDED
