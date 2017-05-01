#include "data.h"
#include <QSettings>

TeamInformation::TeamInformation()//初始化清零
{
    this->Chujie=0;
    this->FinalTime=QTime(23,59,59,999);
    this->isMatched=false;
    this->MatchTime=QTime(23,59,59,999);
    this->Number=0;
    this->StopCar=true;//默认停车成功
    this->TeamName="NoName";
    this->Type="NoType";
}

void TeamInformation::save()
{
    QSettings Information("MatchInformation.ini",QSettings::IniFormat);

    Information.beginGroup(QString::number(this->Number));
    Information.setValue("TeamName",QVariant(this->TeamName));
    Information.setValue("MatchType",QVariant(this->Type));
    Information.setValue("Time",QVariant(this->MatchTime.toString("mm:ss:zzz")));
    Information.setValue("Punishment",QVariant(this->Chujie));
    Information.setValue("StopCar",QVariant(this->StopCar));
    Information.setValue("FinalTime",QVariant(this->FinalTime.toString("mm:ss:zzz")));
    Information.setValue("HasMatched",QVariant(this->isMatched));
    Information.endGroup();
}

void TeamInformation::load(int Number)
{
    QSettings Read("MatchInformation.ini",QSettings::IniFormat);

    Read.beginGroup(QString::number(Number));
    this->Number=Number;
    this->TeamName=Read.value("TeamName").toString();
    this->Type=Read.value("MatchType").toString();
    this->MatchTime=QTime::fromString(Read.value("Time").toString(),"mm:ss:zzz");
    this->Chujie=Read.value("Punishment").toInt();
    this->StopCar=Read.value("StopCar").toBool();
    this->FinalTime=QTime::fromString(Read.value("FinalTime").toString(),"mm:ss:zzz");
    this->isMatched=Read.value("HasMatched").toBool();
    Read.endGroup();
}

void TeamInformation::reset()
{
    this->Chujie=0;
    this->FinalTime=QTime(23,59,59,999);
    this->isMatched=false;
    this->MatchTime=QTime(23,59,59,999);
    this->Number=0;
    this->StopCar=true;//默认停车成功
    this->TeamName="NoName";
    this->Type="NoType";
}

void TeamInformation::reset_Number()
{
    this->Chujie=0;
    this->FinalTime=QTime(23,59,59,999);
    this->isMatched=false;
    this->MatchTime=QTime(23,59,59,999);
    this->StopCar=true;//默认停车成功
    this->TeamName="NoName";
    this->Type="光电四轮组";
}

TeamInformation NowMatch;//声明一个类储存当前选手信息
