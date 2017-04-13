#ifndef DATA_H
#define DATA_H
//专门定义储存比赛信息的类型
#include <QString>
#include <QTime>
#include <QtSql>

class TeamInformation
{
public:
    QString TeamName;//队伍名
    QString Type;//比赛组别
    int Number;//编号
    QTime MatchTime;//比赛时间
    int Chujie;//出界次数
    bool StopCar;//停车是否成功
    QTime FinalTime;//最终时间
    bool isMatched;//是否比赛过

    TeamInformation();//构造函数清零
    void reset();//清零
    void load(int Number);//从磁盘装载第几号选手信息
    void save();//储存当前选手信息





    //sql测试部分
   QSqlDatabase db;
   void SQLOpen();



};

extern TeamInformation NowMatch;//声明一个类储存当前选手信息


#endif // DATA_H
