#include "planet.h"

Planet::Planet()
{
    //QPoint Location;
    //int Population;
    //int Player;
    //int PopulationGrowth;
    //bool Focus;
    TickTillLastPop=100;
}
void Planet::initialize(int Owner, int Quadrant, QList<Planet> p)
{
    TickTillLastPop=100;
    int i =0;
    Player=Owner;
    bool Collision = false;
    //PopulationGrowth = PlanetSize;
    int sizex = 512;
    int sizey = 384;
    QPoint temp;
    int tempsize;
    if(Quadrant!=1)
    {
        sizex = 256;
        sizey = 192;
    }
    if(Owner==1)
    {
        PlanetImg.load("PB.png",0);
    }
    else
    {
        if(Owner ==2)
        {
            PlanetImg.load("PR.png",0);
        }
        else
        {
            PlanetImg.load("PG.png",0);
        }
    }
    do
    {
        Collision = false;
        temp = QPoint(qrand()%sizex,qrand()%sizey);
        PopulationGrowth = 15+qrand()%50;
        tempsize = PopulationGrowth;
        Location=QRect(temp,QSize(tempsize,tempsize));

        while(i<PlanetCount)
        {
            if(CheckPlanetToPlanetCollision(PlanetArray[i]))
            {
                Collision = true;
            }
            i++;
        }
        PlanetNumber=i;
    }while(Collision);
    Population= PopulationGrowth;//A checker pour des erreur en debug plustard
    PFocus = false;
}

void Planet::MirrorPlanet(Planet SomePlanet,int Quadrant, int PlanetCount)
{
    TickTillLastPop=100;
    int placex = 1024;
    int placey = 768;
    Player=2;
    if(Quadrant!=1)
    {
        if(Quadrant==2)
        {
            if(SomePlanet.Player==1)
            {
                PlanetImg.load("PR.png",0);
                Player=2;
            }
            placex = 1024;
            placey = SomePlanet.Location.y()*2;
             Player=2;

        }
        else
        if(Quadrant==3)
        {
            if(SomePlanet.Player==1)
            {
                PlanetImg.load("PR.png",0);//change for other color later
                Player=3;
            }
            placex = SomePlanet.Location.x()*2;
            placey = 768;


        }
        else
        if(Quadrant==4)
        {
            if(SomePlanet.Player==1)
            {
                PlanetImg.load("PR.png",0);
                Player=4;
            }
            placex = 1024;
            placey = 768;
        }
    }
    else
    {
        //1 Quadrant means its a 1v1 game, so generate for player 2
        if(SomePlanet.Player==1)
        {
            PlanetImg.load("PR.png",0);
            Player=2;
        }
    }

    if(SomePlanet.Player == 5)
    {
        Player=5;
        PlanetImg.load("PG.png",0);
    }
    Location = QRect(QPoint(placex-SomePlanet.Location.x(),placey-SomePlanet.Location.y()),QSize(SomePlanet.Location.size()));
    Player=SomePlanet.Player;
    PopulationGrowth=PopulationGrowth;
    Population =SomePlanet.Population;
    PlanetNumber = SomePlanet.PlanetNumber+PlanetCount;
    PFocus = false;

}

bool Planet::CheckPlanetToPlanetCollision(Planet planet2)
{
  return Location.intersects(planet2.Location);
}

void Planet::PlanetTick(int tickAmmount)
{
    TickTillLastPop-=tickAmmount;
    if(TickTillLastPop <= PopulationGrowth)
    {
        Population += 1;
        TickTillLastPop = 100;
    }
}
