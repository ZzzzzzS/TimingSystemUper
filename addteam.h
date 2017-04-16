#ifndef ADDTEAM_H
#define ADDTEAM_H

#include <QDialog>
#include "data.h"

namespace Ui {
class AddTeam;
}

class AddTeam : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeam(QWidget *parent = 0);
    ~AddTeam();
private slots:
    void NextSlot();
    void LastSlot();
    void SaveSlot();
    void deleteSlot();

private:
    Ui::AddTeam *ui;
};


#if _MSC_VER >= 1600                                //防止中文乱码
#pragma execution_character_set("utf-8")
#endif
#endif // ADDTEAM_H
