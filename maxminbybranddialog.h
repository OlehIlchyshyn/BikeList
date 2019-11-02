#ifndef MAXMINBYBRANDDIALOG_H
#define MAXMINBYBRANDDIALOG_H

#include <QDialog>
#include "bikelist.h"

namespace Ui {
class MaxMinByBrandDialog;
}

class MaxMinByBrandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaxMinByBrandDialog(BikeList list, QWidget *parent = nullptr);
    ~MaxMinByBrandDialog();

private slots:
    void on_buttonFindCheapAndExpensive_clicked();

private:
    Ui::MaxMinByBrandDialog *ui;
    BikeList m_list;
};

#endif // MAXMINBYBRANDDIALOG_H
