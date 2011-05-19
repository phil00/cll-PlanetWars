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
    connect(m_time, SIGNAL(timeout()), this, SLOT(sl_time_TimeOut()));
    connect(m_TcpServ,SIGNAL(newConnection()), this, SLOT(sl_TcpServ_NewConnection()));
}

ServerMain::~ServerMain()
{
    delete ui;
}

void ServerMain::on_btnStartStop_clicked()
{
    if(ui->btnStartStop->text() == "Start")
    {
        ui->btnStartStop->setText("Stop");
        if( !m_time->isActive() )
        {
            qsrand( QTime::currentTime().msec() );
            int random = 6 + qrand()%15;
            Planet temp;
            for( int i = 0 ; i < random ; i++)
            {
                if( i == 1 )
                {
                   temp.initialize( 1, 1, m_Planets );
                }
                else
                {
                   temp.initialize( 5, 1, m_Planets );
                }
                m_Planets.append(temp);
            }
            for( int i = 0 ; i < random ; i++ )
            {
                temp.MirrorPlanet( m_Planets[i], 2, m_Planets.length() );
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
}

void ServerMain::sl_NewMessage(QByteArray p)
{
    emit SendMessage(p);
}
