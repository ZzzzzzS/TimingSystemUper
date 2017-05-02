#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "confirmwindow.h"
#include "ui_confirmwindow.h"
#include "addteam.h"
#include "ui_addteam.h"
#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "addteam_new.h"
#include "ui_addteam_new.h"

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
        addteam_new NewTeam;
        NewTeam.exec();
    }
    ReadyToReady();
    TableLoad();
    ui->ConfirmButton->setEnabled(false);
    ui->ChuJieButton->setEnabled(false);
    ui->StopFailButton->setEnabled(false);
    this->PunishTimes=0;
    ui->ChujieLine->setText("0");
    ui->NumBox->setValue(1);
    //this->setMaximumSize(1440,810);
   // this->setMinimumSize(1440,810);
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
    QObject::connect(ui->ConfirmButton,SIGNAL(clicked()),this,SLOT(Push_Slot()));
    QObject::connect(ui->AddButton,SIGNAL(clicked(bool)),this,SLOT(AddTeam_Slot()));
    QObject::connect(ui->LastTeamButton,SIGNAL(clicked(bool)),this,SLOT(LatTeam_Slot()));
    QObject::connect(ui->NextTeamButton,SIGNAL(clicked(bool)),this,SLOT(NextTeam_Slot()));
    QObject::connect(ui->AboutButton,SIGNAL(clicked(bool)),this,SLOT(AboutSlot()));
    QObject::connect(ui->PauseButton,SIGNAL(clicked(bool)),this,SLOT(PauseSlot()));
    QObject::connect(ui->ResetButton,SIGNAL(clicked(bool)),this,SLOT(ResetSlot()));
    QObject::connect(ui->tableWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(PaiXuSlot(int)));
    QObject::connect(ui->TypeBox,SIGNAL(currentTextChanged(QString)),this,SLOT(WuxiaoSlot()));
    QObject::connect(ui->GotoButton,SIGNAL(clicked(bool)),this,SLOT(GotoSlot()));
}

void MainWindow::Push_Slot()
{
    this->FinshMatch();//完成比赛
    confirmWindow window;
    window.exec();
    Reload(NowMatch.Number);
    NowMatch.load(NowMatch.Number+1);
    if(NowMatch.TeamName.isEmpty()&&NowMatch.Type.isEmpty())
    {
        QMessageBox::information(this,"已经到最后一组了","然而并没有更多的组 ㄟ( ▔, ▔ )ㄏ",QMessageBox::Ok);
        NowMatch.load(NowMatch.Number-1);

    }
    ui->StartButton->setText("准备!");
    this->ReadyToReady();
    PaiXuSlot(6);
}

void MainWindow::AddTeam_Slot()
{
    addteam_new NewTeam;
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
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
        QMessageBox::information(this,"需要更多的队伍","然而并没有更多队伍 (￣_￣|||)",QMessageBox::Ok);
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

void MainWindow::PauseSlot()
{
    if(ui->PauseButton->text()=="暂停")
        ui->PauseButton->setText("继续");
    else if(ui->PauseButton->text()=="继续")
        ui->PauseButton->setText("暂停");
}

void MainWindow::ResetSlot()
{
    if(QMessageBox::question(this,"复位","如果复位将丢失当前组成绩，要复位吗?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
        return;

    QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));
    ui->StartButton->setText("准备!");
    ui->StartButton->setEnabled(true);
    ui->TimeLine->setText("01:00:");//先刷一次图
    ui->TimeLine_MS->setText("000");
    ui->NextTeamButton->setEnabled(true);
    ui->LastTeamButton->setEnabled(true);
    ui->AddButton->setEnabled(true);
    ui->ChuJieButton->setEnabled(false);
    ui->ConfirmButton->setEnabled(false);
    ui->StopFailButton->setEnabled(false);
}

void MainWindow::PaiXuSlot(int n)
{
    ui->tableWidget->sortItems(n,Qt::AscendingOrder);//排序
}

void MainWindow::WuxiaoSlot()
{
    if(ui->TypeBox->currentText()==NowMatch.Type)
        return;

    QMessageBox::information(this,"不能在这里修改","注意，在此处的修改无效，\n修改请在添加/修改比赛处修改",QMessageBox::Ok);
    ui->TypeBox->setCurrentText(NowMatch.Type);
}

void MainWindow::GotoSlot()
{
    if(ui->NumBox->value()<1)
    {
        QMessageBox::information(this,"718 lab","输入值有误，请检查您的输入值",QMessageBox::Ok);
        return;
    }
    int number=NowMatch.Number;
    NowMatch.load(ui->NumBox->value());
    if(NowMatch.TeamName.isEmpty()&&NowMatch.Type.isEmpty())
    {
        //可能存在bug
        NowMatch.load(number);
        QMessageBox::information(this,"718 lab","输入值有误，请检查您的输入值",QMessageBox::Ok);
    }
    this->ReadyToReady();
}
