#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "confirmwindow.h"
#include "ui_confirmwindow.h"
#include "addteam.h"
#include "ui_addteam.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TableInit();
    connect_init();//初始化连接
    Port_Scan();//端口扫描
    NowMatch.load(1);
    if(NowMatch.TeamName.isEmpty()&&NowMatch.Type.isEmpty())
    {
        QMessageBox::information(this,"请添加队伍信息","你可能用了假的数据库 ⊙﹏⊙∥",QMessageBox::Ok);
        AddTeam NewTeam;
        NewTeam.exec();
    }
    ReadyToReady();
    ui->ConfirmButton->setEnabled(false);
    ui->ChuJieButton->setEnabled(false);
    ui->StopFailButton->setEnabled(false);
    this->PunishTimes=0;
    ui->ChujieLine->setText("0");

    this->setMaximumSize(1440,810);
    this->setMinimumSize(1440,810);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::connect_init()
{
    QObject::connect(ui->ChuanKouButton,SIGNAL(clicked(bool)),this,SLOT(Port_Init()));
    QObject::connect(ui->StartButton,SIGNAL(clicked()),this,SLOT(Start_Slot()));//开始按钮的槽
    QObject::connect(ui->ChuJieButton,SIGNAL(clicked()),this,SLOT(Punish_Slot()));
    QObject::connect(ui->StopFailButton,SIGNAL(clicked()),this,SLOT(StopFail_Slot()));
    QObject::connect(ui->AboutQtButton,SIGNAL(clicked()),qApp,SLOT(aboutQt()));
    QObject::connect(ui->ConfirmButton,SIGNAL(clicked()),this,SLOT(Push_Slot()));
    QObject::connect(ui->AddButton,SIGNAL(clicked(bool)),this,SLOT(AddTeam_Slot()));
    QObject::connect(ui->LastTeamButton,SIGNAL(clicked(bool)),this,SLOT(LatTeam_Slot()));
    QObject::connect(ui->NextTeamButton,SIGNAL(clicked(bool)),this,SLOT(NextTeam_Slot()));
}

void MainWindow::Push_Slot()
{
    this->FinshMatch();//完成比赛
    confirmWindow window;
    window.exec();
}

void MainWindow::AddTeam_Slot()
{
    AddTeam NewTeam;
    NewTeam.exec();
    bool ok=true;
    NowMatch.load(ui->NumberLine->text().toInt(&ok,10));
    ReadyToReady();
}

void MainWindow::TableInit()
{
    this->Model->setColumnCount(7);
    this->Model->setHeaderData(0,Qt::Horizontal,QVariant("序号"));
    this->Model->setHeaderData(1,Qt::Horizontal,QVariant("队名"));
    this->Model->setHeaderData(2,Qt::Horizontal,QVariant("组别"));
    this->Model->setHeaderData(3,Qt::Horizontal,QVariant("实际时间"));
    this->Model->setHeaderData(4,Qt::Horizontal,QVariant("出界次数"));
    this->Model->setHeaderData(5,Qt::Horizontal,QVariant("停车成功"));
    this->Model->setHeaderData(6,Qt::Horizontal,QVariant("最终成绩"));
    ui->tableView->setModel(this->Model);
    ui->tableView->resizeColumnsToContents();//自动调节列
    ui->tableView->resizeRowsToContents();//自动调节行
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::LatTeam_Slot()
{
    if(NowMatch.Number<=1)
    {
        QMessageBox::information(this,"718 lab","前面已经没有队伍啦! ╮(╯-╰)╭",QMessageBox::Ok);
        return;
    }
    NowMatch.load(NowMatch.Number-1);
    this->ReadyToReady();
}

void MainWindow::NextTeam_Slot()
{
    NowMatch.load(NowMatch.Number+1);
    if(NowMatch.TeamName.isEmpty()&&NowMatch.Type.isEmpty())
    {
        //可能存在bug
        NowMatch.load(NowMatch.Number-1);
        QMessageBox::information(this,"718 lab","然而并没有更多队伍 (￣_￣|||)",QMessageBox::Ok);
    }
    this->ReadyToReady();
}
