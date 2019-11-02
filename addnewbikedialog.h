#ifndef ADDNEWBIKEDIALOG_H
#define ADDNEWBIKEDIALOG_H

#include <QDialog>
#include "bicycle.h"
namespace Ui {
class AddNewBikeDialog;
}

class AddNewBikeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewBikeDialog(QWidget *parent = nullptr);
    ~AddNewBikeDialog();
    Bicycle getBike();
private:
    Ui::AddNewBikeDialog *ui;
};

#endif // ADDNEWBIKEDIALOG_H
