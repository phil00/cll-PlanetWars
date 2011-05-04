#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#include <QMainWindow>
#include <thserveur.h>
#include <QtGui>
#include <QtNetwork>

namespace Ui {
    class ServerMain;
}

class ServerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerMain(QWidget *parent = 0);
    ~ServerMain();

private slots:
    void on_btnStartStop_clicked();
    void on_time_TimeOut();
    void on_TcpServ_NewConnection();
    void on_pushButton_clicked();

private:
    Ui::ServerMain *ui;
    thServeur *m_thServeur;
    QTimer* time;
    QTcpServer *TcpServ;

signals:
     void newTime();
};

#endif // SERVERMAIN_H
