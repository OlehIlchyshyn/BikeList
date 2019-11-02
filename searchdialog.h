#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "bikelist.h"
namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(BikeList list, QWidget *parent = nullptr);
    ~SearchDialog();

private slots:

    void on_buttonFind_clicked();

private:
    Ui::SearchDialog *ui;
    BikeList m_list;
};

#endif // SEARCHDIALOG_H
