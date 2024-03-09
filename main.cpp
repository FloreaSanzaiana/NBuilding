#include "mainwindow.h"

#include <QApplication>

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

int port;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    struct sockaddr_in server;


    if(argc != 3)
    {
        printf ("Sintaxa: %s <adresa_server> <port>\n",argv[0]);
        return -1;
    }

    port = atoi (argv[2]);
    if((w.sd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("Eroare la socket().\n");
        return errno;
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_port=htons(port);

    if(connect(w.sd,(struct sockaddr *) &server, sizeof(struct sockaddr))==-1)
    {
        perror("[client]Eroare la connect().\n");
        return errno;
    }
    w.setWindowTitle("NBuilding");
    w.setObjectName("NBuilding");
    w.setFixedSize(1500,900);
   // w.setStyleSheet("QWidget#NBuilding { border: 5px solid white ;}");
    w.show();
    return a.exec();
}


/*



*/
