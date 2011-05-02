#include "thserveur.h"

thServeur::thServeur(QObject *parent) :
    QThread(parent)
{
}

void thServeur::run()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

void thServeur::on_time_newTime()
{
    int tableau[5];
    tableau[0]=3;

   // sockServeur->write();
}
