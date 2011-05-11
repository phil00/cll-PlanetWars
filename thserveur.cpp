#include "thserveur.h"

thServeur::thServeur(QObject *parent) :
    QThread(parent)
{
    connect(sockserveur, SIGNAL(ReadyRead()), this, SLOT(ReadyToRead()));
}

void thServeur::run()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
    if(sockServeur->waitForConnected())
    {

    }
}

void thServeur::on_time_newTime()
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
        p->FromByteArray(sockServeur->read(124));
        emit NewMessage(p);
    }
}

void on_SendMessage(QByteArray send)
{

}
