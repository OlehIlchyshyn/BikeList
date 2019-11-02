#include "maxminbybranddialog.h"
#include "ui_maxminbybranddialog.h"

MaxMinByBrandDialog::MaxMinByBrandDialog(BikeList list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaxMinByBrandDialog)
{
    ui->setupUi(this);
    m_list = list;
    QPixmap bkgnd("H:/Backgrounds/28.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MaxMinByBrandDialog::~MaxMinByBrandDialog()
{
    delete ui;
}

void MaxMinByBrandDialog::on_buttonFindCheapAndExpensive_clicked()
{
    QString brand = ui->editBrand->text();
    QVector<Bicycle> vec = m_list.findByBrand(brand);
    if (!vec.length())
    {
        QMessageBox::warning(this, "Еххххх:(", "У списку відсутні велосипеди такої марки");
        return;
    }
    Bicycle cheapest = vec[0], mostExpensive = vec[0];
    for (int i = 0; i < vec.length(); ++i)
    {
        if (vec[i].getPrice() < cheapest.getPrice())
        {
            cheapest = vec[i];
            continue;
        }
        if (vec[i].getPrice() > mostExpensive.getPrice())
        {
            mostExpensive = vec[i];
            continue;
        }
    }
    QString cheapName = cheapest.getBrand() + " " + cheapest.getModel();
    QString expensiveName = mostExpensive.getBrand() + " " + mostExpensive.getModel();
    ui->editCheapest->setText(cheapName);
    ui->editMostExpensive->setText(expensiveName);
}
