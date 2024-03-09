#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QTabWidget>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     int sd;
     QWidget *createCorpPage();
     QStackedWidget *stack;
      QWidget *createNewCorpPage();
       QWidget *createNewFacPage();
      QString array_corpuri;
      QString array_facultati;
       QWidget *createAdminCautaPage();
        QWidget *createAdminInsereazaPage();
         QWidget *createAdminStergePage();
    QWidget *createAdminFacPage();
     QWidget *createCorpFacPage();
     QWidget *createAdminCorpPage();
  private slots:
    void showUserPage();
   void showLogPage();
   void showStartPage();
   void showVizitMeniu();
    void showAdminMeniu();
   int verifCont();
   int existaSala();
   void cautaSala(QString s);
   void showCorpPage();
   void showFacPage();


private:
   // Ui::MainWindow *ui;

    QWidget *createStartPage();
   QWidget *createUserPage();
   QWidget *createLogPage();
   QWidget *createVizitMeniu();
   QWidget *createAdminMeniu();

    QString stusername;
    QString stpassword;
    QLabel *msg;
    QPushButton *b;
     bool passwordEditable;
     QString raspunsServer;
     QWidget *createFacPage();

     QString sali;
     QString corpBut;

};
#endif // MAINWINDOW_H

class fereastraSala :public QDialog{
    Q_OBJECT
public:
    fereastraSala(QWidget *parent = nullptr);
    //~fereastraSala();

    QTabWidget *tab;
   // private:
};
