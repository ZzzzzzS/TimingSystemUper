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

private:
    Ui::AddTeam *ui;
};

#endif // ADDTEAM_H
