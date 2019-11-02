#include "addnewbikedialog.h"
#include "ui_addnewbikedialog.h"

AddNewBikeDialog::AddNewBikeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewBikeDialog)
{
    ui->setupUi(this);
    QPixmap bkgnd("H:/Backgrounds/28.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QRegExp rx("[Є-ЯҐа-їґ-]+");
    ui->editColor->setValidator(new QRegExpValidator(rx, this));
    QRegExp rx2("[A-Za-z-]+");
    ui->editBrand->setValidator(new QRegExpValidator(rx2, this));
    ui->editModel->setValidator(new QRegExpValidator(rx2, this));
    QRegExp rx3("[0-9]+");
    ui->editPrice->setValidator(new QRegExpValidator(rx3, this));
}

AddNewBikeDialog::~AddNewBikeDialog()
{
    delete ui;
}

Bicycle AddNewBikeDialog::getBike()
{
    QString brand = ui->editBrand->text();
    QString model = ui->editModel->text();
    BicycleType type = BicycleTypeFromString(ui->comboType->currentText());
    QString color = ui->editColor->text();
    unsigned tyreDiameter = ui->spinTyreDiameter->value();
    FrameSize frameSize = FrameSizeFromString(ui->comboFrameSize->currentText());
    BikeState state = BikeStateFromString(ui->comboState->currentText());
    unsigned price = ui->editPrice->text().toInt();
    return Bicycle(brand, model, type, color, tyreDiameter, frameSize, state, price);
}
