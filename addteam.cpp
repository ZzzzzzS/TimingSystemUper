#include "addteam.h"
#include "ui_addteam.h"
#include <QMessageBox>
#include <QtDebug>

AddTeam::AddTeam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTeam)
{
    ui->setupUi(this);
    this->setMaximumSize(384,153);
    this->setMinimumSize(384,153);
    QObject::connect(ui->NextButton,SIGNAL(clicked()),this,SLOT(NextSlot()));
    QObject::connect(ui->LastButton,SIGNAL(clicked()),this,SLOT(LastSlot()));
    QObject::connect(ui->SaveButton,SIGNAL(clicked()),this,SLOT(SaveSlot()));
    QObject::connect(ui->DeleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteSlot()));


    ui->TeamLine->setText(NowMatch.TeamName);
    ui->TypeBox->setCurrentText(NowMatch.Type);
    ui->NumberBox->setValue(NowMatch.Number);
    if(NowMatch.Number<=1)
        ui->LastButton->setEnabled(false);
}

AddTeam::~AddTeam()
{
    delete ui;
}

void AddTeam::NextSlot()
{
    if(ui->NumberBox->value()>=1)
        ui->LastButton->setEnabled(true);

    NowMatch.reset();
    NowMatch.Number=ui->NumberBox->value();
    NowMatch.TeamName=ui->TeamLine->text();
    NowMatch.Type=ui->TypeBox->currentText();

    NowMatch.save();
    QMessageBox::information(this,"保存","本组信息更新成功!",QMessageBox::Ok);
    ui->TeamLine->clear();
    ui->NumberBox->setValue(ui->NumberBox->value()+1);

    NowMatch.load(ui->NumberBox->value());
    ui->TeamLine->setText(NowMatch.TeamName);
    ui->TypeBox->setCurrentText(NowMatch.Type);
}

void AddTeam::LastSlot()
{
    if(ui->NumberBox->value()<=2)
        ui->LastButton->setEnabled(false);

    ui->NumberBox->setValue(ui->NumberBox->value()-1);
    NowMatch.load(ui->NumberBox->value());
    ui->TeamLine->setText(NowMatch.TeamName);
    ui->TypeBox->setCurrentText(NowMatch.Type);
}

void AddTeam::SaveSlot()
{
    NowMatch.load(ui->NumberBox->value());
    if(NowMatch.isMatched==true)
    {
        if(QMessageBox::question(this,"错误","当前队伍已比赛，此操作会清除比赛成绩，\n确定要保存吗？",QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
        {
            close();
            return;
        }
    }

    NowMatch.reset();

    NowMatch.Number=ui->NumberBox->value();
    NowMatch.TeamName=ui->TeamLine->text();
    NowMatch.Type=ui->TypeBox->currentText();

    NowMatch.save();

    close();
}

void AddTeam::deleteSlot()
{
   if(QMessageBox::question(this,"真的不要我了吗 (；′⌒`)","确认重置这一组?        ",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
    {
       int a=ui->NumberBox->value();
       int n=NowMatch.Number;
       NowMatch.load(a);
       NowMatch.reset();
       NowMatch.save();
       NowMatch.load(n);

       ui->TeamLine->clear();
       ui->TypeBox->setCurrentIndex(0);
   }
}


