#include "thserveur.h"

thServeur::thServeur(QObject *parent) :
    QThread(parent)
{

}

void thServeur::run()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
    if(sockServeur->ConnectedState == 3)
    {
    }
}

void thServeur::on_time_newTime()
{
    Paquet *p = new Paquet(1, 255, new int[30] {1});
    sockServeur->write(p->ToByteArray());
}
