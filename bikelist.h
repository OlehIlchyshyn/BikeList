#ifndef BIKELIST_H
#define BIKELIST_H
#include <QVector>
#include <QTextStream>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include "bicycle.h"
#include "addnewbikedialog.h"

class BikeList
{
private:
    QVector<Bicycle> m_list;
public:
    BikeList();
    int getLength();
    Bicycle at(int index);
    void fillFromFile(QFile *file);
    void saveToFile(QFile *file);
    void addNewElement(Bicycle bike);
    void clear();
    void removeAt(int index);
    bool isEmpty();
    void sortByMarks(bool descending = false);
    QVector<Bicycle> findByBrand(QString brand);
    QVector<Bicycle> findByType(BicycleType type);
    QVector<Bicycle> findByTyreDiameter(unsigned tyreDiam);
    QVector<Bicycle> findByFrameSize(FrameSize size);
    QString findMostCommonColour();
};


#endif // BIKELIST_H
