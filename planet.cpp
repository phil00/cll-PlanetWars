#include "planet.h"

Planet::Planet()
{
    TickTillLastPop=100;
}

void Planet::initialize(int Owner, int Quadrant,QList<Planet> PlanetArray)
{
    TickTillLastPop=100;
    int i =0;
    Player=Owner;
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
        if(Player!=1)
        {
            temp = QPoint(qrand()%sizex,qrand()%sizey);
            PopulationGrowth = 15+qrand()%50;
        }

        else
        {
            temp = QPoint(qrand()%(sizex-40),qrand()%(sizey-40));
            PopulationGrowth = 20+qrand()%45;
        }
        tempsize = PopulationGrowth;
        Location=QRect(temp,QSize(tempsize,tempsize));
        GenerationRect = QRect(QPoint(temp.x()-Location.width()/2,temp.y()-Location.height()/2),QSize(Location.width()*2,Location.height()*2));
        i=0;
        while(i<PlanetArray.length())
        {
           Collision = CheckPlanetToPlanetCollision(PlanetArray[i]);
           i++;
        }
        PlanetNumber=i;

    }while(Collision);
    Population= PopulationGrowth;
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
    Location = QRect(QPoint(placex-SomePlanet.Location.x()-SomePlanet.Location.width(),placey-SomePlanet.Location.y()),QSize(SomePlanet.Location.size()));
    Player=SomePlanet.Player;
    PopulationGrowth=PopulationGrowth;
    Population =SomePlanet.Population;
    PlanetNumber = SomePlanet.PlanetNumber+PlanetCount;
    PFocus = false;
}

bool Planet::CheckPlanetToPlanetCollision(Planet planet2)
{
    QRect temp = QRect(QPoint(0,0),QSize(1100,900));
    if(GenerationRect.intersects(planet2.GenerationRect))
    {
        return true;
    }
    else
    {
    if(GenerationRect.intersects(temp))
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
    TickTillLastPop-=tickAmmount;
    if(TickTillLastPop <= PopulationGrowth)
    {
    Population += 1;
    TickTillLastPop = 100;
    }
}

void Planet::initializeFromint(int W[])
{
     PFocus = false;
     Player = W[0];
     PopulationGrowth = W[1];
     Population = W[2];
     Location = QRect(QPoint(W[3],W[4]),QSize(W[5],W[6]));
}

int * Planet::Toint()
{
    pl[0] = Player;
    pl[1] = PopulationGrowth;
    pl[2] = Population;
    pl[3] = Location.topLeft().rx();
    pl[4] = Location.topLeft().ry();
    pl[5] = Location.width();
    pl[6] = Location.height();
    return pl;
}
