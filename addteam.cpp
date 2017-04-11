#include "addteam.h"
#include "ui_addteam.h"

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
    ui->NumberBox->setValue(1);
    ui->LastButton->setEnabled(false);
}

AddTeam::~AddTeam()
{
    delete ui;
}

void AddTeam::NextSlot()
{
    if(ui->NumberBox->value()==1)
        ui->LastButton->setEnabled(true);

    bool ok=true;
    NowMatch.reset();

    NowMatch.Number=ui->NumberBox->value();
    NowMatch.TeamName=ui->TeamLine->text();
    NowMatch.Type=ui->TypeBox->currentText();

    NowMatch.save();
    ui->TeamLine->clear();
    ui->NumberBox->setValue(ui->NumberBox->value()+1);
}

void AddTeam::LastSlot()
{
    if(ui->NumberBox->value()==2)
        ui->LastButton->setEnabled(false);

    ui->NumberBox->setValue(ui->NumberBox->value()-1);
    NowMatch.load(ui->NumberBox->value());
    ui->TeamLine->setText(NowMatch.TeamName);
    ui->TypeBox->setCurrentText(NowMatch.Type);
}

void AddTeam::SaveSlot()
{
    bool ok=true;
    NowMatch.reset();

    NowMatch.Number=ui->NumberBox->value();
    NowMatch.TeamName=ui->TeamLine->text();
    NowMatch.Type=ui->TypeBox->currentText();

    NowMatch.save();

    close();
}

