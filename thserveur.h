#ifndef THSERVEUR_H
#define THSERVEUR_H

#include <QThread>
#include <QtGui>
#include <QtNetwork>
#include <paquet.h>

class thServeur : public QThread
{
    Q_OBJECT
public:
    explicit thServeur(QObject *parent = 0);
    QTcpSocket *sockServeur;


protected:
    void run();
signals:
    void NewMessage(QByteArray);

public slots:
    void sl_time_newTime();
    void ReadyToRead();
    void sl_SendMessage(QByteArray);
    void sl_Start();

private:
    QTimer thTimer;
    Paquet *p;
};

#endif // THSERVEUR_H
