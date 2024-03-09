#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QtWidgets>
#include <QPixmap>
#include <QString>
#include <QDialog>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "conectivitate.hpp"
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,
      stack(new QStackedWidget(this))
{

    QWidget *start=createStartPage();//0
    stack->addWidget(start);

    QWidget *user=createUserPage();//1
    stack->addWidget(user);


    QWidget *log=createLogPage();//2
    stack->addWidget(log);
    QWidget *admin=createAdminMeniu();//3
    stack->addWidget(admin);

    QWidget *vizit=createVizitMeniu();//4
    stack->addWidget(vizit);

    QWidget *fac=createFacPage();//5
    stack->addWidget(fac);
    QWidget *corp=createCorpPage();//6
    stack->addWidget(corp);

    QWidget *i=createAdminInsereazaPage();//7
    stack->addWidget(i);

    QWidget *s=createAdminStergePage();//8
    stack->addWidget(s);

    QWidget *c=createAdminCautaPage();//9
    stack->addWidget(c);

    QWidget *nf=createNewCorpPage();//10
    stack->addWidget(nf);



  // QWidget *crearecorpnou=createNewFacPage();//11
  //  stack->addWidget(crearecorpnou);


    stack->setCurrentIndex(0);

    setCentralWidget(stack);
}

MainWindow::~MainWindow()
{

}



QWidget *MainWindow::createStartPage(){

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text=new QLabel ("                       BINE ATI VENIT LA \nUNIVERSITATEA ALEXANDRU IOAN CUZA\n                                DIN IASI",page);
    text->setStyleSheet("color: white; font-size:50px; font-family: Times New Roman; font-weight: bold;");
    text->setGeometry(225,300,1300,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(250,250);
    label->setPixmap(imagee);
    label->move(100,50);

    QPushButton *buton=new QPushButton("INCEPE  >>",page);
    buton->setGeometry(1200,700,200,90);
    buton->setStyleSheet("font-size: 30px ; color: darkblue; font-weight: bold;");

    connect(buton,&QPushButton::clicked,this,&MainWindow::showUserPage);
    return page;
}



QWidget *MainWindow::createUserPage(){

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");



    QLabel *text=new QLabel (" CONTINUATI CA ....",page);
    text->setStyleSheet("color: white; font-size: 80px; font-family: Times New Roman; font-weight: bold;");
    text->setGeometry(370,100,900,300);


    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
     butonBack->setVisible(true);
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
       showStartPage();
    });


    QPushButton *buton1=new QPushButton("ADMINISTRATOR",page);
    buton1->setGeometry(420,400,300,100);
    buton1->setStyleSheet(" background-color: white;border: 4px solid grey; font-size: 30px ; color: darkblue; font-weight: bold;");
    QPushButton *buton2=new QPushButton("VIZITATOR",page);
    buton2->setGeometry(820,400,300,100);
    buton2->setStyleSheet(" background-color: white;border: 4px solid grey; font-size: 30px ; color: darkblue; font-weight: bold;");
    connect(buton2,&QPushButton::clicked,this,[=](){
         butonBack->setVisible(false);
         int r=2;
        write(MainWindow::sd,&r,sizeof(int));
        read(MainWindow::sd,&r,sizeof(r));
        showVizitMeniu();
    });
    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    connect(buton1,&QPushButton::clicked,this,[=](){
          butonBack->setVisible(false);
        int r=1;
       write(MainWindow::sd,&r,sizeof(int));

       showLogPage();
    });


    return page;
}

QWidget *MainWindow::createLogPage(){

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text=new QLabel ("Admin Login",page);
    text->setStyleSheet("color: white; font-size: 60px; font-family: Times New Roman; ");
    text->setGeometry(600,10,900,300);


    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *usl=new QLabel("Username:",page);
    QLabel *psl=new QLabel("Password:",page);
    usl->setStyleSheet("color:white; font-size: 30px;");
    psl->setStyleSheet("color:white; font-size: 30px;");
    usl->setGeometry(400,300,200,60);
    psl->setGeometry(400,380,200,60);

    QLineEdit *username =new QLineEdit (page);
    username->setPlaceholderText("Enter your username");
    username->setGeometry(600,280,400,60);

    QLineEdit *password =new QLineEdit (page);
    password->setPlaceholderText("Enter your username");
    password->setGeometry(600,380,400,60);
    password->setEchoMode(QLineEdit::Password);

    QPushButton *but=new QPushButton("LOG IN ",page);
    but->setGeometry(600,630,400,60);
    but->setStyleSheet(" background-color: white;border: 4px solid grey; font-size: 30px ; color: darkblue; font-weight: bold;");
      msg=new QLabel("",page);
    msg->setGeometry(600,800,100,50);
     msg->setStyleSheet("color:green; font-size: 25px;");

    b=new QPushButton("",page);
     b->setGeometry(1250,780,0,0);

     username->clear();
     password->setEnabled(true);
      msg->clear();
      b->setVisible(false);
    connect(but,&QPushButton::clicked,this,[=]()
    {
        b->setVisible(false);
        stusername=username->text();
        stpassword=password->text();
         QString rasp=stusername+" "+stpassword;
         QByteArray ba=rasp.toUtf8();
          char*raspp=ba.data();
          if(!ba.isEmpty())
          {
               raspp[strlen(raspp)]='\0';
                printf("\n%s_\n",raspp);
          }


        if(stusername.isEmpty())
        {
             msg->setText("Introduceti un username.");
            msg->setStyleSheet("font-family: Times New Roman ;color:red; font-size: 30px ; font-weight: bold;");
            msg->setGeometry(600,500,400,50);
        }
        else
        {
               int lungime=strlen(raspp);

                write(sd,&lungime,sizeof(int));
                write(sd,raspp,lungime);

                memset(raspp,0,strlen(raspp));
                read(sd,raspp,2);
                raspp[2]='\0';
             if(strstr(raspp,"DA"))
            {
                b->setVisible(true);
                b->setText("NEXT  >>");
                b->setGeometry(1250,780,200,70);

                b->setStyleSheet(" background-color: green;border: 2px solid white; font-family: Times New Roman ; font-size: 30px ; color: white; font-weight: bold;");
                connect(b,&QPushButton::clicked,this,[=]()
                {
                   username->clear();
                   password->clear();
                   msg->clear();
                   b->setVisible(false);
                  showAdminMeniu();
                });

                QString m = "Bine ati venit, " + stusername + " !";
                msg->setText(m);
                msg->setStyleSheet("color:green;font-family: Times New Roman ; font-size: 30px ; font-weight: bold;");
                msg->setGeometry(600,500,300,50);

            }
            else
            {
                msg->setText("Utilizator negasit!");
                msg->setStyleSheet("color:red; font-family: Times New Roman ;font-size: 30px ; font-weight: bold;");
                msg->setGeometry(600,500,300,50);
            }
        }

    });



    return page;

}

QWidget *MainWindow::createAdminMeniu(){

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("MENIU ADMINISTRATOR",page);
    text->setStyleSheet("color: white; font-size: 60px; font-family: Times New Roman; ");
    text->setGeometry(450,10,900,300);


    QPushButton *cauta=new QPushButton("CAUTA DATE",page);
    cauta->setGeometry(670,300,200,80);
    cauta->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");
    connect(cauta,&QPushButton::clicked,this,[=](){

        stack->setCurrentIndex(9);
    });

    QPushButton *insert=new QPushButton("INSEREAZA DATE",page);
    insert->setGeometry(670,400,200,80);
    insert->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");
    connect(insert,&QPushButton::clicked,this,[=](){

        stack->setCurrentIndex(7);
    });


    QPushButton *sterge=new QPushButton("STERGE DATE",page);
    sterge->setGeometry(670,500,200,80);
    sterge->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");
    connect(sterge,&QPushButton::clicked,this,[=](){

        stack->setCurrentIndex(8);
    });



    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
       int cod=-1;
       write(sd,&cod,sizeof(int));
       exit(EXIT_SUCCESS);
    });
    return page;
}


QString raspuns_de_la_serverr;
QWidget *MainWindow::createAdminCautaPage()
{
    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);


    QLabel *text=new QLabel ("CAUTA DATE",page);
    text->setStyleSheet("color: white; font-size: 35px; font-family: Times New Roman; ");
    text->setGeometry(650,10,900,80);


    //creare meniu
    //BUTON CAUTA SALA
    QLineEdit *cauta =new QLineEdit (page);
     cauta->setGeometry(900,200,0,0);
     QPushButton *cb=new QPushButton("CAUTA",page);
     cb->setGeometry(900,200,0,0);

    QPushButton *sala=new QPushButton("CAUTA SALA",page);
    sala->setGeometry(650,200,200,80);
    sala->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");
      QLabel *mm=new QLabel (".",page);
      cauta->clear();
      mm->clear();
      cb->setVisible(false);
      cauta->setVisible(false);
    connect(sala,&QPushButton::clicked,this,[=]()
    {

        cb->setVisible(true);
        cauta->setVisible(true);
        cauta->setPlaceholderText("Enter a room.");
        cauta->setGeometry(900,200,200,35);
        cb->setGeometry(900,250,100,25);
        cb->setStyleSheet("background-color: grey; color: black; border: 2px solid black;");


    });
    connect(cb,&QPushButton::clicked,this,[=](){
         mm->clear();
        QString nume_sala=cauta->text();
         printf("\nS-A APASAT BUTONUL CAUTA SALA.\n");
        if(nume_sala.isEmpty())
        {
             printf("\nTEXT HOLDERUL ESTE GOL.\n");
            cauta->clear();
            mm->setText(" Introduceti o sala.");
           mm->setStyleSheet("color: red; font-size: 15px; font-family: Times New Roman; font-weight: bold;");
           mm->setGeometry(900,280,200,30);
           //raspunsServer="NU";
        }
       else
        {
            printf("\nTEXT HOLDERUL NU ESTE GOL.\n");
              printf("\n[CAUTA SALA ADMIN]: Raspunsul catre server este: %s\n",nume_sala.toUtf8().data());
            mm->clear();

            int cod=1;
            write(sd,&cod,sizeof(int));
            cod='S';
            write(sd,&cod,sizeof(int));

          int lungime_sala=nume_sala.length();
          write(sd,&lungime_sala,sizeof(int));
          printf("\n[CAUTA SALA ADMIN]: Lungimea raspunsului catre server este: %d\n",lungime_sala);

          write(sd,nume_sala.toUtf8().data(),lungime_sala);
           printf("\n[CAUTA SALA ADMIN]: Raspunsul catre server este: %s\n",nume_sala.toUtf8().data());

          int lungime_rasp=0;
          read(sd,&lungime_rasp,sizeof(int));
           printf("\n[RASPUNS SERVER]: Lungimea raspunsului de la server este: %d\n",lungime_rasp);
          char* sir_rasp=new char[lungime_rasp];
          memset(sir_rasp,0,lungime_rasp);
          read(sd,sir_rasp,lungime_rasp);
          sir_rasp[lungime_rasp]='\0';
           printf("\n[RASPUNS SERVER]: Raspunsul de la server este: %s\n",sir_rasp);

          raspuns_de_la_serverr=QString::fromUtf8(sir_rasp);

             if(strstr( sir_rasp,"NU"))//if(strstr(rasp,"NU"))
            {
                 cauta->clear();
                 mm->setText("Nu s-a putut gasi sala.");
                mm->setStyleSheet("color: red; font-size: 15px; font-family: Times New Roman; font-weight: bold;");
                mm->setGeometry(900,280,200,30);
            }
            else
            {
                mm->clear();
                 cauta->clear();
               // cb->setVisible(false);
               // cauta->setVisible(false);
                cautaSala( raspuns_de_la_serverr);//rasp
            }
        }
    });

    //BUTON CAUTA CORP

    QPushButton *corp=new QPushButton("CAUTA CORP",page);
    corp->setGeometry(650,350,200,80);
    corp->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");

     connect(corp,&QPushButton::clicked,this,[=](){

         mm->clear();
         cauta->clear();
         cb->setVisible(false);
         cauta->setVisible(false);

         int cod=7; //cod interogare;
                 write(sd,&cod,sizeof(int));
                 cod='C';
                   write(sd,&cod,sizeof(int));

                   int lung_rasp=0;

                   read(sd,&lung_rasp,sizeof(int));
                   printf("Am primit lung : %d!\n",lung_rasp);

                   char* arr_corp_sir=new char[lung_rasp];

                   read(sd,arr_corp_sir,lung_rasp);

                   arr_corp_sir[strlen(arr_corp_sir)]='\0';

                   printf("Sir primit: %s!",arr_corp_sir);

                   MainWindow::array_corpuri=QString::fromUtf8(arr_corp_sir);




          QWidget *newCorp=createAdminCorpPage();
          stack->insertWidget(10,newCorp);
          stack->setCurrentIndex(10);
     });
    //BUTON CAUTA FACULTATE

    QPushButton *fac=new QPushButton("CAUTA FACULTATE",page);
    fac->setGeometry(650,500,200,80);
    fac->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");

    connect(fac,&QPushButton::clicked,this,[=](){
        mm->clear();
        cauta->clear();
        cb->setVisible(false);
        cauta->setVisible(false);


        int cod=7; //cod interogare;
                write(sd,&cod,sizeof(int));
                cod='F';
                  write(sd,&cod,sizeof(int));

                  int lung_rasp=0;

                  read(sd,&lung_rasp,sizeof(int));
                  printf("Am primit lung : %d!\n",lung_rasp);

                  char* arr_corp_sir=new char[lung_rasp];

                  read(sd,arr_corp_sir,lung_rasp);

                  arr_corp_sir[strlen(arr_corp_sir)]='\0';

                  printf("Sir primit: %s!",arr_corp_sir);

                  MainWindow::array_facultati=QString::fromUtf8(arr_corp_sir);




        QWidget *newFac=createAdminFacPage();
        stack->insertWidget(10,newFac);
        stack->setCurrentIndex(10);
    });


    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
        mm->clear();
        cauta->clear();
        cb->setVisible(false);
        cauta->setVisible(false);
       showAdminMeniu();
    });

    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
       mm->clear();
        cauta->clear();
        cb->setVisible(false);
        cauta->setVisible(false);
        int cod=-1;
        write(sd,&cod,sizeof(int));
        exit(EXIT_SUCCESS);
    });

    return page;
}




char*numeFacc;
char*numeFacServerr;
 QString nume_in_butonn;
 QString nume_facultatee;
 int sell;
 QString sett;
QWidget *MainWindow::createAdminFacPage()
{

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("CAUTA FACULTATE",page);
    text->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; ");
    text->setGeometry(650,30,500,50);

    QLabel *textt=new QLabel ("Selectati o facultate:",page);
    textt->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; font-weight: bold;");
    textt->setGeometry(50,150,300,40);

    ///====================PENTRU OPTIUNEA DE FILTRARE=============================
    QLineEdit *capacitate_text=new QLineEdit(page);
    capacitate_text->setPlaceholderText("ex: >=30, <=30, ==30 etc.");
    capacitate_text->setGeometry(0,0,0,0);

    QLabel *capacitate_titlu=new QLabel ("",page);
    capacitate_titlu->setGeometry(20,500,0,0);



   QLineEdit *tip_text=new QLineEdit(page);
  tip_text->setPlaceholderText("ex: BIROU, AMFITEATRU, LABORATOR etc.");
   tip_text->setGeometry(0,0,0,0);


  QLabel *tip_titlu=new QLabel ("",page);
  tip_titlu->setGeometry(20,500,0,0);

   QPushButton *cautaSali=new QPushButton("AFISEAZA SALI",page);
   QLabel *eroare_filtrare=new QLabel("",page);
    /// ================================================


    int cod=7; //cod interogare afisare;
    write(sd,&cod,sizeof(int));

      cod='F';             //cod interogare pt corpuri;
      write(sd,&cod,sizeof(int));

      int lung_rasp;  ///lungime

      read(sd,&lung_rasp,sizeof(int));
      printf("Am primit lung : %d!\n",lung_rasp);

      char* arr_corp_sir=new char[lung_rasp];

      read(sd,arr_corp_sir,lung_rasp);

      arr_corp_sir[strlen(arr_corp_sir)]='\0';

      printf("Sir primit: %s!",arr_corp_sir);

     QString f=QString::fromUtf8(arr_corp_sir);




    int i=1;
    QString fac;
    int k=0;
    int x,y,z,t;
    x=350;
    y=150;
    z=150;
    t=30;
    QPushButton *bt[10];
    int b=0;
    QString ff[10];


    while(f[i]!='\0')
    {
        if(f[i]!="|")
            fac[k++]=f[i];
        else
        {
            bt[b]=new QPushButton("FACULTATEA DE\n "+fac,page);
            bt[b]->setGeometry(x,y,z,t);
            bt[b]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
            ff[b]=fac;
            b++;
            if(x>1000)
            {
                x=350;
                y+=50;
            }
            else
               x+=175;
            fac.clear();
            k=0;
        }
        i++;
    }

    QPushButton *cauta=new QPushButton("CAUTA",page);
    cauta->setGeometry(1300,150,100,40);
    cauta->setStyleSheet("background-color:grey; border: 2px solid black; color: black; font-size: 15px; font-weight:bold;");




    for(int i=0;i<b;i++)
    {
        connect(bt[i],&QPushButton::clicked,this,[=](){
             bt[i]->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
               nume_in_butonn.clear();
              nume_in_butonn=ff[i];
               //qDebug()<<"\n[BUTON CAUTA FACULTATE]: Numele facultatii este: "<<nume_facultatee<<endl;
             sell=i;
             sett="ok";
             for(int q=0;q<b;q++)
             {
                 if(q!=i)
                     bt[q]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
             }

        });
    }

    QPushButton *ts=new QPushButton("",page);
    QPushButton *tc=new QPushButton("",page);
    QString sss;
     ts->setVisible(false);
    QTextEdit *lista1=new QTextEdit(page);
     QScrollBar *bar1=new QScrollBar(page);
    bar1->setOrientation(Qt::Vertical);
    lista1->setVisible(false);
    bar1->setVisible(false);
    lista1->clear();
    bar1->setValue(0);

    QTextEdit *lista2=new QTextEdit(page);
     QScrollBar *bar2=new QScrollBar(page);
    bar2->setOrientation(Qt::Vertical);
    lista2->setVisible(false);
    bar2->setVisible(false);
    lista2->clear();
    bar2->setValue(0);

   // QPushButton *sortare1=new QPushButton("",page);
    QPushButton *filtrare1=new QPushButton("",page);
  //  sortare1->setVisible(false);
    filtrare1->setVisible(false);

   // QPushButton *sortare2=new QPushButton("",page);
  //  QPushButton *filtrare2=new QPushButton("",page);
   // sortare2->setVisible(false);
   // filtrare2->setVisible(false);

    lista2->setVisible(false);
    bar2->setVisible(false);
   // sortare2->setVisible(false);
   // filtrare2->setVisible(false);
    tc->setVisible(false);

    QLabel *err=new QLabel("",page);
    err->setVisible(false);

    eroare_filtrare->setVisible(false);
   cautaSali->setVisible(false);
   tip_text->clear();
   capacitate_text->clear();
   tip_titlu->setVisible(false);
   tip_text->setVisible(false);
   capacitate_text->setVisible(false);
    capacitate_titlu->setVisible(false);
    connect(cauta,&QPushButton::clicked,this,[=](){
           if(sett=="ok")
           {
               eroare_filtrare->setVisible(false);
              cautaSali->setVisible(false);
              tip_text->clear();
              capacitate_text->clear();
              tip_titlu->setVisible(false);
              tip_text->setVisible(false);
              capacitate_text->setVisible(false);
               capacitate_titlu->setVisible(false);

               nume_facultatee.clear();
               nume_facultatee=nume_in_butonn;
               //qDebug()<<"\n[BUTON CAUTA SALI]: Numele facultatii este: "<<nume_facultatee<<endl;
                err->setVisible(false);
               tc->setVisible(true);
                ts->setVisible(true);

                lista2->setVisible(false);
                bar2->setVisible(false);
               // sortare2->setVisible(false);
               // filtrare2->setVisible(false);
                lista1->clear();
                lista2->clear();
                bar1->setValue(0);
                 bar2->setValue(0);

                lista1->setVisible(false);
                bar1->setVisible(false);
               // sortare1->setVisible(false);
                filtrare1->setVisible(false);
              bt[sell]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
              ts->setGeometry(400,280,180,50);
              ts->setText("AFISATI TOATE SALILE >>");
              ts->setStyleSheet("background-color:grey; color:black; border:2px solid black; font-size:12px; font-weight:bold; ");
              tc->setGeometry(850,280,180,50);
              tc->setText("AFISATI TOATE CORPURILE >>");
              tc->setStyleSheet("background-color:grey; color:black; border:2px solid black; font-size:12px; font-weight:bold; ");
               sett="nok";
           }
           else
           {
               tc->setVisible(false);
                ts->setVisible(false);
              err->setVisible(true);
              err->setText("Selectati o facultate");
              err->setGeometry(1280,210,200,50);
              err->setStyleSheet("color:red; font-size: 20px;");

              lista2->setVisible(false);
              bar2->setVisible(false);
              //sortare2->setVisible(false);
            //  filtrare2->setVisible(false);
              lista1->clear();
              lista2->clear();
              bar1->setValue(0);
               bar2->setValue(0);

              lista1->setVisible(false);
              bar1->setVisible(false);
             // sortare1->setVisible(false);
              filtrare1->setVisible(false);
           }

        });

    connect(ts,&QPushButton::clicked,this,[=](){
          //delete [] numeFacServer;
          numeFacServerr=new char[nume_facultatee.length()];
          numeFacServerr=nume_facultatee.toUtf8().data();

          capacitate_text->clear();
          tip_text->clear();

        int cod=8; //cod interogare afisare;
        write(sd,&cod,sizeof(int));

          cod='S';             //cod interogare pt corpuri;
          write(sd,&cod,sizeof(int));

          int lung_rasp=nume_facultatee.length();   ///lungime
          write(sd,&lung_rasp,sizeof(int));

            ///numele facultatii
          write(sd,numeFacServerr,lung_rasp);
          printf("\nTrimit facultatea: %s.\n",numeFacServerr);
          memset(numeFacServerr,0,strlen(numeFacServerr));
          lung_rasp=0;
          read(sd,&lung_rasp,sizeof(int));
          printf("Am primit lung : %d!\n",lung_rasp);

          char* arr_corp_sir=new char[lung_rasp];

          read(sd,arr_corp_sir,lung_rasp);

          arr_corp_sir[strlen(arr_corp_sir)]='\0';

          printf("Sirul  primit este: %s!",arr_corp_sir);



         QString rasp=QString::fromUtf8(arr_corp_sir);

           qDebug()<<"\nLista de sali este: "<<sali<<"\n";
         lista1->setVisible(true);
         bar1->setVisible(true);
         //sortare1->setVisible(true);
         filtrare1->setVisible(true);

         lista2->setVisible(false);
         bar2->setVisible(false);
         //sortare2->setVisible(false);
       //  filtrare2->setVisible(false);
        lista1->setGeometry(300,350,400,400);
        QString sali;
        int i=1;
        QString sala;
        while(rasp[i]!='\0')
        {
            if(rasp[i]=='|')
            {
                sali=sali+sala+"\n";
                sala.clear();
            }
            else
                sala+=rasp[i];
            i++;
        }
        lista1->setText(sali);


        lista1->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
       bar1->setGeometry(700,350,20,400);
        bar1->setStyleSheet("background-color: grey; width: 10px;");
        //sortare1->setText("SORTARE");
       // sortare1->setGeometry(30,400,80,50);
      //  sortare1->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");
        bar2->setValue(0);
        lista2->clear();
        filtrare1->setText("FILTRARE");
        filtrare1->setGeometry(100,400,80,50);
        filtrare1->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");


    });

    cautaSali->setVisible(false);
      tip_text->clear();
      capacitate_text->clear();
      tip_titlu->setVisible(false);
      tip_text->setVisible(false);
      capacitate_text->setVisible(false);
       capacitate_titlu->setVisible(false);
       cautaSali->setVisible(false);
     connect(filtrare1,&QPushButton::clicked,this,[=](){
          eroare_filtrare->setVisible(false);
        capacitate_text->setVisible(true);
        capacitate_text->setGeometry(30,550,250,30);
         capacitate_titlu->setVisible(true);
         capacitate_titlu->setGeometry(20,500,230,30);
          capacitate_titlu->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         capacitate_titlu->setText("Introduceti o capacitate:");

         tip_text->setVisible(true);
         tip_text->setGeometry(30,670,250,30);
          tip_titlu->setVisible(true);
          tip_titlu->setGeometry(20,620,230,30);
           tip_titlu->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
          tip_titlu->setText("Introduceti tipul salii:");

           cautaSali->setVisible(true);
           cautaSali->setGeometry(30,730,130,30);
           cautaSali->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");
         ///////////////////////////////////////////////////////////////////////////
     });


     connect(cautaSali,&QPushButton::clicked,this,[=](){
          eroare_filtrare->setVisible(false);
         QString capacitate,tip;
         capacitate=capacitate_text->text();
         tip=tip_text->text();
         qDebug()<<"\n[FILTRARE]: Am citit capacitate: "<<capacitate<<" si tipul: "<<tip<<".\n";


    if(capacitate.isEmpty() && tip.isEmpty())
    {
         eroare_filtrare->setVisible(true);
         eroare_filtrare->setGeometry(250,700,250,30);
         eroare_filtrare->setStyleSheet("color: red; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         eroare_filtrare->setText("INTRODUCETI DATELE.");
    }
    else if(tip.isEmpty())
    {
        eroare_filtrare->setVisible(true);
        eroare_filtrare->setGeometry(250,700,250,30);
        eroare_filtrare->setStyleSheet("color: green; font-size: 20px; font-family: Times New Roman;font-weight: bold;");
        eroare_filtrare->setText("FILTRARE EFECTUATA.");

        int cod=11;
        write(sd,&cod,sizeof(int));


        cod='C';
        write(sd,&cod,sizeof(int));

        int lungime_capacitate=capacitate.length()-2;
        write(sd,&lungime_capacitate,sizeof(int));
        write(sd,capacitate.toUtf8().data()+2,lungime_capacitate);


        int numar_operator=0;



      char operator_introdus[3];
      operator_introdus[0]=capacitate.toUtf8().data()[0];
      operator_introdus[1]=capacitate.toUtf8().data()[1];
      operator_introdus[2]='\0';
      printf("Operator text introdus: %s!\n",operator_introdus);


      if(memcmp(operator_introdus,"==",2)==0)
      {
          printf("Operator ==\n");
          numar_operator=3; //==
      }

      else if(memcmp(operator_introdus,"<=",2)==0)
      {
          printf("Operator ==\n");
          numar_operator=2;
      }

       else if(memcmp(operator_introdus,">=",2)==0)
      {
          printf("Operator ==\n");
          numar_operator=4;
      }
      printf("Operator gasit numar: %d!\n",numar_operator);

      write(sd,&numar_operator,sizeof(int));


        cod='F';
        write(sd,&cod,sizeof(int));

        int lungime_raspuns;
        read(sd,&lungime_raspuns,sizeof(int));
        char *raspuns_server=new char[lungime_raspuns];
        memset(raspuns_server,0 ,lungime_raspuns);
        read(sd,raspuns_server,lungime_raspuns);
        raspuns_server[lungime_raspuns]='\0';

         printf("Raspuns server mesaj filtrare: %s!\n",raspuns_server);

        QString salii;
        int i=1;
        QString salaa;
        while(raspuns_server[i]!='\0')
        {
            if(raspuns_server[i]=='|')
            {
                salii=salii+salaa+"\n";
                 qDebug()<<"[SERVER]: Raspuns server prelucrat o sala: "<<salii<<".\n";
                salaa.clear();
            }
            else
               { salaa+=raspuns_server[i];
                qDebug()<<"[SERVER]: Raspuns server prelucrat o sala separat: "<<salaa<<".\n";
            }
            i++;
        }
        qDebug()<<"[SERVER]: Raspuns server prelucrat: "<<salii<<".\n";
        lista1->clear();
        lista1->setText(salii);
    }
    else if(capacitate.isEmpty())
    {
        eroare_filtrare->setVisible(true);
        eroare_filtrare->setGeometry(250,700,250,30);
        eroare_filtrare->setStyleSheet("color: green; font-size: 20px; font-family: Times New Roman;font-weight: bold;");
        eroare_filtrare->setText("FILTRARE EFECTUATA.");

        int cod=11;
        write(sd,&cod,sizeof(int));


        cod='T';
        write(sd,&cod,sizeof(int));

        int lungime_tip=tip.length();
        write(sd,&lungime_tip,sizeof(int));
        write(sd,tip.toUtf8().data(),lungime_tip);

        cod='F';
        write(sd,&cod,sizeof(int));

        int lungime_raspuns;
        read(sd,&lungime_raspuns,sizeof(int));
        char *raspuns_server=new char[lungime_raspuns];
        memset(raspuns_server,0 ,lungime_raspuns);
        read(sd,raspuns_server,lungime_raspuns);

        QString salii;
        int i=1;
        QString salaa;
        while(raspuns_server[i]!='\0')
        {
            if(raspunsServer[i]=='|')
            {
                salii=salii+salaa+"\n";
                salaa.clear();
            }
            else
                salaa+=raspuns_server[i];
            i++;
        }

        lista1->clear();
        lista1->setText(salii);
    }
    else
    {
        eroare_filtrare->setVisible(true);
        eroare_filtrare->setGeometry(250,700,250,30);
        eroare_filtrare->setStyleSheet("color: green; font-size: 20px; font-family: Times New Roman;font-weight: bold;");
        eroare_filtrare->setText("FILTRARE EFECTUATA.");

        int cod=11;
        write(sd,&cod,sizeof(int));


        cod='A';
        write(sd,&cod,sizeof(int));


        int lungime_capacitate=capacitate.length();
        write(sd,&lungime_capacitate,sizeof(int));
        write(sd,capacitate.toUtf8().data(),lungime_capacitate);

        int lungime_tip=tip.length();
        write(sd,&lungime_tip,sizeof(int));
        write(sd,tip.toUtf8().data(),lungime_tip);


        cod='F';
        write(sd,&cod,sizeof(int));

        int lungime_raspuns;
        read(sd,&lungime_raspuns,sizeof(int));
        char *raspuns_server=new char[lungime_raspuns];
        memset(raspuns_server,0 ,lungime_raspuns);
        read(sd,raspuns_server,lungime_raspuns);

        QString salii;
        int i=1;
        QString salaa;
        while(raspuns_server[i]!='\0')
        {
            if(raspunsServer[i]=='|')
            {
                salii=salii+salaa+"\n";
                salaa.clear();
            }
            else
                salaa+=raspuns_server[i];
            i++;
        }

        lista1->clear();
        lista1->setText(salii);
    }

    capacitate_text->clear();
    tip_text->clear();
    //QString sali_filtrate="C308\nC404\n";
    //lista->clear();
    //lista->setText(sali_filtrate);
});




    connect(tc,&QPushButton::clicked,this,[=](){

        eroare_filtrare->setVisible(false);
       cautaSali->setVisible(false);
       tip_text->clear();
       capacitate_text->clear();
       tip_titlu->setVisible(false);
       tip_text->setVisible(false);
       capacitate_text->setVisible(false);
        capacitate_titlu->setVisible(false);

        numeFacServerr=new char[nume_facultatee.length()];
        numeFacServerr=nume_facultatee.toUtf8().data();

      int cod=8; //cod interogare afisare;
      write(sd,&cod,sizeof(int));

        cod='C';             //cod interogare pt corpuri;
        write(sd,&cod,sizeof(int));

        int lung_rasp=nume_facultatee.length();   ///lungime
        write(sd,&lung_rasp,sizeof(int));

          ///numele facultatii
        write(sd,numeFacServerr,lung_rasp);
        printf("\nTrimit facultatea: %s.\n",numeFacServerr);
        memset(numeFacServerr,0,strlen(numeFacServerr));
        lung_rasp=0;
        read(sd,&lung_rasp,sizeof(int));
        printf("Am primit lung : %d!\n",lung_rasp);

        char* arr_corp_sir=new char[lung_rasp];

        read(sd,arr_corp_sir,lung_rasp);

        arr_corp_sir[strlen(arr_corp_sir)]='\0';

        printf("Sir primit: %s!",arr_corp_sir);




         QString rasp=QString::fromUtf8(arr_corp_sir);


        lista2->setVisible(true);
        bar2->setVisible(true);
        //sortare2->setVisible(true);
       // filtrare2->setVisible(true);
        bar1->setValue(0);
        lista1->clear();

        lista1->setVisible(false);
        bar1->setVisible(false);
       // sortare1->setVisible(false);
        filtrare1->setVisible(false);

        lista2->setGeometry(800,350,400,400);
        QString corpuri;
        int i=1;
        QString corp;
        while(rasp[i]!='\0')
        {
            if(rasp[i]=='|')
            {
                corpuri=corpuri+corp+"\n";
                corp.clear();
            }
            else
                corp+=rasp[i];
            i++;
        }
        lista2->setText(corpuri);
        lista2->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
       bar2->setGeometry(1200,350,20,400);
        bar2->setStyleSheet("background-color: grey; width: 10px;");



       // sortare2->setText("SORTARE");
       // sortare2->setGeometry(1230,400,80,50);
      //  sortare2->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");

     //   filtrare2->setText("FILTRARE");
      //  filtrare2->setGeometry(1400,400,80,50);
      //  filtrare2->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");


    });


   connect(bar1,&QScrollBar::valueChanged,lista1->verticalScrollBar(),&QScrollBar::setValue);
connect(bar2,&QScrollBar::valueChanged,lista2->verticalScrollBar(),&QScrollBar::setValue);
    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
         for(int i=0;i<b;i++)
         {
              bt[i]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
         }

         eroare_filtrare->setVisible(false);
        cautaSali->setVisible(false);
        tip_text->clear();
        capacitate_text->clear();
        tip_titlu->setVisible(false);
        tip_text->setVisible(false);
        capacitate_text->setVisible(false);
         capacitate_titlu->setVisible(false);

         tc->setVisible(false);
          ts->setVisible(false);

         lista2->setVisible(false);
         bar2->setVisible(false);
        // sortare2->setVisible(false);
       //  filtrare2->setVisible(false);
         lista1->clear();
         lista2->clear();
         bar1->setValue(0);
          bar2->setValue(0);

         lista1->setVisible(false);
         bar1->setVisible(false);
         //sortare1->setVisible(false);
         filtrare1->setVisible(false);

          err->setVisible(false);
     stack->setCurrentIndex(9);
    });
    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
        for(int i=0;i<b;i++)
        {
             bt[i]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
        }

        eroare_filtrare->setVisible(false);
       cautaSali->setVisible(false);
       tip_text->clear();
       capacitate_text->clear();
       tip_titlu->setVisible(false);
       tip_text->setVisible(false);
       capacitate_text->setVisible(false);
        capacitate_titlu->setVisible(false);

        tc->setVisible(false);
         ts->setVisible(false);
         err->setVisible(false);

        lista2->setVisible(false);
        bar2->setVisible(false);
        //sortare2->setVisible(false);
       // filtrare2->setVisible(false);
        lista1->clear();
        lista2->clear();
        bar1->setValue(0);
         bar2->setValue(0);

        lista1->setVisible(false);
        bar1->setVisible(false);
        //sortare1->setVisible(false);
        filtrare1->setVisible(false);
        int cod=-1;
        write(sd,&cod,sizeof(int));
        exit(EXIT_SUCCESS);
    });
    return page;
}

int nrCorpp;
QWidget *MainWindow::createAdminCorpPage()
{
    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("CAUTA CORP",page);
    text->setStyleSheet("color: white; font-size: 30px;font-weight:bold; font-family: Times New Roman; ");
    text->setGeometry(650,50,500,50);


    QLabel *textt=new QLabel ("Selectati un corp:",page);
    textt->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; ");
    textt->setGeometry(50,200,500,50);
    QLabel *eroare_filtrare=new QLabel("",page);
    eroare_filtrare->setVisible(false);
     QString rasp=array_corpuri;
    QPushButton *bt[20];
    int k=0,x,y,z,t;
    x=300;
    y=150;
    z=100;
    t=50;
    QString corpuri;
;  for(int i=1;i<rasp.length();i++)
  {
      if(rasp[i]!='|')
      {
          QString cc(rasp[i]);
          bt[k]=new QPushButton("CORP "+cc,page);
          bt[k]->setGeometry(x,y,z,t);
          bt[k]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");
          corpuri[k]=rasp[i];
          k++;
          if(x>900)
          {
              x=300;
              y+=75;
          }
          else
              x+=150;
      }
  }



    for(int i=0;i<k;i++)
    {
        connect(bt[i],&QPushButton::clicked,this,[=](){
            bt[i]->setStyleSheet(" background-color: red ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");
            QChar mc=corpuri.at(i);
            nrCorpp=mc.toLatin1();
            sali="A308  A309  A310";
            corpBut="OK";
            for(int j=0;j<k;j++)
                if(j!=i)
                {

                        bt[j]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");

                }
        });

    }



    QPushButton *showw=new QPushButton("AFISEAZA SALI",page);
    showw->setGeometry(1300,200,150,50);
    showw->setStyleSheet(" background-color: grey ;border: 2px solid black; color:black; font-size: 15px; ");
    QLabel *text3=new QLabel ("",page);
     QLabel *text4=new QLabel ("",page);
     text4->setGeometry(50,500,0,0);
     QLineEdit *cauta =new QLineEdit (page);
      QPushButton *cb=new QPushButton("",page);
      cb->setGeometry(900,500,0,0);
       cauta->setGeometry(900,200,0,0);
        QLabel *mm=new QLabel ("",page);
        cauta->setVisible(false);
        // cauta->clear();
          cb->setVisible(false);
           mm->clear();
           QLabel *text5=new QLabel ("",page);
           text5->setGeometry(50,500,0,0);

      QPushButton *sortare=new QPushButton("",page);
      QPushButton *filtrare=new QPushButton("",page);
       filtrare->setGeometry(0,0,0,0);
      QTextEdit *lista=new QTextEdit(page);
       lista->setGeometry(650,350,0,0);
       QScrollBar *bar=new QScrollBar(page);
       bar->setGeometry(650,350,0,0);
      lista->setReadOnly(true);
      bar->setOrientation(Qt::Vertical);
      lista->setReadOnly(true);
      bar->setOrientation(Qt::Vertical);
      lista->setVisible(false);
      bar->setVisible(false);
      lista->clear();
      sortare->setVisible(false);
      filtrare->setVisible(false);
      bar->setValue(0);

      ///====================PENTRU OPTIUNEA DE FILTRARE=============================
      QLineEdit *capacitate_text=new QLineEdit(page);
      capacitate_text->setPlaceholderText("ex: >=30, <=30, ==30 etc.");
      capacitate_text->setGeometry(0,0,0,0);

      QLabel *capacitate_titlu=new QLabel ("",page);
      capacitate_titlu->setGeometry(20,500,0,0);



     QLineEdit *tip_text=new QLineEdit(page);
    tip_text->setPlaceholderText("ex: BIROU, AMFITEATRU, LABORATOR etc.");
     tip_text->setGeometry(0,0,0,0);


    QLabel *tip_titlu=new QLabel ("",page);
    tip_titlu->setGeometry(20,500,0,0);

     QPushButton *cautaSali=new QPushButton("AFISEAZA SALI",page);
      /// ================================================

    connect(showw,&QPushButton::clicked,this,[=](){
         eroare_filtrare->setVisible(false);
        cautaSali->setVisible(false);
        tip_text->clear();
        capacitate_text->clear();
        tip_titlu->setVisible(false);
        tip_text->setVisible(false);
        capacitate_text->setVisible(false);
         capacitate_titlu->setVisible(false);

        lista->setVisible(true);
        bar->setVisible(true);
       // sortare->setVisible(true);
        filtrare->setVisible(true);
        text5->clear();
        cauta->setVisible(true);
        cb->setVisible(true);
        mm->clear();

        if(corpBut=="OK")
       {
            for(int j=0;j<k;j++)
               bt[j]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");

            text3->setText("Sali disponibile :  ");
            text3->setStyleSheet("color: white; font-size: 25px; font-family: Times New Roman; font-weight:bold;");
            text3->setGeometry(650,270,200,50);
            text4->setText("Introduceti o sala: ");
            text4->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight:bold;");
            text4->setGeometry(1100,380,200,50);

             cauta->setGeometry(1100,440,150,30);
             cauta->setPlaceholderText("Enter a room.");
             cb->setText("CAUTA");
             cb->setGeometry(1100,480,50,20);
             cb->setStyleSheet("background-color: grey; border: 2px solid black; color: black;");
             corpBut="NOK";
            /// sortare->setText("SORTARE");
            /// sortare->setGeometry(100,400,80,50);
            /// sortare->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");

             filtrare->setText("FILTRARE");
             filtrare->setGeometry(250,400,80,50);
             filtrare->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");


                       int cod=9; //cod interogare afisare;
                       write(sd,&cod,sizeof(int));

                         cod='C';             //cod interogare pt corpuri;
                         write(sd,&cod,sizeof(int));

                         int lung_rasp=sizeof(char);   ///lungime
                         write(sd,&lung_rasp,sizeof(int));

                           ///numele corpului
                         write(sd,&nrCorpp,sizeof(char));

                         lung_rasp=0;
                         read(sd,&lung_rasp,sizeof(int));
                         printf("Am primit lung : %d!\n",lung_rasp);

                         char* arr_corp_sir=new char[lung_rasp];

                         read(sd,arr_corp_sir,lung_rasp);

                         arr_corp_sir[strlen(arr_corp_sir)]='\0';

                         printf("Sir primit: %s!",arr_corp_sir);

                        QString rasp=QString::fromUtf8(arr_corp_sir);



             QString sali;
             int i=1;
             QString sala;
             while(rasp[i]!='\0')
             {
                 if(rasp[i]=='|')
                 {
                     sali=sali+sala+"\n";
                     sala.clear();
                 }
                 else
                     sala+=rasp[i];
                 i++;
             }
             lista->setGeometry(550,330,400,400);
             lista->setText(sali);
             lista->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
            bar->setGeometry(950,330,20,400);
             bar->setStyleSheet("background-color: grey; width: 10px;");

        }
        else
        {
            sortare->setVisible(false);
            filtrare->setVisible(false);
            lista->setVisible(false);
            bar->setVisible(false);
            lista->clear();
            cauta->setVisible(false);
            cb->setVisible(false);
            mm->clear();
            text3->clear();
            text4->clear();
            text5->setText("Selectati un corp.");
            text5->setStyleSheet("color: red; font-size: 20px; font-family: Times New Roman;");
            text5->setGeometry(1300,250,200,50);
        }

    });


   cautaSali->setVisible(false);
     tip_text->clear();
     capacitate_text->clear();
     tip_titlu->setVisible(false);
     tip_text->setVisible(false);
     capacitate_text->setVisible(false);
      capacitate_titlu->setVisible(false);
      cautaSali->setVisible(false);
    connect(filtrare,&QPushButton::clicked,this,[=](){
         eroare_filtrare->setVisible(false);
       capacitate_text->setVisible(true);
       capacitate_text->setGeometry(250,500,250,30);
        capacitate_titlu->setVisible(true);
        capacitate_titlu->setGeometry(20,500,230,30);
         capacitate_titlu->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
        capacitate_titlu->setText("Introduceti o capacitate:");

        tip_text->setVisible(true);
        tip_text->setGeometry(250,550,250,30);
         tip_titlu->setVisible(true);
         tip_titlu->setGeometry(20,550,230,30);
          tip_titlu->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         tip_titlu->setText("Introduceti tipul salii:");

          cautaSali->setVisible(true);
          cautaSali->setGeometry(300,630,130,30);
          cautaSali->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");
        ///////////////////////////////////////////////////////////////////////////
    });

    connect(cautaSali,&QPushButton::clicked,this,[=](){
         eroare_filtrare->setVisible(false);
        QString capacitate,tip;
        capacitate=capacitate_text->text();
        tip=tip_text->text();
        qDebug()<<"\n[FILTRARE]: Am citit capacitate: "<<capacitate<<" si tipul: "<<tip<<".\n";



        if(capacitate.isEmpty() && tip.isEmpty())
        {
             eroare_filtrare->setVisible(true);
             eroare_filtrare->setGeometry(250,700,250,30);
             eroare_filtrare->setStyleSheet("color: red; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
             eroare_filtrare->setText("INTRODUCETI DATELE.");
        }
        else if(tip.isEmpty())
        {
            eroare_filtrare->setVisible(true);
            eroare_filtrare->setGeometry(250,700,250,30);
            eroare_filtrare->setStyleSheet("color: green; font-size: 20px; font-family: Times New Roman;font-weight: bold;");
            eroare_filtrare->setText("FILTRARE EFECTUATA.");

            int cod=11;
            write(sd,&cod,sizeof(int));


            cod='C';
            write(sd,&cod,sizeof(int));

            int lungime_capacitate=capacitate.length()-2;
            write(sd,&lungime_capacitate,sizeof(int));
            write(sd,capacitate.toUtf8().data()+2,lungime_capacitate);


            int numar_operator=0;



          char operator_introdus[3];
          operator_introdus[0]=capacitate.toUtf8().data()[0];
          operator_introdus[1]=capacitate.toUtf8().data()[1];
          operator_introdus[2]='\0';
          printf("Operator text introdus: %s!\n",operator_introdus);


          if(memcmp(operator_introdus,"==",2)==0)
          {
              printf("Operator ==\n");
              numar_operator=3; //==
          }

          else if(memcmp(operator_introdus,"<=",2)==0)
          {
              printf("Operator ==\n");
              numar_operator=2;
          }

           else if(memcmp(operator_introdus,">=",2)==0)
          {
              printf("Operator ==\n");
              numar_operator=4;
          }
          printf("Operator gasit numar: %d!\n",numar_operator);

          write(sd,&numar_operator,sizeof(int));


            cod='C';
            write(sd,&cod,sizeof(int));

            int lungime_raspuns;
            read(sd,&lungime_raspuns,sizeof(int));
            char *raspuns_server=new char[lungime_raspuns];
            memset(raspuns_server,0 ,lungime_raspuns);
            read(sd,raspuns_server,lungime_raspuns);
            raspuns_server[lungime_raspuns]='\0';

             printf("Raspuns server mesaj filtrare: %s!\n",raspuns_server);

            QString salii;
            int i=1;
            QString salaa;
            while(raspuns_server[i]!='\0')
            {
                if(raspuns_server[i]=='|')
                {
                    salii=salii+salaa+"\n";
                     qDebug()<<"[SERVER]: Raspuns server prelucrat o sala: "<<salii<<".\n";
                    salaa.clear();
                }
                else
                   { salaa+=raspuns_server[i];
                    qDebug()<<"[SERVER]: Raspuns server prelucrat o sala separat: "<<salaa<<".\n";
                }
                i++;
            }
            qDebug()<<"[SERVER]: Raspuns server prelucrat: "<<salii<<".\n";
            lista->clear();
            lista->setText(salii);
        }
        else if(capacitate.isEmpty())
        {
            eroare_filtrare->setVisible(true);
            eroare_filtrare->setGeometry(250,700,250,30);
            eroare_filtrare->setStyleSheet("color: green; font-size: 20px; font-family: Times New Roman;font-weight: bold;");
            eroare_filtrare->setText("FILTRARE EFECTUATA.");

            int cod=11;
            write(sd,&cod,sizeof(int));


            cod='T';
            write(sd,&cod,sizeof(int));

            int lungime_tip=tip.length();
            write(sd,&lungime_tip,sizeof(int));
            write(sd,tip.toUtf8().data(),lungime_tip);

            cod='C';
            write(sd,&cod,sizeof(int));

            int lungime_raspuns;
            read(sd,&lungime_raspuns,sizeof(int));
            char *raspuns_server=new char[lungime_raspuns];
            memset(raspuns_server,0 ,lungime_raspuns);
            read(sd,raspuns_server,lungime_raspuns);

            QString salii;
            int i=1;
            QString salaa;
            while(raspuns_server[i]!='\0')
            {
                if(rasp[i]=='|')
                {
                    salii=salii+salaa+"\n";
                    salaa.clear();
                }
                else
                    salaa+=raspuns_server[i];
                i++;
            }

            lista->clear();
            lista->setText(salii);
        }
        else
        {
            eroare_filtrare->setVisible(true);
            eroare_filtrare->setGeometry(250,700,250,30);
            eroare_filtrare->setStyleSheet("color: green; font-size: 20px; font-family: Times New Roman;font-weight: bold;");
            eroare_filtrare->setText("FILTRARE EFECTUATA.");

            int cod=11;
            write(sd,&cod,sizeof(int));


            cod='A';
            write(sd,&cod,sizeof(int));


            int lungime_capacitate=capacitate.length();
            write(sd,&lungime_capacitate,sizeof(int));
            write(sd,capacitate.toUtf8().data(),lungime_capacitate);

            int lungime_tip=tip.length();
            write(sd,&lungime_tip,sizeof(int));
            write(sd,tip.toUtf8().data(),lungime_tip);


            cod='C';
            write(sd,&cod,sizeof(int));

            int lungime_raspuns;
            read(sd,&lungime_raspuns,sizeof(int));
            char *raspuns_server=new char[lungime_raspuns];
            memset(raspuns_server,0 ,lungime_raspuns);
            read(sd,raspuns_server,lungime_raspuns);

            QString salii;
            int i=1;
            QString salaa;
            while(raspuns_server[i]!='\0')
            {
                if(rasp[i]=='|')
                {
                    salii=salii+salaa+"\n";
                    salaa.clear();
                }
                else
                    salaa+=raspuns_server[i];
                i++;
            }

            lista->clear();
            lista->setText(salii);
        }

        capacitate_text->clear();
        tip_text->clear();
        //QString sali_filtrate="C308\nC404\n";
        //lista->clear();
        //lista->setText(sali_filtrate);
    });

    connect(bar,&QScrollBar::valueChanged,lista->verticalScrollBar(),&QScrollBar::setValue);

    connect(cb,&QPushButton::clicked,this,[=](){
         mm->clear();

        QString nume_sala=cauta->text();
        if(nume_sala.isEmpty())
        {
            cauta->clear();
            mm->setText(" Introduceti o sala.");
           mm->setStyleSheet("color: red; font-size: 15px; font-family: Times New Roman; font-weight: bold;");
           mm->setGeometry(1100,500,200,30);
           //raspunsServer="NU";
        }
       else
        {   int cod=1;
            write(sd,&cod,sizeof(int));
            cod='S';
            write(sd,&cod,sizeof(int));
            int lungime_sala=nume_sala.length()+1;
             write(sd,&lungime_sala,sizeof(int));
          QByteArray ba=nume_sala.toUtf8();
          char*raspp=ba.data();
          write(sd,raspp,lungime_sala);
          int lungime_rasp=0;
          read(sd,&lungime_rasp,sizeof(int));
          char* sir_rasp=new char[lungime_rasp];
          read(sd,sir_rasp,lungime_rasp);

          sir_rasp[strlen(sir_rasp)]='\0';

          raspunsServer=QString::fromUtf8(sir_rasp);

             if(strstr(sir_rasp,"NU"))//if(strstr(rasp,"NU"))
            {
                 cauta->clear();
                 mm->setText("Nu s-a putut gasi sala.");
                mm->setStyleSheet("color: red; font-size: 15px; font-family: Times New Roman; font-weight: bold;");
                mm->setGeometry(1100,500,200,30);
            }
            else
            {
                mm->clear();
                 cauta->clear();
               // cb->setVisible(false);
               // cauta->setVisible(false);
                cautaSala(raspunsServer);//rasp
            }
        }
    });


    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
         eroare_filtrare->setVisible(false);
        cautaSali->setVisible(false);
        tip_text->clear();
        capacitate_text->clear();
        tip_titlu->setVisible(false);
        tip_text->setVisible(false);
        capacitate_text->setVisible(false);
         capacitate_titlu->setVisible(false);
        bar->setValue(0);
        sortare->setVisible(false);
        filtrare->setVisible(false);
        lista->setVisible(false);
        bar->setVisible(false);
        lista->clear();
         text5->clear();
         cauta->clear();
        cauta->setVisible(false);
        cb->setVisible(false);
         mm->clear();
        text3->clear();
        text4->clear();
       stack->setCurrentIndex(9);
    });
    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
         eroare_filtrare->setVisible(false);
        cautaSali->setVisible(false);
        tip_text->clear();
        capacitate_text->clear();
        tip_titlu->setVisible(false);
        tip_text->setVisible(false);
        capacitate_text->setVisible(false);
         capacitate_titlu->setVisible(false);
        bar->setValue(0);
        sortare->setVisible(false);
        filtrare->setVisible(false);
        lista->setVisible(false);
        bar->setVisible(false);
        lista->clear();
         text5->clear();
         cb->setVisible(false);
         cauta->clear();
        cauta->setVisible(false);
         mm->clear();
        text4->clear();
         text3->clear();
         int cod=-1;
         write(sd,&cod,sizeof(int));
         exit(EXIT_SUCCESS);
    });
    return page;
}

char *raspuns_catre_Server;

QWidget *MainWindow::createAdminInsereazaPage()
{

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("INSERARE DATE",page);
    text->setStyleSheet("color: white; font-size: 35px; font-family: Times New Roman; ");
    text->setGeometry(640,10,900,80);


     QPushButton *insf=new QPushButton("INSERARE\nFACULTATE",page);///inserare facultate
     insf->setGeometry(200,200,150,50);
     insf->setStyleSheet(" background-color: grey ;border: 3px solid black; font-size: 20px ; color: black; font-weight: bold;");

     QPushButton *insc=new QPushButton("INSERARE\nCORP",page);///inserare facultate
     insc->setGeometry(200,270,150,50);
     insc->setStyleSheet(" background-color: grey ;border: 3px solid black; font-size: 20px ; color: black; font-weight: bold;");

     QPushButton *inss=new QPushButton("INSERARE\nSALA",page);///inserare facultate
     inss->setGeometry(200,340,150,50);
     inss->setStyleSheet(" background-color: grey ;border: 3px solid black; font-size: 20px ; color: black; font-weight: bold;");

     //========INSEREAZA FACULTATE==========================================================================
       QLineEdit *f1=new QLineEdit(page);      ///textholder
       QLabel *f2=new QLabel ("",page);    ///text
       QLineEdit *f3=new QLineEdit(page);      ///textholder
       QLabel *f4=new QLabel ("",page);    ///text
       f1->clear();
       f3->clear();
       f1->setVisible(false);
       f2->setVisible(false);
       f3->setVisible(false);
       f4->setVisible(false);
       QPushButton *f7=new QPushButton("",page);
       f7->setVisible(false);

     //========================================================================================================


       //========INSEREAZA CORP==========================================================================
         QLineEdit *c1=new QLineEdit(page);      ///textholder
         QLabel *c2=new QLabel ("",page);    ///text
         QLineEdit *c3=new QLineEdit(page);      ///textholder
         QLabel *c4=new QLabel ("",page);    ///text
         c1->clear();
         c3->clear();
         c1->setVisible(false);
         c2->setVisible(false);
         c3->setVisible(false);
         c4->setVisible(false);
         QPushButton *c7=new QPushButton("",page);
         c7->setVisible(false);

       //========================================================================================================

         //========INSEREAZA SALA==========================================================================
           QLineEdit *s1=new QLineEdit(page);      ///textholder
           QLabel *s2=new QLabel ("",page);    ///text
           QLineEdit *s3=new QLineEdit(page);      ///textholder
           QLabel *s4=new QLabel ("",page);    ///text
            QLabel *s5=new QLabel ("",page);    ///text
             QLineEdit *s6=new QLineEdit(page);      ///textholder
           s1->clear();
           s3->clear();
           s1->setVisible(false);
           s2->setVisible(false);
           s3->setVisible(false);
           s4->setVisible(false);
           s6->clear();
           s6->setVisible(false);
           s5->setVisible(false);

           QPushButton *s7=new QPushButton("",page);
           s7->setVisible(false);

         //========================================================================================================


           QLabel *tf=new QLabel ("",page);
            QLabel *ts=new QLabel ("",page);
             QLabel *tc=new QLabel ("",page);
             tf->setVisible(false);
             ts->setVisible(false);
             tc->setVisible(false);



     connect(insf,&QPushButton::clicked,this,[=](){//inserare facultate

         tf->setVisible(false);
         ts->setVisible(false);
         tc->setVisible(false);
         f1->setVisible(true);
         f2->setVisible(true);
         f3->setVisible(true);
         f4->setVisible(true);
         f1->setPlaceholderText("Enter the name");
         f1->setGeometry(830,270,400,60);
         f2->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         f2->setGeometry(570,270,300,80);
         f2->setText("Introduceti numele facultatii: ");

         f3->setPlaceholderText("Enter the name");
         f3->setGeometry(830,400,400,60);
         f4->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         f4->setGeometry(570,400,300,80);
         f4->setText("Introduceti capacitatea\nfacultatii: ");

         c1->clear();
         c3->clear();
         c1->setVisible(false);
         c2->setVisible(false);
         c3->setVisible(false);
         c4->setVisible(false);

         s1->clear();
         s3->clear();
         s1->setVisible(false);
         s2->setVisible(false);
         s3->setVisible(false);
         s4->setVisible(false);
         s6->clear();
         s6->setVisible(false);
         s5->setVisible(false);
          s7->setVisible(false);
          f7->setVisible(true);
          f7->setText("INSEREAZA");
          f7->setGeometry(830,520,150,50);
          f7->setStyleSheet("background-color: grey; color: black; border: 2px solid black; font-size: 25px; font-weight: bold;");
     });


     connect(f7,&QPushButton::clicked,this,[=](){
         tf->setVisible(false);
         ts->setVisible(false);
         tc->setVisible(false);
         QString tf1=f1->text();
         QString tf2=f3->text();
          //qDebug()<<"\n0.Am citit numele: "<<tf1<<endl;
         if(tf1.isEmpty() || tf2.isEmpty())
         {
             tf->setVisible(true);
             tf->setText("Introduceti datele.");
             tf->setGeometry(1000,520,300,30);
             tf->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
         }
         else
         {

             ///coduri
             int cod=2;
             write(sd,&cod,sizeof(int));
             cod='F';
             write(sd,&cod,sizeof(int));


            ///lungime raspuns
             int lung=tf1.length();
             write(sd,&lung,sizeof(int));
             printf("\nLungimea raspunsului pentru server este: %d\n",lung);


             ///raspuns
             write(sd,  tf1.toUtf8().data(),lung);


            ///lungime rasp 2
              lung=tf2.length();
              write(sd,&lung,sizeof(int));

              ///raspuns 2
              write(sd, tf2.toUtf8().data(),lung);


              ///raspuns de la server
              int lg_ms_server=0;
              read(sd,&lg_ms_server,sizeof(int));
                qDebug()<<"\nRaspunsul de la server are lungimea: "<<lg_ms_server<<"\n";
             char * rasp=new char[lg_ms_server];
              // qDebug()<<"\n[SERVER]: Am raspunsul: "<<rasp<<" de lungime: "<<lg_ms_server<<endl;
              read(sd,rasp,lg_ms_server);
               rasp[lg_ms_server]='\0';
              //qDebug()<<"\n[SERVER]: Am primit raspunsul: "<<rasp<<" de lungime: "<<lg_ms_server<<endl;

              if(strstr(rasp,"NU"))
              {
                  tf->setVisible(true);
                  tf->setText("Datele exista in baza de date.");
                  tf->setGeometry(1000,520,300,30);
                  tf->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
              }
              else
              {
                  tf->setVisible(true);
                  tf->setText("Inserare reusita.");
                  tf->setGeometry(1000,520,300,30);
                  tf->setStyleSheet(" color: green;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
              }

         }
     });

     connect(insc,&QPushButton::clicked,this,[=](){//inserare corp
         tf->setVisible(false);
         ts->setVisible(false);
         tc->setVisible(false);
         f1->clear();
         f3->clear();
         f1->setVisible(false);
         f2->setVisible(false);
         f3->setVisible(false);
         f4->setVisible(false);
         c1->setVisible(true);
         c2->setVisible(true);
         c3->setVisible(true);
         c4->setVisible(true);
         s1->clear();
         s3->clear();
         s1->setVisible(false);
         s2->setVisible(false);
         s3->setVisible(false);
         s4->setVisible(false);
         s6->clear();
         s6->setVisible(false);
         s5->setVisible(false);
         c1->setPlaceholderText("Enter the name");
         c1->setGeometry(830,270,400,60);
         c2->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         c2->setGeometry(570,270,300,80);
         c2->setText("Introduceti numele corpului: ");

         c3->setPlaceholderText("Enter the name");
         c3->setGeometry(830,400,400,60);
         c4->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         c4->setGeometry(570,400,300,80);
         c4->setText("Introduceti numele facultatii: ");
          s7->setVisible(false);
          c7->setVisible(true);
          c7->setText("INSEREAZA");
          c7->setGeometry(830,520,150,50);
          c7->setStyleSheet("background-color: grey; color: black; border: 2px solid black; font-size: 25px; font-weight: bold;");
     });

    connect(c7,&QPushButton::clicked,this,[=](){
        tf->setVisible(false);
        ts->setVisible(false);
        tc->setVisible(false);
        QString tf1=c1->text();
        QString tf2=c3->text();
        if(tf1.isEmpty() || tf2.isEmpty())
        {
           // tf->setVisible(false);
            //ts->setVisible(false);
            tc->setVisible(true);
            tc->setText("Introduceti datele.");
            tc->setGeometry(1000,520,300,30);
            tc->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
        }
        else
        {
           ///trimit coduri
          int cod=2;
          write(sd,&cod,sizeof(int));
          cod='C';
          write(sd,&cod,sizeof(int));

          ///lungime rsp 1
          int lung=tf1.length();
          write(sd,&lung,sizeof(int));

          ///rsp 1
          write(sd,tf1.toUtf8().data(),lung);
         printf("\n[INSERARE CORP 1]: Trimit la server mesajul -%s- de lungime -%d-.\n",tf1.toUtf8().data(),lung);

          ///lungime rsp 2
           lung=tf2.length();
           write(sd,&lung,sizeof(int));

           ///rsp 2
           write(sd,tf2.toUtf8().data(),lung);
             printf("\n[INSERARE CORP 2]: Trimit la server mesajul -%s- de lungime -%d-.\n",tf2.toUtf8().data(),lung);

           ///raspuns de la server
           lung=0;
           read(sd,&lung,sizeof(int));
           char *rasp=new char[lung];
           read(sd,rasp,lung);
           rasp[lung]='\0';
            printf("\n[RASPUNS SERVER]: Primesc de la server mesajul -%s- de lungime -%d-.\n",rasp,lung);

           if(strstr(rasp,"NU"))
           {
               tc->setVisible(true);
               tc->setText("Datele exista in baza de date.");
               tc->setGeometry(1000,520,300,30);
               tc->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
           }
           else
           {
               tc->setVisible(true);
               tc->setText("Inserare reusita.");
               tc->setGeometry(1000,520,300,30);
               tc->setStyleSheet(" color: green;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
           }

        }
    });

     connect(inss,&QPushButton::clicked,this,[=](){
         tf->setVisible(false);
         ts->setVisible(false);
         tc->setVisible(false);
         f1->clear();
         f3->clear();
         f1->setVisible(false);
         f2->setVisible(false);
         f3->setVisible(false);
         f4->setVisible(false);
         c1->clear();
         c3->clear();
         c1->setVisible(false);
         c2->setVisible(false);
         c3->setVisible(false);
         c4->setVisible(false);

         s1->setVisible(true);
         s2->setVisible(true);
         s3->setVisible(true);
         s4->setVisible(true);
         s6->setVisible(true);
         s5->setVisible(true);
         s1->setPlaceholderText("Enter the name");
         s1->setGeometry(830,270,400,60);
         s2->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         s2->setGeometry(570,270,300,80);
         s2->setText("Introduceti numele salii: ");

         s3->setPlaceholderText("Enter the name");
         s3->setGeometry(830,400,400,60);
         s4->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         s4->setGeometry(570,400,300,80);
         s4->setText("Introduceti capacitatea salii: ");

         s6->setPlaceholderText("Enter the name");
         s6->setGeometry(830,550,400,60);
         s5->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         s5->setGeometry(570,550,300,80);
         s5->setText("Introduceti numele corpului: ");
         f7->setVisible(false);
          c7->setVisible(false);
          s7->setVisible(true);
          s7->setText("INSEREAZA");
          s7->setGeometry(830,620,150,50);
          s7->setStyleSheet("background-color: grey; color: black; border: 2px solid black; font-size: 25px; font-weight: bold;");
     });


    connect(s7,&QPushButton::clicked,this,[=](){
        tf->setVisible(false);
        ts->setVisible(false);
        tc->setVisible(false);
        QString tf1=s1->text();
        QString tf2=s3->text();
        QString tf3=s6->text();
        if(tf1.isEmpty() || tf2.isEmpty() || tf3.isEmpty())
        {
           // tf->setVisible(false);
            ts->setVisible(true);
            //tc->setVisible(false);
            ts->setText("Introduceti datele.");
            ts->setGeometry(1000,620,300,30);
            ts->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
        }
        else
        {
            ///trimit coduri
            int cod=2;
            write(sd,&cod,sizeof(int));
            cod='S';
            write(sd,&cod,sizeof(int));

             //lungime rasp1
            int lung=tf1.length();
            write(sd,&lung,sizeof(int));

            //rasp 1
             write(sd,tf1.toUtf8().data(),lung);


             //lungime rasp 2
             lung=tf2.length();
             write(sd,&lung,sizeof(int));

             //rasp 2
             write(sd,tf2.toUtf8().data(),lung);


             //lungime rasp 3
              lung=tf3.length();
              write(sd,&lung,sizeof(int));

              //rasp 3
              write(sd,tf3.toUtf8().data(),lung);



              //raspuns server
              lung=0;
             read(sd,&lung,sizeof(int));
            char* rasp=new char[lung];
             read(sd,rasp,lung);
             rasp[lung]='\0';
             if(strstr(rasp,"NU"))
             {
                 ts->setVisible(true);
                 ts->setText("Datele exista in baza de date.");
                 ts->setGeometry(1000,620,300,30);
                 ts->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
             }
             else
             {
                 ts->setVisible(true);
                 ts->setText("Inserare reusita.");
                 ts->setGeometry(1000,620,300,30);
                 ts->setStyleSheet(" color: green;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
             }
        }
    });

     QPushButton *butonBack=new QPushButton("<<  BACK",page);
     butonBack->setGeometry(50,50,150,50);
     butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
     connect(butonBack,&QPushButton::clicked,this,[=]()
     {
         f1->clear();
         f3->clear();
         f1->setVisible(false);
         f2->setVisible(false);
         f3->setVisible(false);
         f4->setVisible(false);
         c1->clear();
         c3->clear();
         c1->setVisible(false);
         c2->setVisible(false);
         c3->setVisible(false);
         c4->setVisible(false);
         s1->clear();
         s3->clear();
         s1->setVisible(false);
         s2->setVisible(false);
         s3->setVisible(false);
         s4->setVisible(false);
         s6->clear();
         s6->setVisible(false);
         s5->setVisible(false);
          s7->setVisible(false);
          f7->setVisible(false);
           c7->setVisible(false);
           tf->setVisible(false);
           ts->setVisible(false);
           tc->setVisible(false);
        stack->setCurrentIndex(3);
     });

     QPushButton *discon=new QPushButton("DECONECTARE",page);
     discon->setGeometry(1250,780,150,50);
     discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
     connect(discon,&QPushButton::clicked,this,[=]()
     {
         f1->clear();
         f3->clear();
         f1->setVisible(false);
         f2->setVisible(false);
         f3->setVisible(false);
         f4->setVisible(false);
         c1->clear();
         c3->clear();
         c1->setVisible(false);
         c2->setVisible(false);
         c3->setVisible(false);
         c4->setVisible(false);
         s1->clear();
         s3->clear();
         s1->setVisible(false);
         s2->setVisible(false);
         s3->setVisible(false);
         s4->setVisible(false);
         s6->clear();
         s6->setVisible(false);
         s5->setVisible(false);
          s7->setVisible(false);
          f7->setVisible(false);
           c7->setVisible(false);
           tf->setVisible(false);
           ts->setVisible(false);
           tc->setVisible(false);
         int cod=-1;
         write(sd,&cod,sizeof(int));
         exit(EXIT_SUCCESS);
     });

     return page;
}


QWidget *MainWindow::createAdminStergePage()
{
    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("STERGERE DATE",page);
    text->setStyleSheet("color: white; font-size: 35px; font-family: Times New Roman; ");
    text->setGeometry(640,10,900,80);


     QPushButton *strf=new QPushButton("STERGE\nFACULTATE",page);///inserare facultate
     strf->setGeometry(200,200,150,50);
     strf->setStyleSheet(" background-color: grey ;border: 3px solid black; font-size: 20px ; color: black; font-weight: bold;");

     QPushButton *strc=new QPushButton("STERGE\nCORP",page);///inserare facultate
     strc->setGeometry(200,270,150,50);
     strc->setStyleSheet(" background-color: grey ;border: 3px solid black; font-size: 20px ; color: black; font-weight: bold;");

     QPushButton *strs=new QPushButton("STERGE\nSALA",page);///inserare facultate
     strs->setGeometry(200,340,150,50);
     strs->setStyleSheet(" background-color: grey ;border: 3px solid black; font-size: 20px ; color: black; font-weight: bold;");

     //========STERGERE FACULTATE==========================================================================
       QLineEdit *f1=new QLineEdit(page);      ///textholder
       QLabel *f2=new QLabel ("",page);    ///text

       f1->clear();

       f1->setVisible(false);
       f2->setVisible(false);

       QPushButton *f3=new QPushButton("",page);
       f3->setVisible(false);

     //========================================================================================================


       //========STERGERE CORP==========================================================================
         QLineEdit *c1=new QLineEdit(page);      ///textholder
         QLabel *c2=new QLabel ("",page);    ///text

         c1->clear();

         c1->setVisible(false);
         c2->setVisible(false);

         QPushButton *c3=new QPushButton("",page);
         c3->setVisible(false);

       //========================================================================================================

         //========STERGERE SALA==========================================================================
           QLineEdit *s1=new QLineEdit(page);      ///textholder
           QLabel *s2=new QLabel ("",page);    ///text

           s1->clear();

           s1->setVisible(false);
           s2->setVisible(false);

           QPushButton *s3=new QPushButton("",page);
           s3->setVisible(false);

         //========================================================================================================


           QLabel *tf=new QLabel ("",page);
            QLabel *ts=new QLabel ("",page);
             QLabel *tc=new QLabel ("",page);
             tf->setVisible(false);
             ts->setVisible(false);
             tc->setVisible(false);

     connect(strf,&QPushButton::clicked,this,[=](){//inserare facultate
         tf->setVisible(false);
         ts->setVisible(false);
         tc->setVisible(false);
         f1->setVisible(true);
         f2->setVisible(true);
         f3->setVisible(true);

         f1->setPlaceholderText("Enter the name");
         f1->setGeometry(830,270,400,60);
         f2->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         f2->setGeometry(570,270,300,80);
         f2->setText("Introduceti numele facultatii: ");
         f3->setText("STERGE");
         f3->setGeometry(830,350,150,30);
         f3->setStyleSheet("background-color: grey; color:black; border: 2px solid black; font-size: 20px; font-family: Times New Roman; font-weight: bold;");

         c1->clear();
         c1->setVisible(false);
         c2->setVisible(false);
         c3->setVisible(false);

         s1->clear();
         s1->setVisible(false);
         s2->setVisible(false);
         s3->setVisible(false);

     });


     connect(f3,&QPushButton::clicked,this,[=](){
         tf->setVisible(false);
         ts->setVisible(false);
         tc->setVisible(false);
         QString tf1=f1->text();

         if(tf1.isEmpty())
         {
             tf->setVisible(true);
             tf->setText("Introduceti datele.");
             tf->setGeometry(1000,350,300,30);
             tf->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
         }
         else
         {
             int cod=3;
             write(sd,&cod,sizeof(int));
             cod='F';
             write(sd,&cod,sizeof(int));
             int lung=tf1.length();
             write(sd,&lung,sizeof(int));
             char * rasp=tf1.toUtf8().data();
             write(sd,rasp,lung);
             memset(rasp,0,lung);
              lung=0;
              read(sd,&lung,sizeof(int));
              rasp=new char[lung];
              read(sd,rasp,lung);
              if(strstr(rasp,"NU"))
              {
                  tf->setVisible(true);
                  tf->setText("Datele nu exista in baza de date.");
                  tf->setGeometry(1000,350,300,30);
                  tf->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
              }
              else
              {
                  tf->setVisible(true);
                  tf->setText("Stergere reusita.");
                  tf->setGeometry(1000,350,300,30);
                  tf->setStyleSheet(" color: green;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
              }
         }
     });

    connect(strc,&QPushButton::clicked,this,[=](){//inserare corp
         tf->setVisible(false);
         ts->setVisible(false);
         tc->setVisible(false);
         f1->clear();

         f1->setVisible(false);
         f2->setVisible(false);
         f3->setVisible(false);
         s1->clear();

         s1->setVisible(false);
         s2->setVisible(false);
         s3->setVisible(false);

         c1->setVisible(true);
         c2->setVisible(true);
         c3->setVisible(true);

         c1->setPlaceholderText("Enter the name");
         c1->setGeometry(830,270,400,60);
         c2->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         c2->setGeometry(570,270,300,80);
         c2->setText("Introduceti numele corpului: ");

         c3->setText("STERGE");
         c3->setGeometry(830,350,150,30);
         c3->setStyleSheet("background-color: grey; color:black; border: 2px solid black; font-size: 20px; font-family: Times New Roman; font-weight: bold;");


     });

    connect(c3,&QPushButton::clicked,this,[=](){
        tf->setVisible(false);
        ts->setVisible(false);
        tc->setVisible(false);
        QString tf1=c1->text();

        if(tf1.isEmpty())
        {
            tc->setVisible(true);
            tc->setText("Introduceti datele.");
            tc->setGeometry(1000,350,300,30);
            tc->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
        }
        else
        {
            int cod=3;
            write(sd,&cod,sizeof(int));
            cod='C';
            write(sd,&cod,sizeof(int));
            int lung=tf1.length();
            write(sd,&lung,sizeof(int));
            char * rasp=tf1.toUtf8().data();
            write(sd,rasp,lung);
            memset(rasp,0,lung);
             lung=0;
             read(sd,&lung,sizeof(int));
             rasp=new char[lung];
             read(sd,rasp,lung);
             if(strstr(rasp,"NU"))
             {
                 tc->setVisible(true);
                 tc->setText("Datele nu exista in baza de date.");
                 tc->setGeometry(1000,350,300,30);
                 tc->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
             }
             else
             {
                 tc->setVisible(true);
                 tc->setText("Stergere reusita.");
                 tc->setGeometry(1000,350,300,30);
                 tc->setStyleSheet(" color: green;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
             }
        }
    });

     connect(strs,&QPushButton::clicked,this,[=](){
         tf->setVisible(false);
         ts->setVisible(false);
         tc->setVisible(false);
         f1->clear();

         f1->setVisible(false);
         f2->setVisible(false);
         f3->setVisible(false);

         c1->clear();

         c1->setVisible(false);
         c2->setVisible(false);
         c3->setVisible(false);

         s1->setVisible(true);
         s2->setVisible(true);
         s3->setVisible(true);

         s1->setPlaceholderText("Enter the name");
         s1->setGeometry(830,270,400,60);
         s2->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
         s2->setGeometry(570,270,300,80);
         s2->setText("Introduceti numele salii: ");


         s3->setText("STERGE");
         s3->setGeometry(830,350,150,30);
         s3->setStyleSheet("background-color: grey; color:black; border: 2px solid black; font-size: 20px; font-family: Times New Roman; font-weight: bold;");


        });


    connect(s3,&QPushButton::clicked,this,[=](){
        tf->setVisible(false);
        ts->setVisible(false);
        tc->setVisible(false);
        QString tf1=s1->text();

        if(tf1.isEmpty())
        {
            tc->setVisible(true);
            tc->setText("Introduceti datele.");
            tc->setGeometry(1000,350,300,30);
            tc->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
        }
        else
        {
            int cod=3;
            write(sd,&cod,sizeof(int));
            cod='S';
            write(sd,&cod,sizeof(int));
            int lung=tf1.length();
            write(sd,&lung,sizeof(int));
            char * rasp=tf1.toUtf8().data();
            write(sd,rasp,lung);
            memset(rasp,0,lung);
             lung=0;
             read(sd,&lung,sizeof(int));
             rasp=new char[lung];
             read(sd,rasp,lung);
             if(strstr(rasp,"NU"))
             {
                 ts->setVisible(true);
                 ts->setText("Datele nu exista in baza de date.");
                 ts->setGeometry(1000,350,400,30);
                 ts->setStyleSheet(" color: red;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
             }
             else
             {
                 ts->setVisible(true);
                 ts->setText("Stergere reusita.");
                 ts->setGeometry(1000,350,300,30);
                 ts->setStyleSheet(" color: green;  font-size: 25px;font-family: Times New Roman; font-weight: bold;");
             }
        }
    });


    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
        f1->setVisible(false);
        f1->clear();
        f2->setVisible(false);
        f3->setVisible(false);
        tf->setVisible(false);

        c1->setVisible(false);
        c1->clear();
        c2->setVisible(false);
        c3->setVisible(false);
        tc->setVisible(false);

        s1->setVisible(false);
        s1->clear();
        s2->setVisible(false);
        s3->setVisible(false);
        ts->setVisible(false);
       stack->setCurrentIndex(3);
    });

    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
        f1->setVisible(false);
        f1->clear();
        f2->setVisible(false);
        f3->setVisible(false);
        tf->setVisible(false);

        c1->setVisible(false);
        c1->clear();
        c2->setVisible(false);
        c3->setVisible(false);
        tc->setVisible(false);

        s1->setVisible(false);
        s1->clear();
        s2->setVisible(false);
        s3->setVisible(false);
        ts->setVisible(false);
        int cod=-1;
        write(sd,&cod,sizeof(int));
        exit(EXIT_SUCCESS);
    });

     return page;
}



QWidget *MainWindow::createVizitMeniu(){

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);


    QLabel *text=new QLabel ("MENIU VIZITATOR",page);
    text->setStyleSheet("color: white; font-size: 35px; font-family: Times New Roman; ");
    text->setGeometry(600,10,900,80);


    //creare meniu
    //BUTON CAUTA SALA
    QLineEdit *cauta =new QLineEdit (page);
     cauta->setGeometry(900,200,0,0);
     QPushButton *cb=new QPushButton("CAUTA",page);
     cb->setGeometry(900,200,0,0);

    QPushButton *sala=new QPushButton("CAUTA SALA",page);
    sala->setGeometry(650,200,200,80);
    sala->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");
      QLabel *mm=new QLabel (".",page);
      cauta->clear();
      mm->clear();
      cb->setVisible(false);
      cauta->setVisible(false);
    connect(sala,&QPushButton::clicked,this,[=]()
    {

        cb->setVisible(true);
        cauta->setVisible(true);
        cauta->setPlaceholderText("Enter a room.");
        cauta->setGeometry(900,200,200,35);
        cb->setGeometry(900,250,100,25);
        cb->setStyleSheet("background-color: grey; color: black; border: 2px solid black;");


    });
    connect(cb,&QPushButton::clicked,this,[=](){
         mm->clear();
        QString nume_sala=cauta->text();

        if(nume_sala.isEmpty())
        {
            cauta->clear();
            mm->setText(" Introduceti o sala.");
           mm->setStyleSheet("color: red; font-size: 15px; font-family: Times New Roman; font-weight: bold;");
           mm->setGeometry(900,280,200,30);
           //raspunsServer="NU";
        }
       else
        {   int cod=1;
            write(sd,&cod,sizeof(int));
            cod='S';
            write(sd,&cod,sizeof(int));
            int lungime_sala=nume_sala.length()+1;
             write(sd,&lungime_sala,sizeof(int));
          QByteArray ba=nume_sala.toUtf8();
          char*raspp=ba.data();
          write(sd,raspp,lungime_sala);
          int lungime_rasp=0;
          read(sd,&lungime_rasp,sizeof(int));
          char* sir_rasp=new char[lungime_rasp];
          read(sd,sir_rasp,lungime_rasp);

          sir_rasp[strlen(sir_rasp)]='\0';

          raspunsServer=QString::fromUtf8(sir_rasp);

             if(strstr(sir_rasp,"NU"))//if(strstr(rasp,"NU"))
            {
                 cauta->clear();
                 mm->setText("Nu s-a putut gasi sala.");
                mm->setStyleSheet("color: red; font-size: 15px; font-family: Times New Roman; font-weight: bold;");
                mm->setGeometry(900,280,200,30);
            }
            else
            {
                mm->clear();
                 cauta->clear();
               // cb->setVisible(false);
               // cauta->setVisible(false);
                cautaSala(raspunsServer);//rasp
            }
        }
    });

    //BUTON CAUTA CORP

    QPushButton *corp=new QPushButton("CAUTA CORP",page);
    corp->setGeometry(650,350,200,80);
    corp->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");

     connect(corp,&QPushButton::clicked,this,[=](){

         mm->clear();
         cauta->clear();
         cb->setVisible(false);
         cauta->setVisible(false);

         int cod=7; //cod interogare;
                 write(sd,&cod,sizeof(int));
                 cod='C';
                   write(sd,&cod,sizeof(int));

                   int lung_rasp=0;

                   read(sd,&lung_rasp,sizeof(int));
                   printf("Am primit lung : %d!\n",lung_rasp);

                   char* arr_corp_sir=new char[lung_rasp];

                   read(sd,arr_corp_sir,lung_rasp);

                   arr_corp_sir[strlen(arr_corp_sir)]='\0';

                   printf("Sir primit: %s!",arr_corp_sir);

                   MainWindow::array_corpuri=QString::fromUtf8(arr_corp_sir);


        /*QWidget *newCorp=nullptr;
         newCorp=createNewCorpPage();
          stack->addWidget(newCorp);
          stack->setCurrentIndex(11);*/
                     QWidget *newWidd=createNewCorpPage();
                  stack->insertWidget(10,newWidd);
                  stack->setCurrentIndex(10);

     });
    //BUTON CAUTA FACULTATE

    QPushButton *fac=new QPushButton("CAUTA FACULTATE",page);
    fac->setGeometry(650,500,200,80);
    fac->setStyleSheet(" background-color: lightgrey ;border: 2px solid black; font-size: 15px ; color: black; font-weight: bold;");

    connect(fac,&QPushButton::clicked,this,[=](){
        mm->clear();
        cauta->clear();
        cb->setVisible(false);
        cauta->setVisible(false);


        int cod=7; //cod interogare;
                write(sd,&cod,sizeof(int));
                cod='F';
                  write(sd,&cod,sizeof(int));

                  int lung_rasp=0;

                  read(sd,&lung_rasp,sizeof(int));
                  printf("Am primit lung : %d!\n",lung_rasp);

                  char* arr_corp_sir=new char[lung_rasp];

                  read(sd,arr_corp_sir,lung_rasp);

                  arr_corp_sir[strlen(arr_corp_sir)]='\0';

                  printf("Sir primit: %s!",arr_corp_sir);

                  MainWindow::array_facultati=QString::fromUtf8(arr_corp_sir);


/*
        QWidget *newFac=nullptr;
       newFac=createNewFacPage();
        stack->addWidget(newFac);
        stack->setCurrentIndex(11);*/
          QWidget *newWid=createNewFacPage();

         stack->insertWidget(10,newWid);
         // stack->removeWidget(stack->widget(10));
         stack->setCurrentIndex(10);
    });


   /* QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
        mm->clear();
        cauta->clear();
        cb->setVisible(false);
        cauta->setVisible(false);
       showUserPage();
    });*/

    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
       mm->clear();
        cauta->clear();
        cb->setVisible(false);
        cauta->setVisible(false);
        int cod=-1;
        write(sd,&cod,sizeof(int));
        exit(EXIT_SUCCESS);
    });

    return page;
}
 int sel;
QString set="nok";
QWidget *MainWindow::createFacPage(){

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("CAUTA FACULTATE",page);
    text->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; ");
    text->setGeometry(650,30,500,50);

    QLabel *textt=new QLabel ("Selectati o facultate:",page);
    textt->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; font-weight: bold;");
    textt->setGeometry(50,150,300,40);

    QString f="|INFORMATICA|MATEMATICA|BIOLOGIE|ECONOMIE|GEOGRAFIE|EDUCATIE FIZICA SI SPORT|";

    int i=1;
    QString fac;
    int k=0;
    int x,y,z,t;
    x=350;
    y=150;
    z=150;
    t=30;
    QPushButton *bt[10];
    int b=0;
    QString ff[10];

    while(f[i]!='\0')
    {
        if(f[i]!="|")
            fac[k++]=f[i];
        else
        {
            bt[b]=new QPushButton("FACULTATEA DE\n "+fac,page);
            bt[b]->setGeometry(x,y,z,t);
            bt[b]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
            ff[b]=fac;
            b++;
            if(x>1000)
            {
                x=350;
                y+=50;
            }
            else
               x+=175;
            fac.clear();
            k=0;
        }
        i++;
    }

    QPushButton *cauta=new QPushButton("CAUTA",page);
    cauta->setGeometry(1300,150,100,40);
    cauta->setStyleSheet("background-color:grey; border: 2px solid black; color: black; font-size: 15px; font-weight:bold;");
    char rasp[500]="|C309|C310|C311|C312|";
    for(int i=0;i<b;i++)
    {
        connect(bt[i],&QPushButton::clicked,this,[=](){
             bt[i]->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");

             sel=i;
             set="ok";
             for(int q=0;q<b;q++)
             {
                 if(q!=i)
                     bt[q]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
             }

        });
    }

    QPushButton *ts=new QPushButton("",page);
    QPushButton *tc=new QPushButton("",page);
    QString sss;
     ts->setVisible(false);
    QTextEdit *lista1=new QTextEdit(page);
     QScrollBar *bar1=new QScrollBar(page);
    bar1->setOrientation(Qt::Vertical);
    lista1->setVisible(false);
    bar1->setVisible(false);
    lista1->clear();
    bar1->setValue(0);

    QTextEdit *lista2=new QTextEdit(page);
     QScrollBar *bar2=new QScrollBar(page);
    bar2->setOrientation(Qt::Vertical);
    lista2->setVisible(false);
    bar2->setVisible(false);
    lista2->clear();
    bar2->setValue(0);

    QPushButton *sortare1=new QPushButton("",page);
    QPushButton *filtrare1=new QPushButton("",page);
    sortare1->setVisible(false);
    filtrare1->setVisible(false);

    QPushButton *sortare2=new QPushButton("",page);
    QPushButton *filtrare2=new QPushButton("",page);
    sortare2->setVisible(false);
    filtrare2->setVisible(false);

    QPushButton *cs=new QPushButton("",page);
    QPushButton *cc=new QPushButton("",page);
    cs->setVisible(false);
    cc->setVisible(false);
    cc->setVisible(false);
    lista2->setVisible(false);
    bar2->setVisible(false);
    sortare2->setVisible(false);
    filtrare2->setVisible(false);
    tc->setVisible(false);

    QLabel *err=new QLabel("",page);
    err->setVisible(false);
    connect(cauta,&QPushButton::clicked,this,[=](){
           if(set=="ok")
           {
                err->setVisible(false);
               tc->setVisible(true);
                ts->setVisible(true);
                cc->setVisible(false);
                lista2->setVisible(false);
                bar2->setVisible(false);
                sortare2->setVisible(false);
                filtrare2->setVisible(false);
                lista1->clear();
                lista2->clear();
                bar1->setValue(0);
                 bar2->setValue(0);
                cs->setVisible(false);
                lista1->setVisible(false);
                bar1->setVisible(false);
                sortare1->setVisible(false);
                filtrare1->setVisible(false);
              bt[sel]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
              ts->setGeometry(400,280,180,50);
              ts->setText("AFISATI TOATE SALILE >>");
              ts->setStyleSheet("background-color:grey; color:black; border:2px solid black; font-size:12px; font-weight:bold; ");
              tc->setGeometry(850,280,180,50);
              tc->setText("AFISATI TOATE CORPURILE >>");
              tc->setStyleSheet("background-color:grey; color:black; border:2px solid black; font-size:12px; font-weight:bold; ");
               set="nok";
           }
           else
           {
               tc->setVisible(false);
                ts->setVisible(false);
              err->setVisible(true);
              err->setText("Selectati o facultate");
              err->setGeometry(1280,210,200,50);
              err->setStyleSheet("color:red; font-size: 20px;");
              cc->setVisible(false);
              lista2->setVisible(false);
              bar2->setVisible(false);
              sortare2->setVisible(false);
              filtrare2->setVisible(false);
              lista1->clear();
              lista2->clear();
              bar1->setValue(0);
               bar2->setValue(0);
              cs->setVisible(false);
              lista1->setVisible(false);
              bar1->setVisible(false);
              sortare1->setVisible(false);
              filtrare1->setVisible(false);
           }

        });

    connect(ts,&QPushButton::clicked,this,[=](){
         cs->setVisible(true);
         lista1->setVisible(true);
         bar1->setVisible(true);
         sortare1->setVisible(true);
         filtrare1->setVisible(true);
         cc->setVisible(false);
         lista2->setVisible(false);
         bar2->setVisible(false);
         sortare2->setVisible(false);
         filtrare2->setVisible(false);
        lista1->setGeometry(300,350,400,400);
        QString sali;
        int i=1;
        QString sala;
        while(rasp[i]!='\0')
        {
            if(rasp[i]=='|')
            {
                sali=sali+sala+"\n";
                sala.clear();
            }
            else
                sala+=rasp[i];
            i++;
        }
        lista1->setText(sali);
        lista1->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
       bar1->setGeometry(700,350,20,400);
        bar1->setStyleSheet("background-color: grey; width: 10px;");
        sortare1->setText("SORTARE");
        sortare1->setGeometry(30,400,80,50);
        sortare1->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");
        bar2->setValue(0);
        lista2->clear();
        filtrare1->setText("FILTRARE");
        filtrare1->setGeometry(200,400,80,50);
        filtrare1->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");

        cs->setText("CAUTA\nSALA");
        cs->setGeometry(300,770,150,50);
        cs->setStyleSheet("background-color: grey; border: 2px solid black; color: black;font-weight:bold;");

    });


    connect(tc,&QPushButton::clicked,this,[=](){
        cc->setVisible(true);
        lista2->setVisible(true);
        bar2->setVisible(true);
        sortare2->setVisible(true);
        filtrare2->setVisible(true);
        bar1->setValue(0);
        lista1->clear();
        cs->setVisible(false);
        lista1->setVisible(false);
        bar1->setVisible(false);
        sortare1->setVisible(false);
        filtrare1->setVisible(false);

        lista2->setGeometry(800,350,400,400);
        QString corpuri;
        int i=1;
        QString corp;
        while(rasp[i]!='\0')
        {
            if(rasp[i]=='|')
            {
                corpuri=corpuri+corp+"\n";
                corp.clear();
            }
            else
                corp+=rasp[i];
            i++;
        }
        lista2->setText(corpuri);
        lista2->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
       bar2->setGeometry(1200,350,20,400);
        bar2->setStyleSheet("background-color: grey; width: 10px;");



        sortare2->setText("SORTARE");
        sortare2->setGeometry(1230,400,80,50);
        sortare2->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");

        filtrare2->setText("FILTRARE");
        filtrare2->setGeometry(1400,400,80,50);
        filtrare2->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");


        cc->setText("CAUTA\nCORP");
        cc->setGeometry(1070,770,150,50);
        cc->setStyleSheet("background-color: grey; border: 2px solid black; color: black;font-weight:bold;");
    });

    connect(cs,&QPushButton::clicked,this,&MainWindow::showVizitMeniu);
    connect(cc,&QPushButton::clicked,this,&MainWindow::showCorpPage);

   connect(bar1,&QScrollBar::valueChanged,lista1->verticalScrollBar(),&QScrollBar::setValue);
connect(bar2,&QScrollBar::valueChanged,lista2->verticalScrollBar(),&QScrollBar::setValue);
    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
         for(int i=0;i<b;i++)
         {
              bt[i]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
         }

         tc->setVisible(false);
          ts->setVisible(false);
         cc->setVisible(false);
         lista2->setVisible(false);
         bar2->setVisible(false);
         sortare2->setVisible(false);
         filtrare2->setVisible(false);
         lista1->clear();
         lista2->clear();
         bar1->setValue(0);
          bar2->setValue(0);
         cs->setVisible(false);
         lista1->setVisible(false);
         bar1->setVisible(false);
         sortare1->setVisible(false);
         filtrare1->setVisible(false);

          err->setVisible(false);
      showVizitMeniu();
    });
    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
        for(int i=0;i<b;i++)
        {
             bt[i]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
        }

        tc->setVisible(false);
         ts->setVisible(false);
         err->setVisible(false);
        cc->setVisible(false);
        lista2->setVisible(false);
        bar2->setVisible(false);
        sortare2->setVisible(false);
        filtrare2->setVisible(false);
        lista1->clear();
        lista2->clear();
        bar1->setValue(0);
         bar2->setValue(0);
        cs->setVisible(false);
        lista1->setVisible(false);
        bar1->setVisible(false);
        sortare1->setVisible(false);
        filtrare1->setVisible(false);
        int cod=-1;
        write(sd,&cod,sizeof(int));
        exit(EXIT_SUCCESS);
    });
    return page;
}

QWidget *MainWindow::createCorpPage(){

    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("CAUTA CORP",page);
    text->setStyleSheet("color: white; font-size: 30px;font-weight:bold; font-family: Times New Roman; ");
    text->setGeometry(650,50,500,50);


    QLabel *textt=new QLabel ("Selectati un corp:",page);
    textt->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; ");
    textt->setGeometry(50,200,500,50);

    char rasp[200]="|A|B|C|D|E|F|G|H|I|J|k|";
    QPushButton *bt[20];
    int k=0,x,y,z,t;
    x=300;
    y=150;
    z=100;
    t=50;
    //char corpuri[30];
;  for(int i=1;i<10;i++)
  {
      if(rasp[i]!='|')
      {
          QString cc(rasp[i]);
          bt[k]=new QPushButton("CORP "+cc,page);
          bt[k]->setGeometry(x,y,z,t);
          bt[k]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");
        //  corpuri[k]=rasp[i];
          k++;
          if(x>900)
          {
              x=300;
              y+=75;
          }
          else
              x+=150;
      }
  }

    for(int i=0;i<k;i++)
    {
        connect(bt[i],&QPushButton::clicked,this,[=](){
            bt[i]->setStyleSheet(" background-color: red ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");
            sali="A308  A309  A310";
            corpBut="OK";
            for(int j=0;j<k;j++)
                if(j!=i)
                {

                        bt[j]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");

                }
        });

    }



    QPushButton *showw=new QPushButton("AFISEAZA SALI",page);
    showw->setGeometry(1300,200,150,50);
    showw->setStyleSheet(" background-color: grey ;border: 2px solid black; color:black; font-size: 15px; ");
    QLabel *text3=new QLabel ("",page);
     QLabel *text4=new QLabel ("",page);
     text4->setGeometry(50,500,0,0);
     QLineEdit *cauta =new QLineEdit (page);
      QPushButton *cb=new QPushButton("",page);
      cb->setGeometry(900,500,0,0);
       cauta->setGeometry(900,200,0,0);
        QLabel *mm=new QLabel ("",page);
        cauta->setVisible(false);
        // cauta->clear();
          cb->setVisible(false);
           mm->clear();
           QLabel *text5=new QLabel ("",page);
           text5->setGeometry(50,500,0,0);

      QPushButton *sortare=new QPushButton("",page);
      QPushButton *filtrare=new QPushButton("",page);

      QTextEdit *lista=new QTextEdit(page);
       lista->setGeometry(650,350,0,0);
       QScrollBar *bar=new QScrollBar(page);
       bar->setGeometry(650,350,0,0);
      lista->setReadOnly(true);
      bar->setOrientation(Qt::Vertical);
      lista->setReadOnly(true);
      bar->setOrientation(Qt::Vertical);
      lista->setVisible(false);
      bar->setVisible(false);
      lista->clear();
      sortare->setVisible(false);
      filtrare->setVisible(false);
      bar->setValue(0);
    connect(showw,&QPushButton::clicked,this,[=](){

        lista->setVisible(true);
        bar->setVisible(true);
        sortare->setVisible(true);
        filtrare->setVisible(true);
        text5->clear();
        cauta->setVisible(true);
        cb->setVisible(true);
        mm->clear();

        if(corpBut=="OK")
       {
            for(int j=0;j<k;j++)
               bt[j]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");

            text3->setText("Sali disponibile :  ");
            text3->setStyleSheet("color: white; font-size: 25px; font-family: Times New Roman; font-weight:bold;");
            text3->setGeometry(650,270,200,50);
            text4->setText("Introduceti o sala: ");
            text4->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight:bold;");
            text4->setGeometry(1100,380,200,50);

             cauta->setGeometry(1100,440,150,30);
             cauta->setPlaceholderText("Enter a room.");
             cb->setText("CAUTA");
             cb->setGeometry(1100,480,50,20);
             cb->setStyleSheet("background-color: grey; border: 2px solid black; color: black;");
             corpBut="NOK";
             sortare->setText("SORTARE");
             sortare->setGeometry(100,400,80,50);
             sortare->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");

             filtrare->setText("FILTRARE");
             filtrare->setGeometry(250,400,80,50);
             filtrare->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");
             QString rasp;
             rasp="|C309|C308|C310|C311|";
             QString sali;
             int i=1;
             QString sala;
             while(rasp[i]!='\0')
             {
                 if(rasp[i]=='|')
                 {
                     sali=sali+sala+"\n";
                     sala.clear();
                 }
                 else
                     sala+=rasp[i];
                 i++;
             }
             lista->setGeometry(550,330,400,400);
             lista->setText(sali);
             lista->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
            bar->setGeometry(950,330,20,400);
             bar->setStyleSheet("background-color: grey; width: 10px;");

        }
        else
        {
            sortare->setVisible(false);
            filtrare->setVisible(false);
            lista->setVisible(false);
            bar->setVisible(false);
            lista->clear();
            cauta->setVisible(false);
            cb->setVisible(false);
            mm->clear();
            text3->clear();
            text4->clear();
            text5->setText("Selectati un corp.");
            text5->setStyleSheet("color: red; font-size: 20px; font-family: Times New Roman;");
            text5->setGeometry(1300,250,200,50);
        }

    });

    connect(bar,&QScrollBar::valueChanged,lista->verticalScrollBar(),&QScrollBar::setValue);

    connect(cb,&QPushButton::clicked,this,[=](){
         mm->clear();

        QString nume_sala=cauta->text();

        if(nume_sala=="C309")
         raspunsServer="|C309|INFORMATICA|C|CURS|100|/home/florea/PR_RETELE/client/sala.png|";
        else
          raspunsServer="NU";

        if(nume_sala.isEmpty())
        {
            cauta->clear();
            mm->setText(" Introduceti o  sala.");
           mm->setStyleSheet("color: red; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
           mm->setGeometry(1100,500,200,80);
        }
        else if(raspunsServer=="NU")
        {
            mm->clear();
             cauta->clear();
             mm->setText("Nu s-a putut gasi sala.");
            mm->setStyleSheet("color: red; font-size: 20px; font-family: Times New Roman; font-weight: bold;");
            mm->setGeometry(1100,500,200,80);
        }
        else
        {
            mm->clear();
             cauta->clear();
           // cb->setVisible(false);
           // cauta->setVisible(false);
            cautaSala(raspunsServer);
        }
        //mm->clear();
    });


    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
        bar->setValue(0);
        sortare->setVisible(false);
        filtrare->setVisible(false);
        lista->setVisible(false);
        bar->setVisible(false);
        lista->clear();
         text5->clear();
         cauta->clear();
        cauta->setVisible(false);
        cb->setVisible(false);
         mm->clear();
        text3->clear();
        text4->clear();
       showVizitMeniu();
    });
    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
        bar->setValue(0);
        sortare->setVisible(false);
        filtrare->setVisible(false);
        lista->setVisible(false);
        bar->setVisible(false);
        lista->clear();
         text5->clear();
         cb->setVisible(false);
         cauta->clear();
        cauta->setVisible(false);
         mm->clear();
        text4->clear();
         text3->clear();
         int cod=-1;
         write(sd,&cod,sizeof(int));
         exit(EXIT_SUCCESS);
    });
    return page;
}


void MainWindow::showStartPage(){

    stack->setCurrentIndex(0);
}

void MainWindow::showUserPage(){

    stack->setCurrentIndex(1);
}

void MainWindow::showLogPage(){

    stack->setCurrentIndex(2);
}

void MainWindow::showAdminMeniu(){

    stack->setCurrentIndex(3);
}

void MainWindow::showVizitMeniu(){

    stack->setCurrentIndex(4);
}

void MainWindow::showCorpPage(){

    stack->setCurrentIndex(6);
}
void MainWindow::showFacPage(){

    stack->setCurrentIndex(5);
}


int MainWindow::verifCont(){
    if(stusername=="ioana" && stpassword=="ioana")
        return 1;
    return 0;
}

int MainWindow::existaSala()
{
    return 0;
}

fereastraSala::fereastraSala(QWidget *parent):QDialog(parent)
{
   tab=new QTabWidget(this);
   QWidget *tab1=new QWidget();
    QWidget *tab2=new QWidget();
    tab->addTab(tab1,"INFORMATII");
    tab->addTab(tab2,"VIZUALIZARE");
    tab1->setStyleSheet("background-color: blue;");
    tab2->setStyleSheet("background-color: blue;");
}

  char nrCorp;
QWidget *MainWindow::createNewCorpPage()
{
    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("CAUTA CORP",page);
    text->setStyleSheet("color: white; font-size: 30px;font-weight:bold; font-family: Times New Roman; ");
    text->setGeometry(650,50,500,50);


    QLabel *textt=new QLabel ("Selectati un corp:",page);
    textt->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; ");
    textt->setGeometry(50,200,500,50);


     QString rasp=array_corpuri;
    QPushButton *bt[20];
    int k=0,x,y,z,t;
    x=300;
    y=150;
    z=100;
    t=50;
    QString corpuri;
;  for(int i=1;i<rasp.length();i++)
  {
      if(rasp[i]!='|')
      {
          QString cc(rasp[i]);
          bt[k]=new QPushButton("CORP "+cc,page);
          bt[k]->setGeometry(x,y,z,t);
          bt[k]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");
          corpuri[k]=rasp[i];
          k++;
          if(x>900)
          {
              x=300;
              y+=75;
          }
          else
              x+=150;
      }
  }



    for(int i=0;i<k;i++)
    {
        connect(bt[i],&QPushButton::clicked,this,[=](){
            bt[i]->setStyleSheet(" background-color: red ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");
            QChar mc=corpuri.at(i);
            nrCorp=mc.toLatin1();
            sali="A308  A309  A310";
            corpBut="OK";
            for(int j=0;j<k;j++)
                if(j!=i)
                {

                        bt[j]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");

                }
        });

    }



    QPushButton *showw=new QPushButton("AFISEAZA SALI",page);
    showw->setGeometry(1300,200,150,50);
    showw->setStyleSheet(" background-color: grey ;border: 2px solid black; color:black; font-size: 15px; ");
    QLabel *text3=new QLabel ("",page);
     QLabel *text4=new QLabel ("",page);
     text4->setGeometry(50,500,0,0);
     QLineEdit *cauta =new QLineEdit (page);
      QPushButton *cb=new QPushButton("",page);
      cb->setGeometry(900,500,0,0);
       cauta->setGeometry(900,200,0,0);
        QLabel *mm=new QLabel ("",page);
        cauta->setVisible(false);
        // cauta->clear();
          cb->setVisible(false);
           mm->clear();
           QLabel *text5=new QLabel ("",page);
           text5->setGeometry(50,500,0,0);

      QPushButton *sortare=new QPushButton("",page);
      QPushButton *filtrare=new QPushButton("",page);

      QTextEdit *lista=new QTextEdit(page);
       lista->setGeometry(650,350,0,0);
       QScrollBar *bar=new QScrollBar(page);
       bar->setGeometry(650,350,0,0);
      lista->setReadOnly(true);
      bar->setOrientation(Qt::Vertical);
      lista->setReadOnly(true);
      bar->setOrientation(Qt::Vertical);
      lista->setVisible(false);
      bar->setVisible(false);
      lista->clear();
      sortare->setVisible(false);
      filtrare->setVisible(false);
      bar->setValue(0);
    connect(showw,&QPushButton::clicked,this,[=](){

        lista->setVisible(true);
        bar->setVisible(true);
        sortare->setVisible(true);
        filtrare->setVisible(true);
        text5->clear();
        cauta->setVisible(true);
        cb->setVisible(true);
        mm->clear();

        if(corpBut=="OK")
       {
            for(int j=0;j<k;j++)
               bt[j]->setStyleSheet(" background-color: green ;border: 2px solid white; color:white; font-size: 20px; font-weight: bold;");

            text3->setText("Sali disponibile :  ");
            text3->setStyleSheet("color: white; font-size: 25px; font-family: Times New Roman; font-weight:bold;");
            text3->setGeometry(650,270,200,50);
            text4->setText("Introduceti o sala: ");
            text4->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; font-weight:bold;");
            text4->setGeometry(1100,380,200,50);

             cauta->setGeometry(1100,440,150,30);
             cauta->setPlaceholderText("Enter a room.");
             cb->setText("CAUTA");
             cb->setGeometry(1100,480,50,20);
             cb->setStyleSheet("background-color: grey; border: 2px solid black; color: black;");
             corpBut="NOK";
             sortare->setText("SORTARE");
             sortare->setGeometry(100,400,80,50);
             sortare->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");

             filtrare->setText("FILTRARE");
             filtrare->setGeometry(250,400,80,50);
             filtrare->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");


                       int cod=9; //cod interogare afisare;
                       write(sd,&cod,sizeof(int));

                         cod='C';             //cod interogare pt corpuri;
                         write(sd,&cod,sizeof(int));

                         int lung_rasp=sizeof(char);   ///lungime
                         write(sd,&lung_rasp,sizeof(int));

                           ///numele corpului
                         write(sd,&nrCorp,sizeof(char));

                         lung_rasp=0;
                         read(sd,&lung_rasp,sizeof(int));
                         printf("Am primit lung : %d!\n",lung_rasp);

                         char* arr_corp_sir=new char[lung_rasp];

                         read(sd,arr_corp_sir,lung_rasp);

                         arr_corp_sir[strlen(arr_corp_sir)]='\0';

                         printf("Sir primit: %s!",arr_corp_sir);

                        QString rasp=QString::fromUtf8(arr_corp_sir);



             QString sali;
             int i=1;
             QString sala;
             while(rasp[i]!='\0')
             {
                 if(rasp[i]=='|')
                 {
                     sali=sali+sala+"\n";
                     sala.clear();
                 }
                 else
                     sala+=rasp[i];
                 i++;
             }
             lista->setGeometry(550,330,400,400);
             lista->setText(sali);
             lista->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
            bar->setGeometry(950,330,20,400);
             bar->setStyleSheet("background-color: grey; width: 10px;");

        }
        else
        {
            sortare->setVisible(false);
            filtrare->setVisible(false);
            lista->setVisible(false);
            bar->setVisible(false);
            lista->clear();
            cauta->setVisible(false);
            cb->setVisible(false);
            mm->clear();
            text3->clear();
            text4->clear();
            text5->setText("Selectati un corp.");
            text5->setStyleSheet("color: red; font-size: 20px; font-family: Times New Roman;");
            text5->setGeometry(1300,250,200,50);
        }

    });

    connect(bar,&QScrollBar::valueChanged,lista->verticalScrollBar(),&QScrollBar::setValue);

    connect(cb,&QPushButton::clicked,this,[=](){
         mm->clear();

        QString nume_sala=cauta->text();
        if(nume_sala.isEmpty())
        {
            cauta->clear();
            mm->setText(" Introduceti o sala.");
           mm->setStyleSheet("color: red; font-size: 15px; font-family: Times New Roman; font-weight: bold;");
           mm->setGeometry(1100,500,200,30);
           //raspunsServer="NU";
        }
       else
        {   int cod=1;
            write(sd,&cod,sizeof(int));
            cod='S';
            write(sd,&cod,sizeof(int));
            int lungime_sala=nume_sala.length()+1;
             write(sd,&lungime_sala,sizeof(int));
          QByteArray ba=nume_sala.toUtf8();
          char*raspp=ba.data();
          write(sd,raspp,lungime_sala);
          int lungime_rasp=0;
          read(sd,&lungime_rasp,sizeof(int));
          char* sir_rasp=new char[lungime_rasp];
          read(sd,sir_rasp,lungime_rasp);

          sir_rasp[strlen(sir_rasp)]='\0';

          raspunsServer=QString::fromUtf8(sir_rasp);

             if(strstr(sir_rasp,"NU"))//if(strstr(rasp,"NU"))
            {
                 cauta->clear();
                 mm->setText("Nu s-a putut gasi sala.");
                mm->setStyleSheet("color: red; font-size: 15px; font-family: Times New Roman; font-weight: bold;");
                mm->setGeometry(1100,500,200,30);
            }
            else
            {
                mm->clear();
                 cauta->clear();
               // cb->setVisible(false);
               // cauta->setVisible(false);
                cautaSala(raspunsServer);//rasp
            }
        }
    });


    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
        bar->setValue(0);
        sortare->setVisible(false);
        filtrare->setVisible(false);
        lista->setVisible(false);
        bar->setVisible(false);
        lista->clear();
         text5->clear();
         cauta->clear();
        cauta->setVisible(false);
        cb->setVisible(false);
         mm->clear();
        text3->clear();
        text4->clear();
       showVizitMeniu();
    });
    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
        bar->setValue(0);
        sortare->setVisible(false);
        filtrare->setVisible(false);
        lista->setVisible(false);
        bar->setVisible(false);
        lista->clear();
         text5->clear();
         cb->setVisible(false);
         cauta->clear();
        cauta->setVisible(false);
         mm->clear();
        text4->clear();
         text3->clear();
         int cod=-1;
         write(sd,&cod,sizeof(int));
         exit(EXIT_SUCCESS);
    });
    return page;
}



char*numeFac;
char*numeFacServer;
 QString nume_in_buton;
 QString nume_facultate;
QWidget *MainWindow::createNewFacPage()
{


    QWidget *page=new QWidget(this);
    page->setObjectName("client");
    page->setStyleSheet("QWidget#client{background-color: darkblue ; border: 3px solid white;}");

    QLabel *text2=new QLabel ("         UNIVERSITATEA \nALEXANDRU IOAN CUZA \n                  DIN IASI",page);
    text2->setStyleSheet("color: white; font-size: 18px; font-family: Times New Roman; font-weight: bold;");
    text2->setGeometry(720,660,900,300);

    QLabel *label=new QLabel(page);
    QPixmap image("/home/florea/PR_RETELE/client/uaic.png");
    QPixmap imagee=image.scaled(100,100);
    label->setPixmap(imagee);
    label->move(600,760);

    QLabel *text=new QLabel ("CAUTA FACULTATE",page);
    text->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; ");
    text->setGeometry(650,30,500,50);

    QLabel *textt=new QLabel ("Selectati o facultate:",page);
    textt->setStyleSheet("color: white; font-size: 30px; font-family: Times New Roman; font-weight: bold;");
    textt->setGeometry(50,150,300,40);



    int cod=7; //cod interogare afisare;
    write(sd,&cod,sizeof(int));

      cod='F';             //cod interogare pt corpuri;
      write(sd,&cod,sizeof(int));

      int lung_rasp;  ///lungime

      read(sd,&lung_rasp,sizeof(int));
      printf("Am primit lung : %d!\n",lung_rasp);

      char* arr_corp_sir=new char[lung_rasp];

      read(sd,arr_corp_sir,lung_rasp);

      arr_corp_sir[strlen(arr_corp_sir)]='\0';

      printf("Sir primit: %s!",arr_corp_sir);

     QString f=QString::fromUtf8(arr_corp_sir);




    int i=1;
    QString fac;
    int k=0;
    int x,y,z,t;
    x=350;
    y=150;
    z=150;
    t=30;
    QPushButton *bt[10];
    int b=0;
    QString ff[10];


    while(f[i]!='\0')
    {
        if(f[i]!="|")
            fac[k++]=f[i];
        else
        {
            bt[b]=new QPushButton("FACULTATEA DE\n "+fac,page);
            bt[b]->setGeometry(x,y,z,t);
            bt[b]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
            ff[b]=fac;
            b++;
            if(x>1000)
            {
                x=350;
                y+=50;
            }
            else
               x+=175;
            fac.clear();
            k=0;
        }
        i++;
    }

    QPushButton *cauta=new QPushButton("CAUTA",page);
    cauta->setGeometry(1300,150,100,40);
    cauta->setStyleSheet("background-color:grey; border: 2px solid black; color: black; font-size: 15px; font-weight:bold;");




    for(int i=0;i<b;i++)
    {
        connect(bt[i],&QPushButton::clicked,this,[=](){
             bt[i]->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
               nume_in_buton.clear();
              nume_in_buton=ff[i];
              // qDebug()<<"\n[BUTON CAUTA FACULTATE]: Numele facultatii este: "<<nume_facultate<<endl;
             sel=i;
             set="ok";
             for(int q=0;q<b;q++)
             {
                 if(q!=i)
                     bt[q]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
             }

        });
    }

    QPushButton *ts=new QPushButton("",page);
    QPushButton *tc=new QPushButton("",page);
    QString sss;
     ts->setVisible(false);
    QTextEdit *lista1=new QTextEdit(page);
     QScrollBar *bar1=new QScrollBar(page);
    bar1->setOrientation(Qt::Vertical);
    lista1->setVisible(false);
    bar1->setVisible(false);
    lista1->clear();
    bar1->setValue(0);

    QTextEdit *lista2=new QTextEdit(page);
     QScrollBar *bar2=new QScrollBar(page);
    bar2->setOrientation(Qt::Vertical);
    lista2->setVisible(false);
    bar2->setVisible(false);
    lista2->clear();
    bar2->setValue(0);

    QPushButton *sortare1=new QPushButton("",page);
    QPushButton *filtrare1=new QPushButton("",page);
    sortare1->setVisible(false);
    filtrare1->setVisible(false);

    QPushButton *sortare2=new QPushButton("",page);
    QPushButton *filtrare2=new QPushButton("",page);
    sortare2->setVisible(false);
    filtrare2->setVisible(false);

    lista2->setVisible(false);
    bar2->setVisible(false);
    sortare2->setVisible(false);
    filtrare2->setVisible(false);
    tc->setVisible(false);

    QLabel *err=new QLabel("",page);
    err->setVisible(false);
    connect(cauta,&QPushButton::clicked,this,[=](){
           if(set=="ok")
           {
               nume_facultate.clear();
               nume_facultate=nume_in_buton;
               //qDebug()<<"\n[BUTON CAUTA SALI]: Numele facultatii este: "<<nume_facultate<<endl;
                err->setVisible(false);
               tc->setVisible(true);
                ts->setVisible(true);

                lista2->setVisible(false);
                bar2->setVisible(false);
                sortare2->setVisible(false);
                filtrare2->setVisible(false);
                lista1->clear();
                lista2->clear();
                bar1->setValue(0);
                 bar2->setValue(0);

                lista1->setVisible(false);
                bar1->setVisible(false);
                sortare1->setVisible(false);
                filtrare1->setVisible(false);
              bt[sel]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
              ts->setGeometry(400,280,180,50);
              ts->setText("AFISATI TOATE SALILE >>");
              ts->setStyleSheet("background-color:grey; color:black; border:2px solid black; font-size:12px; font-weight:bold; ");
              tc->setGeometry(850,280,180,50);
              tc->setText("AFISATI TOATE CORPURILE >>");
              tc->setStyleSheet("background-color:grey; color:black; border:2px solid black; font-size:12px; font-weight:bold; ");
               set="nok";
           }
           else
           {
               tc->setVisible(false);
                ts->setVisible(false);
              err->setVisible(true);
              err->setText("Selectati o facultate");
              err->setGeometry(1280,210,200,50);
              err->setStyleSheet("color:red; font-size: 20px;");

              lista2->setVisible(false);
              bar2->setVisible(false);
              sortare2->setVisible(false);
              filtrare2->setVisible(false);
              lista1->clear();
              lista2->clear();
              bar1->setValue(0);
               bar2->setValue(0);

              lista1->setVisible(false);
              bar1->setVisible(false);
              sortare1->setVisible(false);
              filtrare1->setVisible(false);
           }

        });

    connect(ts,&QPushButton::clicked,this,[=](){
          //delete [] numeFacServer;
          numeFacServer=new char[nume_facultate.length()];
          numeFacServer=nume_facultate.toUtf8().data();

        int cod=8; //cod interogare afisare;
        write(sd,&cod,sizeof(int));

          cod='S';             //cod interogare pt corpuri;
          write(sd,&cod,sizeof(int));

          int lung_rasp=nume_facultate.length();   ///lungime
          write(sd,&lung_rasp,sizeof(int));

            ///numele facultatii
          write(sd,numeFacServer,lung_rasp);
          printf("\nTrimit facultatea: %s.\n",numeFacServer);
          memset(numeFacServer,0,strlen(numeFacServer));
          lung_rasp=0;
          read(sd,&lung_rasp,sizeof(int));
          printf("Am primit lung : %d!\n",lung_rasp);

          char* arr_corp_sir=new char[lung_rasp];

          read(sd,arr_corp_sir,lung_rasp);

          arr_corp_sir[strlen(arr_corp_sir)]='\0';

          printf("Sir primit: %s!",arr_corp_sir);



         QString rasp=QString::fromUtf8(arr_corp_sir);


         lista1->setVisible(true);
         bar1->setVisible(true);
         sortare1->setVisible(true);
         filtrare1->setVisible(true);

         lista2->setVisible(false);
         bar2->setVisible(false);
         sortare2->setVisible(false);
         filtrare2->setVisible(false);
        lista1->setGeometry(300,350,400,400);
        QString sali;
        int i=1;
        QString sala;
        while(rasp[i]!='\0')
        {
            if(rasp[i]=='|')
            {
                sali=sali+sala+"\n";
                sala.clear();
            }
            else
                sala+=rasp[i];
            i++;
        }
        lista1->setText(sali);
        lista1->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
       bar1->setGeometry(700,350,20,400);
        bar1->setStyleSheet("background-color: grey; width: 10px;");
        sortare1->setText("SORTARE");
        sortare1->setGeometry(30,400,80,50);
        sortare1->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");
        bar2->setValue(0);
        lista2->clear();
        filtrare1->setText("FILTRARE");
        filtrare1->setGeometry(200,400,80,50);
        filtrare1->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");


    });


    connect(tc,&QPushButton::clicked,this,[=](){

        numeFacServer=new char[nume_facultate.length()];
        numeFacServer=nume_facultate.toUtf8().data();

      int cod=8; //cod interogare afisare;
      write(sd,&cod,sizeof(int));

        cod='C';             //cod interogare pt corpuri;
        write(sd,&cod,sizeof(int));

        int lung_rasp=nume_facultate.length();   ///lungime
        write(sd,&lung_rasp,sizeof(int));

          ///numele facultatii
        write(sd,numeFacServer,lung_rasp);
        printf("\nTrimit facultatea: %s.\n",numeFacServer);
        memset(numeFacServer,0,strlen(numeFacServer));
        lung_rasp=0;
        read(sd,&lung_rasp,sizeof(int));
        printf("Am primit lung : %d!\n",lung_rasp);

        char* arr_corp_sir=new char[lung_rasp];

        read(sd,arr_corp_sir,lung_rasp);

        arr_corp_sir[strlen(arr_corp_sir)]='\0';

        printf("Sir primit: %s!",arr_corp_sir);




         QString rasp=QString::fromUtf8(arr_corp_sir);


        lista2->setVisible(true);
        bar2->setVisible(true);
        sortare2->setVisible(true);
        filtrare2->setVisible(true);
        bar1->setValue(0);
        lista1->clear();

        lista1->setVisible(false);
        bar1->setVisible(false);
        sortare1->setVisible(false);
        filtrare1->setVisible(false);

        lista2->setGeometry(800,350,400,400);
        QString corpuri;
        int i=1;
        QString corp;
        while(rasp[i]!='\0')
        {
            if(rasp[i]=='|')
            {
                corpuri=corpuri+corp+"\n";
                corp.clear();
            }
            else
                corp+=rasp[i];
            i++;
        }
        lista2->setText(corpuri);
        lista2->setStyleSheet("background-color: white; color: black; border: 2px solid grey; font-size: 20px ;");
       bar2->setGeometry(1200,350,20,400);
        bar2->setStyleSheet("background-color: grey; width: 10px;");



        sortare2->setText("SORTARE");
        sortare2->setGeometry(1230,400,80,50);
        sortare2->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");

        filtrare2->setText("FILTRARE");
        filtrare2->setGeometry(1400,400,80,50);
        filtrare2->setStyleSheet("background-color: grey; border: 2px solid white; color: black;font-weight:bold;");


    });


   connect(bar1,&QScrollBar::valueChanged,lista1->verticalScrollBar(),&QScrollBar::setValue);
connect(bar2,&QScrollBar::valueChanged,lista2->verticalScrollBar(),&QScrollBar::setValue);
    QPushButton *butonBack=new QPushButton("<<  BACK",page);
    butonBack->setGeometry(50,50,150,50);
    butonBack->setStyleSheet(" background-color: lightblue ;border: 2px solid white; font-size: 30px ; color: white; font-weight: bold;");
    connect(butonBack,&QPushButton::clicked,this,[=]()
    {
         for(int i=0;i<b;i++)
         {
              bt[i]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
         }

         tc->setVisible(false);
          ts->setVisible(false);

         lista2->setVisible(false);
         bar2->setVisible(false);
         sortare2->setVisible(false);
         filtrare2->setVisible(false);
         lista1->clear();
         lista2->clear();
         bar1->setValue(0);
          bar2->setValue(0);

         lista1->setVisible(false);
         bar1->setVisible(false);
         sortare1->setVisible(false);
         filtrare1->setVisible(false);

          err->setVisible(false);
      showVizitMeniu();
    });
    QPushButton *discon=new QPushButton("DECONECTARE",page);
    discon->setGeometry(1250,780,150,50);
    discon->setStyleSheet(" background-color: red ;border: 2px solid white; font-size: 15px ; color: white; font-weight: bold;");
    connect(discon,&QPushButton::clicked,this,[=]()
    {
        for(int i=0;i<b;i++)
        {
             bt[i]->setStyleSheet(" background-color: #B0C4DE ;border: 2px solid white; font-size: 10px ; color: black; font-weight: bold; ");
        }

        tc->setVisible(false);
         ts->setVisible(false);
         err->setVisible(false);

        lista2->setVisible(false);
        bar2->setVisible(false);
        sortare2->setVisible(false);
        filtrare2->setVisible(false);
        lista1->clear();
        lista2->clear();
        bar1->setValue(0);
         bar2->setValue(0);

        lista1->setVisible(false);
        bar1->setVisible(false);
        sortare1->setVisible(false);
        filtrare1->setVisible(false);
        int cod=-1;
        write(sd,&cod,sizeof(int));
        exit(EXIT_SUCCESS);
    });
    return page;
}

void MainWindow::cautaSala(QString s){

    fereastraSala *w=new fereastraSala(this);
    w->setWindowTitle("EXPLORARE SALA");
    w->setObjectName("SALA");
    w->setFixedSize(500,500);
    w->setStyleSheet("QWidget#SALA { border: 2px solid white ;}");
    w->tab->setGeometry(0,0,500,500);

    QString sala,fac,corp,tip,cap,poza,proprietar;
    int i=1,k=0,x=0,y=0,z=0,p=0,u=0;
    while(s[i]!='|' && i<s.length())
    {
        sala[k++]=s[i++];
    }
    i++;
    while(s[i]!='|'  && i<s.length())
    {
        fac[x++]=s[i++];
    }
    std::string stdString = fac.toStdString();
    i++;

    corp[0]=s[i];
    corp[1]='\0';
    i++; i++;
    while(s[i]!='|'  && i<s.length())
    {
         cap[y++]=s[i++];
    }
    stdString = cap.toStdString();
    i++;
    while(s[i]!='|'  && i<s.length())
    {

         tip[z++]=s[i++];
    }
    stdString = tip.toStdString();
    i++;
    while(s[i]!='|'  && i<s.length())
    {
        proprietar[u++]=s[i++];
    }
    i++;
    while(s[i]!='|'  && i<s.length())
    {
        poza[p++]=s[i++];
    }
    poza[p]='\0';
     qDebug()<<"\nPoza 1: "<<poza<<" \n";
    int lungime_poza=0;
    read(sd,&lungime_poza,sizeof(int));
    printf("\n[POZA]: Dimensiune: %d\n",lungime_poza);
     char *nume_poza;
     nume_poza=poza.toUtf8().data();
     nume_poza[strlen(nume_poza)]='\0';

     printf("\n[POZA]: Nume: %s\n",nume_poza);

     FILE *image_ptr=fopen(nume_poza,"wb");
     char *buffer_poza=new char [lungime_poza];
     int bytes_read=0;
     while(bytes_read<lungime_poza)
     {
         long chunk_size=read(sd,buffer_poza,sizeof(buffer_poza));
         if(chunk_size==-1)
         {
             printf("\nEroare primire imagine\n");
             ::close(sd);
             exit(0);
         }
         fwrite(buffer_poza,1,chunk_size,image_ptr);
         bytes_read+=chunk_size;
     }

     if (bytes_read < 0) {
         perror("Error reading file");
         delete[] buffer_poza;
         ::close(MainWindow::sd);
         exit(EXIT_FAILURE);
     }

     printf("[POZA]: Poza a fost primita cu succes!");
     fclose(image_ptr);


   // QString adresa_poza="/home/florea/PR_RETELE/client/";
   // adresa_poza+=poza;
   // poza=adresa_poza;

   // qDebug()<<"\nPoza primita este: "<<poza<<endl;

    QLabel *titlu=new QLabel ("Sala "+sala,w->tab->widget(0));
    titlu->setStyleSheet("color: white; font-size: 30px; font-weight: bold;font-family: Times New Roman; ");
    titlu->setGeometry(160,2,300,200);

    QLabel *cont=new QLabel ("> FACULTATEA:  "+fac+"\n\n> CORP:  "+corp+"\n\n> TIP SALA:  "+tip+"\n\n> CAPACITATE:  "+cap+"\n\n>PROPRIETAR: "+proprietar,w->tab->widget(0));
    cont->setStyleSheet("color: white; font-size: 20px; font-family: Times New Roman; ");
    cont->setGeometry(30,150,500,300);

    QLabel *label=new QLabel(w->tab->widget(1));

    char cwd[1024];
    if(getcwd(cwd,sizeof(cwd))!=NULL)
    {
        printf("[POZA]: Director curent:%s\n\n",cwd );
    }
    else
    {
      printf("Eroare la director curent..\n");
    }

    int lungime_cale_imagine=strlen(cwd)+strlen(nume_poza);
    char *cale=new char[lungime_cale_imagine+64];
     memset(cale,0,lungime_cale_imagine+64);
    strcpy(cale,cwd);
    strcat(cale,"/");
    char *nume_poza_final=poza.toUtf8().data();
     printf("Nume poza: %s\n",nume_poza_final);
     //int capat_cale=strlen(cale);
     int h=strlen(nume_poza_final);
     for(int i=0;i<h;i++)
     {
         printf("%c\n",nume_poza_final[i]);
         cale[strlen(cwd)+1+i]=nume_poza_final[i];
     }
     cale[strlen(cale)]='\0';
     printf("Cale imagine: %s\n",cale);
     poza.clear();
     poza=QString::fromUtf8(cale);
     poza[poza.length()-1]='\0';

     qDebug()<<"\n[POZA]: Adresa si numele pozei sunt: "<<cale<<".\n";
    QPixmap image(cale);
    QPixmap imagee=image.scaled(450,400);
    label->setPixmap(imagee);
    label->move(25,25);

    w->tab->show();
    w->show();
}

