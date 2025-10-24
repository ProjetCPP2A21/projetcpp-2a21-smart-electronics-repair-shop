#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

class fournisseur
{
public:
    fournisseur();
private:
    fournisseur creer_fournisseur(); //CRUD S
    void ajouter_fournisseur();
    void supprimer_fournisseur();
    void recherche_id_fournisseur(); //CRUD E
    void tri_nom_ent_fournisseur();
    void exporter_f_enpdf();
    void  statistique_f();
    void m_inonvant();

};

#endif // FOURNISSEUR_H
