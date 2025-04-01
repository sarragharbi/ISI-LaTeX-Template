#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouterButton_clicked();  // Add employee
    void on_annulerButton_clicked();  // Cancel operation
    void on_supprimerButton_clicked(); // Delete employee
    void on_modifierButton_clicked(); // Modify employee
    void on_tableView_clicked(const QModelIndex &index); // Table view click

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    int id_selectionne = -1;  // To track selected employee ID

    void afficherEmployes();  // Display employees instead of events
};

#endif // MAINWINDOW_H
