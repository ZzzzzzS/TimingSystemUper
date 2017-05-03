#include "addteam_new.h"
#include "ui_addteam_new.h"

addteam_new::addteam_new(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addteam_new)
{
    ui->setupUi(this);
    ui->NumberBox->setValue(NowMatch.Number);
    if(ui->NumberBox->value()<=2)
        ui->LastButton->setEnabled(false);
    this->ReNew->start(10);
    this->InformationRenew();
    QObject::connect(ui->QuestionButton,SIGNAL(clicked(bool)),this,SLOT(QuestionSlot()));
    QObject::connect(ui->SaveButton,SIGNAL(clicked(bool)),this,SLOT(SaveSlot()));
    QObject::connect(ui->NextButton,SIGNAL(clicked(bool)),this,SLOT(NextSlot()));
    QObject::connect(ui->LastButton,SIGNAL(clicked(bool)),this,SLOT(LastSlot()));
    QObject::connect(ui->ResetButton,SIGNAL(clicked(bool)),this,SLOT(ResetSlot()));
    QObject::connect(ui->ToButton,SIGNAL(clicked(bool)),this,SLOT(GoToSlot()));
    QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(TimeSlot()));
    this->setWindowTitle("718 lab");
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

addteam_new::~addteam_new()
{
    delete ui;
}

void addteam_new::InformationRenew()
{
    ui->NameLine->setText(NowMatch.TeamName);
    ui->TypeBox->setCurrentText(NowMatch.Type);
    ui->ChujieBox->setValue(NowMatch.Chujie);
    ui->RealTimeLine->setText(NowMatch.MatchTime.toString("mm:ss:zzz"));
    ui->FinalTimeLine->setText(NowMatch.FinalTime.toString("mm:ss:zzz"));
    if(NowMatch.StopCar==true)
    {
        ui->StopBox->setCurrentText("是");
    }
    else if(NowMatch.StopCar==false)
    {
        ui->StopBox->setCurrentText("否");
    }
}

void addteam_new::InformationSave()
{
    //ui->NumberBox->setValue(NowMatch.Number);
    NowMatch.TeamName=ui->NameLine->text();
    NowMatch.Type=ui->TypeBox->currentText();
    QString temp;
    temp=ui->RealTimeLine->text();
    NowMatch.MatchTime=QTime::fromString(temp,"mm:ss:zzz");
    temp=ui->FinalTimeLine->text();
    NowMatch.FinalTime=QTime::fromString(temp,"mm:ss:zzz");
    if(ui->StopBox->currentIndex()==0)
        NowMatch.StopCar=true;
    else if(ui->StopBox->currentIndex()==1)
        NowMatch.StopCar=false;
    NowMatch.Chujie=ui->ChujieBox->value();

    NowMatch.save();
}

void addteam_new::QuestionSlot()
{
    QMessageBox::information(this,"718 lab","勾选此项后按下一组时会自动储存当前组信息",QMessageBox::Ok);
}

void addteam_new::GoToSlot()
{
    if(ui->NumberBox->value()<1)
    {
        QMessageBox::information(this,"718 lab","输入值有误，请检查您的输入值",QMessageBox::Ok);
        return;
    }
    if(ui->NumberBox->value()<=2)
        ui->LastButton->setEnabled(false);

    if(ui->AutoBox->isChecked())
    {
        this->InformationSave();
    }
    NowMatch.load(ui->NumberBox->value());
    InformationRenew();
}

void addteam_new::NextSlot()
{
    if(ui->AutoBox->isChecked())
    {
        this->InformationSave();
    }
    ui->NumberBox->setValue(ui->NumberBox->value()+1);
    if(ui->NumberBox->value()>=1)
        ui->LastButton->setEnabled(true);

    NowMatch.load(ui->NumberBox->value());
    this->InformationRenew();
}

void addteam_new::LastSlot()
{
    ui->NumberBox->setValue(ui->NumberBox->value()-1);
    if(ui->NumberBox->value()<=2)
        ui->LastButton->setEnabled(false);
    NowMatch.load(ui->NumberBox->value());
    this->InformationRenew();
}

void addteam_new::SaveSlot()
{
    this->InformationSave();
    QMessageBox::information(this,"718 lab","信息更新成功",QMessageBox::Ok);
    if(ui->AutoBox->isChecked())
    {
        this->close();
    }
}

void addteam_new::ResetSlot()
{
    if(QMessageBox::question(this,"真的不要我了吗 (；′⌒`)","确认重置这一组?        ",QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
        return;
    NowMatch.reset_Number();
    this->InformationRenew();
    ui->NumberBox->setValue(NowMatch.Number);
}

void addteam_new::TimeSlot()
{
    QTime temp=QTime::fromString(ui->RealTimeLine->text(),"mm:ss:zzz");
    temp=temp.addSecs(ui->ChujieBox->value());
    if(ui->StopBox->currentIndex()==1)
        temp=temp.addSecs(1);
    ui->FinalTimeLine->setText(temp.toString("mm:ss:zzz"));
}
