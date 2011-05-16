#ifndef PLANET_H
#define PLANET_H

#include <QObject>
#include <QtGui>
#include "paquet.h"
class Planet
{
    //Q_OBJECT
public:
    explicit Planet();
    QRect m_Location;
    QRect m_GenerationRect;
    int m_Population;
    int m_PlanetNumber;
    int m_Player;
    int m_PopulationGrowth;
    bool m_PFocus;
    int m_TickTillLastPop;
    QImage m_PlanetImg;
    int m_pl[7];
    //populationGrowth va etre utiliser pour determiner la grandeur de la planete.
    //une variable de texture
    //int planettype;
    void initialize(int Owner, int Quadrant,QList<Planet> PlanetArray);
    void MirrorPlanet(Planet SomePlanet,int Quadrant, int PlanetCount);
    bool CheckPlanetToPlanetCollision(Planet planet2);
    void PlanetTick(int tickAmmount);
    void initializeFromint(int W[]);
    int * Toint();
private:
    void LoadImage();
signals:

public slots:


};

#endif // PLANET_H
