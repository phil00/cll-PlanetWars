#include "paquet.h"

Paquet::Paquet(int Message, int Player, int Data[30])
{
    m_Message = Message;
    m_Player = Player;
    m_Data = Data;
}
QByteArray Paquet::ToByteArray()
{

}
void Paquet::FromByteArray(QByteArray un)
{

}
