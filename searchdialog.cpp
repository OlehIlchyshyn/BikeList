#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(BikeList list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    m_list = list;
    QPixmap bkgnd("H:/Backgrounds/28.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_buttonFind_clicked()
{
    QString searchStr = ui->editSearchBar->text();
    QVector<Bicycle> vec;
    if (ui->radioBrand->isChecked())
    {
        vec = m_list.findByBrand(searchStr);
    }
    if (ui->radioType->isChecked())
    {
        BicycleType type = BicycleTypeFromString(searchStr);
        vec = m_list.findByType(type);
    }
    if (ui->radioTyreDiam->isChecked())
    {
        unsigned diam = searchStr.toInt();
        vec = m_list.findByTyreDiameter(diam);
    }
    if (ui->radioFrameSize->isChecked())
    {
        FrameSize size = FrameSizeFromString(searchStr);
        vec = m_list.findByFrameSize(size);
    }
    int length = vec.length();
    if (!length)
    {
        QMessageBox::warning(this, "Ехххх:(", "Не вдалось відшукати збіги у заданому списку");
        return;
    }
    ui->tableSearchResult->setRowCount(length);
    for (int i = 0; i < length; ++i)
    {
        ui->tableSearchResult->setItem(i, 0, new QTableWidgetItem(vec[i].getBrand()));
        ui->tableSearchResult->setItem(i, 1, new QTableWidgetItem(vec[i].getModel()));
        ui->tableSearchResult->setItem(i, 2, new QTableWidgetItem(vec[i].getTypeString()));
        ui->tableSearchResult->setItem(i, 3, new QTableWidgetItem(vec[i].getColor()));
        ui->tableSearchResult->setItem(i, 4, new QTableWidgetItem(QString::number(vec[i].getTyreDiameter())));
        ui->tableSearchResult->setItem(i, 5, new QTableWidgetItem(vec[i].getFrameSizeString()));
        ui->tableSearchResult->setItem(i, 6, new QTableWidgetItem(vec[i].getStateString()));
        ui->tableSearchResult->setItem(i, 7, new QTableWidgetItem(QString::number(vec[i].getPrice())));
    }
}
