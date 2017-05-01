#ifndef ADDTEAM_NEW_H
#define ADDTEAM_NEW_H

#include <QDialog>
#include "data.h"
#include <QMessageBox>
#include <QTimer>

namespace Ui {
class addteam_new;
}

class addteam_new : public QDialog
{
    Q_OBJECT

public:
    explicit addteam_new(QWidget *parent = 0);
    ~addteam_new();
private slots:
    void QuestionSlot();
    void GoToSlot();
    void NextSlot();
    void LastSlot();
    void SaveSlot();
    void ResetSlot();
    void TimeSlot();

private:
    Ui::addteam_new *ui;
    QTimer *ReNew=new QTimer;
    void InformationRenew();
    void InformationSave();
};

#if _MSC_VER >= 1600                                //防止中文乱码
#pragma execution_character_set("utf-8")
#endif
#endif // ADDTEAM_NEW_H
