#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusLabel = new QLabel;
    list = new BikeList;
    ui->tableBikeList->horizontalHeader()->setVisible(true);
    ui->statusBar->addWidget(statusLabel);
    statusLabel->setText("Для початку роботи відкрийте файл або додайте елементи списку вручну.");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (fileIsOpened)
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Список велосипедів");
        msgBox.setText("Під час роботи програми список, можливо, було змінено.");
        msgBox.setInformativeText("Чи хочете ви зберегти зміни?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Save:
            list->saveToFile(openedFile);
            event->accept();
              break;
          case QMessageBox::Discard:
            event->accept();
              break;
          case QMessageBox::Cancel:
            event->ignore();
              break;
          default:
              break;
        }
    }
}

MainWindow::~MainWindow()
{
    delete statusLabel;
    delete list;
    if (fileIsOpened)
    {
        openedFile->close();
        delete openedFile;
    }
    delete ui;
}


void MainWindow::on_openFile_triggered()
{
    if (fileIsOpened)
    {
        if (openedFile->isOpen())
        openedFile->close();
        delete openedFile;
        list->clear();
    }
    QString fileName = QFileDialog::getOpenFileName(this,
            "Відкрити список велосипедів", "H:\\inputBicycles",
            "Текстовий файл (*.txt);;Усі файли (*)");
    if (fileName.isEmpty())
    {
            return;
    }
    else
    {
        openedFile = new QFile(fileName);
        if (!(openedFile->open(QIODevice::ReadWrite | QFile::Text)))
        {
            QMessageBox::information(this, "Упс...",
                "Не вдалося відкрити файл.\n");
            openedFile->close();
            delete openedFile;
            return;
        }
        else
        {
            list->fillFromFile(openedFile);
            fileIsOpened = true;
            printList();
            statusLabel->setText("Відкрито файл "+openedFile->fileName()+".");
        }
    }
    if (list->isEmpty()) statusLabel->setText("Список порожній.");
}

void MainWindow::printList()
{
    int length = list->getLength();
    ui->tableBikeList->setRowCount(length);
    for (int i = 0; i < length; ++i)
    {
        ui->tableBikeList->setItem(i, 0, new QTableWidgetItem(list->at(i).getBrand()));
        ui->tableBikeList->setItem(i, 1, new QTableWidgetItem(list->at(i).getModel()));
        ui->tableBikeList->setItem(i, 2, new QTableWidgetItem(list->at(i).getTypeString()));
        ui->tableBikeList->setItem(i, 3, new QTableWidgetItem(list->at(i).getColor()));
        ui->tableBikeList->setItem(i, 4, new QTableWidgetItem(QString::number(list->at(i).getTyreDiameter())));
        ui->tableBikeList->setItem(i, 5, new QTableWidgetItem(list->at(i).getFrameSizeString()));
        ui->tableBikeList->setItem(i, 6, new QTableWidgetItem(list->at(i).getStateString()));
        ui->tableBikeList->setItem(i, 7, new QTableWidgetItem(QString::number(list->at(i).getPrice())));
    }
}
void MainWindow::on_save_triggered()
{
    if (fileIsOpened)
    {
        list->saveToFile(openedFile);
        statusLabel->setText("Поточний список було збережено у попередньо відкритий файл.");
    }
    else if (openedFile)
    {
        openedFile->open(QIODevice::ReadWrite | QFile::Text);
        list->saveToFile(openedFile);
        statusLabel->setText("Поточний список було збережено у попередньо відкритий файл.");

    }
    else
    {
        QMessageBox::warning(this,"Упс...","Не вдалось зберегти зміни, так як файл не відкрито."
                                           "Для збереження поточного списку у файл скористайтесь опцією \"Зберегти як\" з меню \"Файл\"");
    }
}

void MainWindow::on_saveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            "Зберегти список велосипедів", "H:\\inputBicycles",
            "Текстовий файл (*.txt);;Усі файли (*)");
    if (fileName.isEmpty())
    {
            return;
    }
    else
    {
        auto *out = new QFile(fileName);
        if (!(out->open(QIODevice::WriteOnly | QFile::Text)))
        {
            QMessageBox::information(this, "Упс...",
                "Не вдалося відкрити файл.\n");
            out->close();
            return;
        }
        else
        {
            list->saveToFile(out);
            statusLabel->setText("Список було збережено у файл "+out->fileName()+".");
        }
    }
}

void MainWindow::on_ClearList_triggered()
{
    list->clear();
    printList();
    statusLabel->setText("Список велосипедів було очищено.");
}

void MainWindow::on_AddNewBike_triggered()
{
    AddNewBikeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        Bicycle temp = dialog.getBike();
        list->addNewElement(temp);
        printList();
        statusLabel->setText("Дані про велосипед були успішно додані до списку.");
    }
}

void MainWindow::on_aboutProgram_triggered()
{
    QMessageBox::information(this,"Про програму",
                             "Назва програми: \"Список велосипедів\"\n"
                             "Версія: 1.0\n"
                             "Розробник: студент групи ПЗ-23 Ільчишин Олег");
}

void MainWindow::on_deleteSelected_triggered()
{
    QModelIndexList selectedList = ui->tableBikeList->selectionModel()->selectedRows();
    for (int i = 0; i < selectedList.count(); ++i)
    {
        list->removeAt(selectedList.at(i).row());
    }
    printList();
    statusLabel->setText("Обрані записи було видалено зі списку.");
    if (list->isEmpty()) statusLabel->setText("Список порожній.");
}

void MainWindow::on_search_triggered()
{
    SearchDialog dialog(*list, this);
    dialog.exec();
}

void MainWindow::on_deleteWithMostCommonColour_triggered()
{
    int length = list->getLength();
    QString commonCol = list->findMostCommonColour();
    for (int i = 0; i < length; ++i)
    {
        if (list->at(i).getColor() == commonCol)
        {
            list->removeAt(i);
            i--;
            length--;
        }
    }
    printList();
    statusLabel->setText("Дані про велосипеди з кольором, який зустрічався найчастіше були видалені зі списку.");
}

void MainWindow::on_deleteAllNew_triggered()
{
    int length = list->getLength();
    for (int i = 0; i < length; ++i)
    {
        if (list->at(i).isNew())
        {
            list->removeAt(i);
            i--;
            length--;
        }
    }
    printList();
    statusLabel->setText("Дані про нові велосипеди були видалені зі списку.");
}

void MainWindow::on_deleteAllUsed_triggered()
{
    int length = list->getLength();
    for (int i = 0; i < length; ++i)
    {
        if (!(list->at(i).isNew()))
        {
            list->removeAt(i);
            i--;
            length--;
        }
    }
    printList();
    statusLabel->setText("Дані про користовані велосипеди були видалені зі списку.");
}

void MainWindow::on_findCheapestAndMostExpensiveByBrand_triggered()
{
    MaxMinByBrandDialog dialog(*list, this);
    dialog.exec();
}

void MainWindow::on_sortByPriceDescending_triggered()
{
    list->sortByMarks(true);
    printList();
    statusLabel->setText("Список велосипедів було посортовано за ціною в порядку спадання.");
}

void MainWindow::on_sortByPriceAscending_triggered()
{
    list->sortByMarks();
    printList();
    statusLabel->setText("Список велосипедів було посортовано за ціною в порядку зростання.");
}

void MainWindow::on_showStatistics_triggered()
{

}
