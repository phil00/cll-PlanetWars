#ifndef THSERVEUR_H
#define THSERVEUR_H

#include <QThread>
#include <QtGui>
#include <QtNetwork>

class thServeur : public QThread
{
    Q_OBJECT
public:
    explicit thServeur(QObject *parent = 0);
    QTcpSocket *sockServeur;

signals:

protected:
    void run();

public slots:
    void on_time_newTime();
};

#endif // THSERVEUR_H
