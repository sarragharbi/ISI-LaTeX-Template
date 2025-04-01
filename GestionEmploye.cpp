#include "GestionEmploye.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

bool GestionEmploye::ajouterEmploye(const QString &nom, const QString &prenom, const QString &email,
                                    const QString &departement, double salaire, const QDate &dateEmbauche,
                                    const QString &typeContrat, int idEvenement, int idMagasin) {
    // Vérification du salaire
    if (salaire <= 0) {
        QMessageBox::warning(nullptr, "Erreur", "Le salaire doit être supérieur à zéro.");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (NOM, PRENOM, EMAIL, DEPARTEMENT, SALAIRE, DATE_EMBAUCHE, TYPE_CONTRAT, ID_EVENEMENT, ID_MAGASIN) "
                  "VALUES (:nom, :prenom, :email, :departement, :salaire, :date_embauche, :type_contrat, :id_evenement, :id_magasin)");

    // Liaison des paramètres
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":departement", departement);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date_embauche", dateEmbauche);
    query.bindValue(":type_contrat", typeContrat);
    query.bindValue(":id_evenement", idEvenement);
    query.bindValue(":id_magasin", idMagasin);

    // Exécution de la requête
    if (!query.exec()) {
        // Affichage de l'erreur SQL si la requête échoue
        qDebug() << "Erreur SQL lors de l'ajout d'employé : " << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de l'ajout de l'employé : " + query.lastError().text());
        return false;
    }

    return true;
}


bool GestionEmploye::modifierEmploye(int id, const QString &nom, const QString &prenom, const QString &email,
                                     const QString &departement, double salaire, const QDate &dateEmbauche,
                                     const QString &typeContrat, int idEvenement, int idMagasin) {
    if (salaire <= 0) {
        QMessageBox::warning(nullptr, "Erreur", "Le salaire doit être supérieur à zéro.");
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM = :nom, PRENOM = :prenom, EMAIL = :email, DEPARTEMENT = :departement, SALAIRE = :salaire, "
                  "DATE_EMBAUCHE = :date_embauche, TYPE_CONTRAT = :type_contrat, ID_EVENEMENT = :id_evenement, ID_MAGASIN = :id_magasin "
                  "WHERE ID = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":departement", departement);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date_embauche", dateEmbauche);
    query.bindValue(":type_contrat", typeContrat);
    query.bindValue(":id_evenement", idEvenement);
    query.bindValue(":id_magasin", idMagasin);

    return query.exec();
}

QSqlQueryModel* GestionEmploye::afficherEmployes() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");
    return model;
}

bool GestionEmploye::supprimerEmploye(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE ID = :id");
    query.bindValue(":id", id);

    return query.exec();
}
