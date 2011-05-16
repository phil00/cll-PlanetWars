#include "thserveur.h"

thServeur::thServeur(QObject *parent) :
    QThread(parent)
{
    connect(sockServeur, SIGNAL(ReadyRead()), this, SLOT(ReadyToRead()));
}

void thServeur::run()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
    if(sockServeur->waitForConnected())
    {

    }
}

void thServeur::sl_time_newTime()
{
    int data[30];
    data[0] = 1;
    p = new Paquet(1, 255, data);
    sl_SendMessage(p->ToByteArray());
}

void thServeur::ReadyToRead()
{
    while(sockServeur->bytesAvailable())
    {
        emit NewMessage(sockServeur->read(124));
    }
}

void thServeur::sl_SendMessage(QByteArray send)
{
    sockServeur->write(send);
    sockServeur->waitForBytesWritten();
}

void thServeur::sl_Start(QList<Planet> p, short nbP)
{
    int pl[p.length() * 7];
    for(int i = 0; i < p.length(); i++)
    {
        int *ptemp;
        ptemp = p[i].Toint();
        pl[0] = ptemp[0];
        pl[1] = ptemp[1];
        pl[2] = ptemp[2];
        pl[3] = ptemp[3];
        pl[4] = ptemp[4];
        pl[5] = ptemp[5];
        pl[6] = ptemp[6];
    }
    Paquet *pk = new Paquet(2, nbP, pl);
    sl_SendMessage(pk->ToByteArray());
}
