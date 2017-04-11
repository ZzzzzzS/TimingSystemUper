#include "confirmwindow.h"
#include "ui_confirmwindow.h"

confirmWindow::confirmWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmWindow)
{
    ui->setupUi(this);
    ui->TeamNameLine->setText(NowMatch.TeamName);
    ui->NumberLine->setText(QString::number(NowMatch.Number));
    ui->TimeLine->setText(NowMatch.MatchTime.toString("mm:ss:zzz"));
    ui->FinalTimeLine->setText(NowMatch.FinalTime.toString("mm:ss:zzz"));
    ui->chujiebox->setValue(NowMatch.Chujie);
    if(NowMatch.StopCar==true)
        ui->StopCarBox->setCurrentIndex(0);
    else
        ui->StopCarBox->setCurrentIndex(1);
    ui->TypeLine->setText(NowMatch.Type);
    QObject::connect(ui->OkButton,SIGNAL(clicked(bool)),this,SLOT(SaveFileSlot()));
    ReNew->start(100);//100ms刷新一次
    QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(Reload()));

    this->setMaximumSize(324,576);
    this->setMinimumSize(324,576);

}

confirmWindow::~confirmWindow()
{
    delete ReNew;
    delete ui;
}

void confirmWindow::SaveFileSlot()
{
    QString temp;
    temp=ui->TimeLine->text();
    NowMatch.MatchTime=QTime::fromString(temp,"mm:ss:zzz");
    temp=ui->FinalTimeLine->text();
    NowMatch.FinalTime=QTime::fromString(temp,"mm:ss:zzz");
    if(ui->StopCarBox->currentIndex()==0)
        NowMatch.StopCar=true;
    else if(ui->StopCarBox->currentIndex()==1)
        NowMatch.StopCar=false;
    NowMatch.Chujie=ui->chujiebox->value();
    NowMatch.isMatched=true;
    NowMatch.save();
    QMessageBox::information(this,"提交成绩","成功!   ",QMessageBox::Close);
    this->close();
}

void confirmWindow::Reload()
{
    QTime temp=QTime::fromString(ui->TimeLine->text(),"mm:ss:zzz");
    temp=temp.addSecs(ui->chujiebox->value());
    if(ui->StopCarBox->currentIndex()==1)
        temp=temp.addSecs(1);
    ui->FinalTimeLine->setText(temp.toString("mm:ss:zzz"));
}
