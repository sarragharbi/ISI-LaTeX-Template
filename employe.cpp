#include "employe.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

// Constructeur de la classe Employe
Employe::Employe(int id, QString nom, QString prenom, QString email, QString departement,
                 double salaire, QDate dateEmbauche, QString typeContrat, int idEvenement, int idMagasin)
    : id_employe(id), nom(nom), prenom(prenom), email(email), departement(departement), salaire(salaire),
    date_embauche(dateEmbauche), type_contrat(typeContrat), id_evenement(idEvenement), id_magasin(idMagasin) {}

// Getters
int Employe::getIdEmploye() const { return id_employe; }
QString Employe::getNom() const { return nom; }
QString Employe::getPrenom() const { return prenom; }
QString Employe::getEmail() const { return email; }
QString Employe::getDepartement() const { return departement; }
double Employe::getSalaire() const { return salaire; }
QDate Employe::getDateEmbauche() const { return date_embauche; }
QString Employe::getTypeContrat() const { return type_contrat; }
int Employe::getIdEvenement() const { return id_evenement; }
int Employe::getIdMagasin() const { return id_magasin; }

// Setters
void Employe::setIdEmploye(int id) { id_employe = id; }
void Employe::setNom(QString nom) { this->nom = nom; }
void Employe::setPrenom(QString prenom) { this->prenom = prenom; }
void Employe::setEmail(QString email) { this->email = email; }
void Employe::setDepartement(QString departement) { this->departement = departement; }
void Employe::setSalaire(double salaire) { this->salaire = salaire; }
void Employe::setDateEmbauche(QDate date) { this->date_embauche = date; }
void Employe::setTypeContrat(QString typeContrat) { this->type_contrat = typeContrat; }
void Employe::setIdEvenement(int idEvenement) { this->id_evenement = idEvenement; }
void Employe::setIdMagasin(int idMagasin) { this->id_magasin = idMagasin; }

// Méthodes de gestion de la base de données

// Ajouter un employé
bool Employe::ajouterEmploye() {
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (NOM, PRENOM, EMAIL, DEPARTEMENT, SALAIRE, DATE_EMBAUCHE, TYPE_CONTRAT, ID_EVENEMENT, ID_MAGASIN) "
                  "VALUES (:nom, :prenom, :email, :departement, :salaire, :date_embauche, :type_contrat, :id_evenement, :id_magasin)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":departement", departement);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date_embauche", date_embauche);
    query.bindValue(":type_contrat", type_contrat);
    query.bindValue(":id_evenement", id_evenement);
    query.bindValue(":id_magasin", id_magasin);

    bool result = query.exec();
    if (!result) {
        qDebug() << "Erreur lors de l'ajout de l'employé : " << query.lastError().text();
    }
    return result;
}

// Afficher les employés
QSqlQueryModel* Employe::afficherEmployes() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");
    return model;
}

// Modifier un employé
bool Employe::modifierEmploye() {
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM = :nom, PRENOM = :prenom, EMAIL = :email, DEPARTEMENT = :departement, SALAIRE = :salaire, "
                  "DATE_EMBAUCHE = :date_embauche, TYPE_CONTRAT = :type_contrat, ID_EVENEMENT = :id_evenement, ID_MAGASIN = :id_magasin "
                  "WHERE ID = :id");
    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":departement", departement);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date_embauche", date_embauche);
    query.bindValue(":type_contrat", type_contrat);
    query.bindValue(":id_evenement", id_evenement);
    query.bindValue(":id_magasin", id_magasin);

    return query.exec();
}

// Supprimer un employé
bool Employe::supprimerEmploye(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE ID = :id");
    query.bindValue(":id", id);

    return query.exec();
}
