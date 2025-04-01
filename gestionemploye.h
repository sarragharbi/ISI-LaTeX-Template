#ifndef GESTIONEMPLOYES_H
#define GESTIONEMPLOYES_H

#include "employe.h"
#include <QSqlQueryModel>

class GestionEmploye
{
public:
    static bool ajouterEmploye(const QString &nom, const QString &prenom, const QString &email, const QString &departement, double salaire, const QDate &dateEmbauche, const QString &typeContrat, int idEvenement, int idMagasin);
    static QSqlQueryModel* afficherEmployes();
    static bool modifierEmploye(int id, const QString &nom, const QString &prenom, const QString &email, const QString &departement, double salaire, const QDate &dateEmbauche, const QString &typeContrat, int idEvenement, int idMagasin);
    static bool supprimerEmploye(int id);
};

#endif // GESTIONEMPLOYES_H
