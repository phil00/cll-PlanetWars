#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#include <QMainWindow>
#include <thserveur.h>
#include <QtGui>
#include <QtNetwork>
#include <planet.h>

namespace Ui {
    class ServerMain;
}

class ServerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerMain(QWidget *parent = 0);
    QList<Planet> Planets;
    ~ServerMain();

private slots:
    void on_btnStartStop_clicked();
    void sl_time_TimeOut();
    void sl_TcpServ_NewConnection();
    void on_pushButton_clicked();
    void sl_NewMessage(QByteArray);

private:
    Ui::ServerMain *ui;
    thServeur *m_thServeur;
    QTimer* time;
    QTcpServer *TcpServ;

signals:
     void newTime();
     void SendMessage(QByteArray);
     void NewMessage(QByteArray);
     void Start(QList<Planet>, short);
};

#endif // SERVERMAIN_H
