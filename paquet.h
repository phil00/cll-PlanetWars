#ifndef PAQUET_H
#define PAQUET_H

#include <QtGui>

class Paquet
{
public:
    Paquet(short Message, short Player, int Data[]);
    short m_Message;
    short m_Player;
    int m_Data[30];
    public slots:
    QByteArray ToByteArray();
    void FromByteArray(QByteArray unBA);
};

#endif // PAQUET_H
