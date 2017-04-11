#ifndef CONFIRMWINDOW_H
#define CONFIRMWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include "data.h"

namespace Ui {
class confirmWindow;
}

class confirmWindow : public QDialog
{
    Q_OBJECT

public:
    explicit confirmWindow(QWidget *parent = 0);
    ~confirmWindow();
private slots:
    void SaveFileSlot();//储存比赛信息
    void Reload();

private:
    Ui::confirmWindow *ui;
    QTimer *ReNew=new QTimer;
};

#if _MSC_VER >= 1600                                //防止中文乱码
#pragma execution_character_set("utf-8")
#endif

#endif // CONFIRMWINDOW_H
