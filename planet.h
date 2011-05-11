#ifndef PLANET_H
#define PLANET_H

#include <QObject>
#include <QtGui>

class Planet
{
    //Q_OBJECT
public:
    explicit Planet();
    QRect Location;
    int Population;
    int PlanetNumber;
    int Player;
    int PopulationGrowth;
    bool PFocus;
    int TickTillLastPop;
    QImage PlanetImg;
    //populationGrowth va etre utiliser pour determiner la grandeur de la planete.
    //une variable de texture
   //int planettype;
    void initialize(int Owner, int Quadrant, QList<Planet>,int PlanetCount);
    void MirrorPlanet(Planet SomePlanet,int Quadrant,int PlanetCount);
    bool CheckPlanetToPlanetCollision(Planet planet2);
    void PlanetTick(int tickAmmount);
signals:

public slots:


};

#endif // PLANET_H
