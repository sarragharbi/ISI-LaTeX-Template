#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "employe.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;

    // Vérifier si la connexion à la base fonctionne
    bool test = c.createconnect();
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database Status"),
                                 QObject::tr("Connection successful!"), QMessageBox::Ok);
        qDebug() << " Connexion à la base de données réussie.";
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Connection failed! Check your settings."), QMessageBox::Cancel);
        qDebug() << " Échec de la connexion à la base de données.";
        return -1;  // Quitter si la connexion échoue
    }

    // Affichage de la fenêtre principale
    MainWindow w;
    w.show();
    w.showFullScreen();


    return a.exec();
}
