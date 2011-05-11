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
    sockServeur->write(p->ToByteArray());
    sockServeur->waitForBytesWritten();
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

void thServeur::sl_Start()
{

}
