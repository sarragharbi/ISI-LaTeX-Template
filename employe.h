#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Employe
{
public:
    // Constructeur
    Employe(int id = 0, QString nom = "", QString prenom = "", QString email = "",
            QString departement = "", double salaire = 0.0, QDate dateEmbauche = QDate::currentDate(),
            QString typeContrat = "", int idEvenement = 0, int idMagasin = 0);

    // Getters
    int getIdEmploye() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getEmail() const;
    QString getDepartement() const;
    double getSalaire() const;
    QDate getDateEmbauche() const;
    QString getTypeContrat() const;
    int getIdEvenement() const;
    int getIdMagasin() const;

    // Setters
    void setIdEmploye(int id);
    void setNom(QString nom);
    void setPrenom(QString prenom);
    void setEmail(QString email);
    void setDepartement(QString departement);
    void setSalaire(double salaire);
    void setDateEmbauche(QDate date);
    void setTypeContrat(QString typeContrat);
    void setIdEvenement(int idEvenement);
    void setIdMagasin(int idMagasin);

    // Méthodes de gestion de la base de données
    bool ajouterEmploye();
    QSqlQueryModel* afficherEmployes();
    bool modifierEmploye();
    bool supprimerEmploye(int id);

private:
    int id_employe;
    QString nom;
    QString prenom;
    QString email;
    QString departement;
    double salaire;
    QDate date_embauche;
    QString type_contrat;
    int id_evenement;
    int id_magasin;
};

#endif // EMPLOYE_H
