#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "confirmwindow.h"
#include "ui_confirmwindow.h"
#include "addteam.h"
#include "ui_addteam.h"
#include "aboutwindow.h"
#include "ui_aboutwindow.h"


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
    TableLoad();
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
    QObject::connect(ui->AboutButton,SIGNAL(clicked(bool)),this,SLOT(AboutSlot()));
}

void MainWindow::Push_Slot()
{
    this->FinshMatch();//完成比赛
    confirmWindow window;
    window.exec();
    Reload(NowMatch.Number);
    this->ReadyToReady();
}

void MainWindow::AddTeam_Slot()
{
    AddTeam NewTeam;
    NewTeam.exec();
    bool ok=true;
    NowMatch.load(ui->NumberLine->text().toInt(&ok,10));
    this->TableLoad();
    ReadyToReady();
}

void MainWindow::TableInit()
{
    ui->tableWidget->resizeRowsToContents();//自动调节列
    ui->tableWidget->resizeColumnsToContents();//自动调节行
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

void MainWindow::AboutSlot()
{
    AboutWindow About;
    About.exec();
}

void MainWindow::TableLoad()
{
    int store=NowMatch.Number;//先记录当前组的序号

    int i=1;
    while(true)
    {
        NowMatch.load(i);
       if(NowMatch.TeamName.isEmpty()&&NowMatch.Type.isEmpty())
        {
            break;
        }
        ui->tableWidget->setItem(i-1,0,new QTableWidgetItem(QString::number(NowMatch.Number)));
        ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(NowMatch.TeamName));
        ui->tableWidget->setItem(i-1,2,new QTableWidgetItem(NowMatch.Type));
        ui->tableWidget->setItem(i-1,3,new QTableWidgetItem(NowMatch.MatchTime.toString("mm:ss:zzz")));
        ui->tableWidget->setItem(i-1,4,new QTableWidgetItem(QString::number(NowMatch.Chujie)));
        ui->tableWidget->setItem(i-1,6,new QTableWidgetItem(NowMatch.FinalTime.toString("mm:ss:zzz")));
        if(NowMatch.StopCar==true)
        {
            ui->tableWidget->setItem(i-1,5,new QTableWidgetItem("是"));
        }
        else
        {
            ui->tableWidget->setItem(i-1,5,new QTableWidgetItem("否"));
        }

        i++;
    }
    NowMatch.load(store);
}

void MainWindow::Reload(int n)
{
    int store=NowMatch.Number;
    NowMatch.load(n);

    ui->tableWidget->setItem(n-1,0,new QTableWidgetItem(QString::number(NowMatch.Number)));
    ui->tableWidget->setItem(n-1,1,new QTableWidgetItem(NowMatch.TeamName));
    ui->tableWidget->setItem(n-1,2,new QTableWidgetItem(NowMatch.Type));
    ui->tableWidget->setItem(n-1,3,new QTableWidgetItem(NowMatch.MatchTime.toString("mm:ss:zzz")));
    ui->tableWidget->setItem(n-1,4,new QTableWidgetItem(QString::number(NowMatch.Chujie)));
    ui->tableWidget->setItem(n-1,6,new QTableWidgetItem(NowMatch.MatchTime.toString("mm:ss:zzz")));
    if(NowMatch.StopCar==true)
    {
        ui->tableWidget->setItem(n-1,5,new QTableWidgetItem("是"));
    }
    else
    {
        ui->tableWidget->setItem(n-1,5,new QTableWidgetItem("否"));
    }

    NowMatch.load(store);
}
