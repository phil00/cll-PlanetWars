#include "servermain.h"
#include "ui_servermain.h"

ServerMain::ServerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerMain)
{
    ui->setupUi(this);
    TcpServ = new QTcpServer();
    TcpServ->listen(QHostAddress::Any, 35994);
    time = new QTimer();
    connect(time, SIGNAL(timeout()), this, SLOT(sl_time_TimeOut()));
    connect(TcpServ,SIGNAL(newConnection()), this, SLOT(sl_TcpServ_NewConnection()));
    connect(m_thServeur, SIGNAL(NewMessage(QByteArray)), this, SLOT(sl_NewMessage(QByteArray)));
    //connect(this, SIGNAL(Start), m_thServeur, SLOT(sl_Start()));
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
        if(!time->isActive())
        {
            //emit(Start);
            time->start(42);
        }
    }
    else
    {
        ui->btnStartStop->setText("Start");
        time->stop();
    }
}

void ServerMain::sl_time_TimeOut()
{
    emit(newTime());
}

void ServerMain::sl_TcpServ_NewConnection()
{
    m_thServeur = new thServeur();
    connect(this, SIGNAL(newTime()), m_thServeur, SLOT(on_time_newTime()));
    connect(this, SIGNAL(SendMessage(QByteArray)), m_thServeur, SLOT(on_SendMessage(QByteArray)));
    ui->sbNbUtilisateur->setValue(ui->sbNbUtilisateur->value() + 1);
    m_thServeur->sockServeur = TcpServ->nextPendingConnection();
    m_thServeur->start();
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
