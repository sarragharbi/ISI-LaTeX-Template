#include "GestionEmploye.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "GestionEmploye.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QSqlQueryModel())
{
    ui->setupUi(this);
    connect(ui->pushButton_ajouter, &QPushButton::clicked, this, &MainWindow::on_ajouterButton_clicked);
    connect(ui->pushButton_annuler, &QPushButton::clicked, this, &MainWindow::on_annulerButton_clicked);
    connect(ui->pushButton_supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimerButton_clicked);
    connect(ui->tableView_employes, &QTableView::clicked, this, &MainWindow::on_tableView_clicked);
    connect(ui->pushButton_modifier, &QPushButton::clicked, this, &MainWindow::on_modifierButton_clicked);
    afficherEmployes();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::on_ajouterButton_clicked() {
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QString departement = ui->lineEdit_depart->text();
    double salaire = ui->lineEdit_salaire->text().toDouble();
    QDate dateEmbauche = ui->dateEdit_date->date();
    QString typeContrat = ui->lineEdit_typecon->text();
    // On suppose qu'ID_EVENEMENT et ID_MAGASIN ne sont pas obligatoires
    int idEvenement = ui->lineEdit_idev->text().toInt();
    int idMagasin = ui->lineEdit_idmag->text().toInt();

    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || departement.isEmpty() || salaire == 0 || typeContrat.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    bool success = GestionEmploye::ajouterEmploye(nom, prenom, email, departement, salaire, dateEmbauche, typeContrat, idEvenement, idMagasin);

    if (success) {
        QMessageBox::information(this, "Succès", "L'employé a été ajouté.");
        ui->lineEdit_nom->clear();
        ui->lineEdit_prenom->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_depart->clear();
        ui->lineEdit_salaire->clear();
        ui->lineEdit_typecon->clear();
        ui->lineEdit_idev->clear();
        ui->lineEdit_idmag->clear();
        afficherEmployes();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout.");
    }
}

void MainWindow::on_annulerButton_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Quitter", "Êtes-vous sûr ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qApp->quit();
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    int row = index.row();
    id_selectionne = model->index(row, 0).data().toInt(); // ID_EMPLOYE
    ui->lineEdit_nom->setText(model->index(row, 1).data().toString()); // NOM
    ui->lineEdit_prenom->setText(model->index(row, 2).data().toString()); // PRENOM
    ui->lineEdit_email->setText(model->index(row, 3).data().toString()); // EMAIL
    ui->lineEdit_depart->setText(model->index(row, 4).data().toString()); // DEPARTEMENT
    ui->lineEdit_salaire->setText(model->index(row, 5).data().toString()); // SALAIRE
    ui->dateEdit_date->setDate(model->index(row, 6).data().toDate()); // DATE_EMBAUCHE
    ui->lineEdit_typecon->setText(model->index(row, 7).data().toString()); // TYPE_CONTRAT
    ui->lineEdit_idev->setText(model->index(row, 8).data().toString()); // ID_EVENEMENT
    ui->lineEdit_idmag->setText(model->index(row, 9).data().toString()); // ID_MAGASIN
}

void MainWindow::on_modifierButton_clicked() {
    if (id_selectionne == -1) {
        QMessageBox::warning(this, "Erreur", "Aucun employé sélectionné.");
        return;
    }

    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QString departement = ui->lineEdit_depart->text();
    double salaire = ui->lineEdit_salaire->text().toDouble();
    QDate dateEmbauche = ui->dateEdit_date->date();
    QString typeContrat = ui->lineEdit_typecon->text();
    int idEvenement = ui->lineEdit_idev->text().toInt();
    int idMagasin = ui->lineEdit_idmag->text().toInt();

    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || departement.isEmpty() || salaire == 0 || typeContrat.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis.");
        return;
    }

    bool success = GestionEmploye::modifierEmploye(id_selectionne, nom, prenom, email, departement, salaire, dateEmbauche, typeContrat, idEvenement, idMagasin);

    if (success) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès.");
        afficherEmployes();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification.");
    }
}

void MainWindow::on_supprimerButton_clicked() {
    if (id_selectionne == -1) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un employé à supprimer.");
        return;
    }

    bool success = GestionEmploye::supprimerEmploye(id_selectionne);

    if (success) {
        QMessageBox::information(this, "Succès", "Employé supprimé.");
        afficherEmployes();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression.");
    }
}

void MainWindow::afficherEmployes() {
    model = GestionEmploye::afficherEmployes();
    ui->tableView_employes->setModel(model);
}
