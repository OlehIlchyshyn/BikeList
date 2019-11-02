#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDebug>
#include "bikelist.h"
#include "searchdialog.h"
#include "maxminbybranddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFile_triggered();

    void printList();

    void on_save_triggered();

    void on_saveAs_triggered();

    void on_ClearList_triggered();

    void on_AddNewBike_triggered();

    void on_aboutProgram_triggered();

    void on_deleteSelected_triggered();

    void on_search_triggered();

    void on_deleteWithMostCommonColour_triggered();

    void on_deleteAllNew_triggered();

    void on_deleteAllUsed_triggered();

    void on_findCheapestAndMostExpensiveByBrand_triggered();

    void on_sortByPriceDescending_triggered();

    void on_sortByPriceAscending_triggered();

    void on_showStatistics_triggered();

private:
    void closeEvent(QCloseEvent *event);
    Ui::MainWindow *ui;
    QFile* openedFile;
    bool fileIsOpened = false;
    QLabel* statusLabel;
    BikeList *list = nullptr;
};
#endif // MAINWINDOW_H
