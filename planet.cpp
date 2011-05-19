#include "planet.h"

Planet::Planet()
{
    m_TickTillLastPop=100;
}

void Planet::initialize(int Owner, int Quadrant,QList<Planet> PlanetArray)
{
    m_TickTillLastPop=100;
    int i =0;
    m_Player=Owner;
    bool Collision = false;
    int sizex = 480;
    int sizey = 770;
    QPoint temp;
    int tempsize;
    if(Quadrant!=1)
    {
        sizex = 512;
        sizey = 384;
    }
    do
    {
        if(m_Player!=1)
        {
            temp = QPoint(qrand()%sizex,qrand()%sizey);
            m_PopulationGrowth = 15+qrand()%50;
        }

        else
        {
            temp = QPoint(qrand()%(sizex-40),qrand()%(sizey-40));
            m_PopulationGrowth = 20+qrand()%45;
        }
        tempsize = m_PopulationGrowth;
        m_Location=QRect(temp,QSize(tempsize,tempsize));
        m_GenerationRect = QRect(QPoint(temp.x()-m_Location.width()/2,temp.y()-m_Location.height()/2),QSize(m_Location.width()*2,m_Location.height()*2));
        i=0;
        while(i<PlanetArray.length())
        {
           Collision = CheckPlanetToPlanetCollision(PlanetArray[i]);
           i++;
        }
        m_PlanetNumber=i;

    }while(Collision);
    m_Population = m_PopulationGrowth;
    m_PFocus = false;
}

void Planet::MirrorPlanet(Planet SomePlanet,int Quadrant, int PlanetCount)
{
    m_TickTillLastPop=100;
    int placex = 1024;
    int placey = 768;
    if(Quadrant!=1)
    {
        if(Quadrant==2)
        {
            if(SomePlanet.m_Player==1)
            {
                m_Player=2;
            }
            placex = 1024;
            placey = SomePlanet.m_Location.y()*2;
            m_Player=2;
        }
        else
        if(Quadrant==3)
        {
            if(SomePlanet.m_Player==1)
            {
                m_Player=3;
            }
            placex = SomePlanet.m_Location.x()*2;
            placey = 768;


        }
        else
        if(Quadrant==4)
        {
            if(SomePlanet.m_Player==1)
            {
                m_Player=4;
            }
            placex = 1024;
            placey = 768;
        }
    }
    else
    {
        //1 Quadrant means its a 1v1 game, so generate for player 2
        if(SomePlanet.m_Player==1)
        {
            m_Player=2;
        }
    }

    if(SomePlanet.m_Player == 5)
    {
        m_Player=5;
    }
    m_Location = QRect(QPoint(placex-SomePlanet.m_Location.x()-SomePlanet.m_Location.width(),placey-SomePlanet.m_Location.y()),QSize(SomePlanet.m_Location.size()));
    m_Player=SomePlanet.m_Player;
    m_PopulationGrowth=SomePlanet.m_PopulationGrowth;
    m_Population =SomePlanet.m_Population;
    m_PlanetNumber = SomePlanet.m_PlanetNumber+PlanetCount;
    m_PFocus = false;

}

bool Planet::CheckPlanetToPlanetCollision(Planet planet2)
{
    QRect temp = QRect(QPoint(0,0),QSize(1100,900));
    if(m_GenerationRect.intersects(planet2.m_GenerationRect))
    {
        return true;
    }
    else
    {
    if(m_GenerationRect.intersects(temp))
    {
        return false;
    }
    else
    {
        return true;
    }
    }

}

void Planet::PlanetTick(int tickAmmount)
{
    m_TickTillLastPop-=tickAmmount;
    if(m_TickTillLastPop <= m_PopulationGrowth)
    {
        m_Population += 1;
        m_TickTillLastPop = 100;
    }
}

void Planet::initializeFromint(int W[])
{
     m_PFocus = false;
     m_Player = W[0];
     m_PopulationGrowth = W[1];
     m_Population = W[2];
     m_Location = QRect(QPoint(W[3],W[4]),QSize(W[5],W[6]));
}

int * Planet::Toint()
{
    m_pl[0] = m_Player;
    m_pl[1] = m_PopulationGrowth;
    m_pl[2] = m_Population;
    m_pl[3] = m_Location.topLeft().rx();
    m_pl[4] = m_Location.topLeft().ry();
    m_pl[5] = m_Location.width();
    m_pl[6] = m_Location.height();
    return m_pl;
}
