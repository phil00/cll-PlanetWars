#include "paquet.h"

Paquet::Paquet(short Message, short Player, int Data[30])
{
    m_Message = Message;
    m_Player = Player;
    for(int i = 0; i < 30; i++)
    {
        m_Data[i] = Data[i];
    }
}
QByteArray Paquet::ToByteArray()
{
    char temp;
    QByteArray unBA;
    temp = (char)(255 & m_Message);
    unBA.append(temp);
    temp = (char)(m_Message >> 8);
    unBA.append(temp);
    temp = (char)(255 & m_Player);
    unBA.append(temp);
    temp = (char)(m_Player >> 8);
    unBA.append(temp);
    for(int i = 0; i < 30; i++)
    {
        temp = (char)(255 & m_Data[i]);
        unBA.append(temp);
        temp = (char)((65280 & m_Data[i]) >> 8);
        unBA.append(temp);
        temp = (char)((16711680 & m_Data[i]) >> 16);
        unBA.append(temp);
        temp = (char)(m_Data[i] >> 24);
        unBA.append(temp);
    }
    return unBA;
}
void Paquet::FromByteArray(QByteArray unBA)
{
    m_Message = unBA[0] | (unBA[1] << 8);
    m_Player = unBA[2] | (unBA[3] << 8);
    int j = 0;
    for(int i = 0; i < 30; i++)
    {
        for(int k = 0; k < 4; k++)
        {
            m_Data[i] |= (unBA[j] << 8*k);
            j++;
        }
    }
}
