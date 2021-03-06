#include "servermain.h"
#include "ui_servermain.h"

ServerMain::ServerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerMain)
{
    ui->setupUi(this);
    m_TcpServ = new QTcpServer();
    m_TcpServ->listen(QHostAddress::Any, 35994);
    m_time = new QTimer();
    m_Joueur = 0;
    connect(m_time, SIGNAL(timeout()), this, SLOT(sl_time_TimeOut()));
    connect(m_TcpServ,SIGNAL(newConnection()), this, SLOT(sl_TcpServ_NewConnection()));
}

ServerMain::~ServerMain()
{
    delete ui;
    delete m_TcpServ;
    delete m_time;
    delete m_thServeur;
}

void ServerMain::on_btnStartStop_clicked()
{
    /*Planet *p = new Planet();
    p->m_Location.setX(50);
    p->m_Location.setY(50);
    p->m_Location.setWidth(10);
    p->m_Location.setHeight(10);
    p->m_GenerationRect.setX(40);
    p->m_GenerationRect.setY(40);
    p->m_GenerationRect.setWidth(30);
    p->m_GenerationRect.setHeight(30);
    p->m_PFocus = false;
    p->m_PlanetNumber = 1;
    p->m_Player = 1;
    p->m_Population = 25;
    p->m_PopulationGrowth = 25;
    p->m_TickTillLastPop = 100;
    m_Planets.append(*p);*/
    if(ui->btnStartStop->text() == "Start")
    {
        ui->btnStartStop->setText("Stop");
        if( !m_time->isActive() )
        {
            qsrand(QTime::currentTime().msec());
            int random = 8+qrand()%6;
            Planet temp;
            temp.initialize(1,1,m_Planets);
            m_Planets.append(temp);
            for(int i =1;i<random;i++)
            {
                temp.initialize(5,1,m_Planets);
                m_Planets.append(temp);
            }
            for(int i = 0;i<random;i++)
            {
                temp.MirrorPlanet(m_Planets[i],1,m_Planets.length());
                temp.m_Location.moveRight(temp.m_Location.x()+120);
                m_Planets.append(temp);
            }
            emit(Start(m_Planets, (short)ui->sbNbUtilisateur->value()));
            m_time->start(42);
       }
    }
    else
    {
        ui->btnStartStop->setText("Start");
        m_time->stop();
        emit(Stop());
        m_thServeur->terminate();
        m_thServeur->wait(1000);
        ui->sbNbUtilisateur->setValue(0);
    }
}

void ServerMain::sl_time_TimeOut()
{
    emit(newTime());
}

void ServerMain::sl_TcpServ_NewConnection()
{
    m_thServeur = new thServeur();
    connect(this, SIGNAL(newTime()), m_thServeur, SLOT(sl_time_newTime()));
    connect(this, SIGNAL(SendMessage(QByteArray)), m_thServeur, SLOT(sl_SendMessage(QByteArray)));
    connect(m_thServeur, SIGNAL(NewMessage(QByteArray)), this, SLOT(sl_NewMessage(QByteArray)));
    connect(m_thServeur, SIGNAL(Deco()), this, SLOT(on_btnStartStop_clicked()));
    connect(this, SIGNAL(Start(QList<Planet>, short)), m_thServeur, SLOT(sl_Start(QList<Planet>, short)));
    connect(this,SIGNAL(Stop()), m_thServeur, SLOT(sl_Stop()));
    ui->sbNbUtilisateur->setValue(ui->sbNbUtilisateur->value() + 1);
   /* if(ui->sbNbUtilisateur->value() == 2 || ui->sbNbUtilisateur->value() == 4)
    {
        ui->btnStartStop->setEnabled(true);
    }
    else
    {
        ui->btnStartStop->setEnabled(false);
    }*/
    m_thServeur->m_sockServeur = m_TcpServ->nextPendingConnection();
    connect(m_thServeur->m_sockServeur, SIGNAL(readyRead()), m_thServeur, SLOT(ReadyToRead()));
    m_Joueur = m_Joueur + 1;
    m_thServeur->m_Joueur = m_Joueur;
    //m_thServeur->start();
}

void ServerMain::on_pushButton_clicked()
{
    int yo[30];
    for(int i; i<30;i++)
    {
        yo[i]=QString(ui->lineEdit_3->text()[i]).toInt();
    }
    Paquet *p = new Paquet(50, 49,yo);
    QByteArray b = p->ToByteArray();
    p->FromByteArray(b);
    delete p;
}

void ServerMain::sl_NewMessage(QByteArray p)
{
    emit SendMessage(p);
}
