#ifndef PAQUET_H
#define PAQUET_H

#include <QtGui>

class Paquet
{
public:
    Paquet(int Message, int Player, int Data[]);
    short m_Message;
    short m_Player;
    int m_Data[30];
    public slots:
    QByteArray ToByteArray();
    void FromByteArray(QByteArray un);
};

#endif // PAQUET_H
