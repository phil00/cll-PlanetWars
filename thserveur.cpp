#include "thserveur.h"

thServeur::thServeur(QObject *parent) :
    QThread(parent)
{
    m_sockServeur = new QTcpSocket();
    connect(m_sockServeur, SIGNAL(readyRead()), this, SLOT(ReadyToRead()));
}

void thServeur::run()
{
}

void thServeur::sl_time_newTime()
{
    int data[30];
    data[0] = 1;
    m_p = new Paquet(1, 255, data);
    sl_SendMessage(m_p->ToByteArray());
}

void thServeur::ReadyToRead()
{
    while(m_sockServeur->bytesAvailable())
    {
        emit NewMessage(m_sockServeur->read(124));
    }
}

void thServeur::sl_SendMessage(QByteArray send)
{
    m_sockServeur->write(send);
    m_sockServeur->waitForBytesWritten();
}

void thServeur::sl_Start(QList<Planet> p, short nbP)
{
    int * pl;
    Paquet *pk;
    for(int i = 0; i < p.length(); i++)
    {
        pl = p[i].Toint();
        pk = new Paquet(2, nbP, pl);
        sl_SendMessage(pk->ToByteArray());
    }
}

void thServeur::sl_Stop()
{
    m_sockServeur->disconnectFromHost();
    m_sockServeur->waitForDisconnected();
}
