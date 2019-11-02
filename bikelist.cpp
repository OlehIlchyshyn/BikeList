#include "bikelist.h"

BikeList::BikeList()
{

}

Bicycle BikeList::at(int index)
{
    if (index>=0 && index < m_list.length())
        return m_list.at(index);
    else
    {
        QMessageBox::critical(nullptr, "Критична помилка", "Був здійснений вихід за межі списку");
        QApplication::quit();
    }
}

void BikeList::fillFromFile(QFile *file)
{
    QTextStream in(&*file);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    int lineCount = 0;
    bool openForEditing = false;
    while(!in.atEnd())
    {
        lineCount++;

        QString brand, model, type, uaType, color, uaColor, frameSize, state, uaState;
        int tyreDiameter, price;
        in >> brand >> model >> type >> color;
        in >> tyreDiameter >> frameSize >> state >> price;
        BicycleType enType = BicycleTypeFromString(type);
        FrameSize enSize = FrameSizeFromString(frameSize);
        BikeState enState = BikeStateFromString(state);
        QString line = in.readLine();
        line.remove(' ');
        if (!line.isEmpty())
        {
            QMessageBox::warning(0,"Упс...","Було знайдено лишні дані під час читання файлу у рядку"
                                                 " " + QString::number(lineCount) + ".\n"
                                                 "Дані буде відкинуто, і програма продовжить роботу у звичному режимі.");
        }
        Bicycle temp(brand, model, enType, color, tyreDiameter, enSize, enState, price);
        m_list.append(temp);
        /*
        switch(temp.validate())
        {
        case VALIDATION_SUCCESS:
            m_list->append(temp);
            break;
        case SURNAME_ERROR:
            if (QMessageBox::warning(0,"Упс...","Було знайдено помилку у прізвищі під час читання файлу у рядку"
                                     " " + QString::number(lineCount) + ".\n"
                                     "Виправте помилку та спробуйте відкрити файл ще раз.") == QMessageBox::Ok)
            {
                openForEditing = true;
            }
            break;
        case NAME_ERROR:
            if (QMessageBox::warning(0,"Упс...","Було знайдено помилку у імені під час читання файлу у рядку"
                                     " " + QString::number(lineCount) + ".\n"
                                     "Виправте помилку та спробуйте відкрити файл ще раз.") == QMessageBox::Ok)
            {
                openForEditing = true;
            }
            break;
        case DATE_ERROR:
            if (QMessageBox::warning(0,"Упс...","Було знайдено помилку у даті під час читання файлу у рядку"
                                     " " + QString::number(lineCount) + ".\n"
                                     "Виправте помилку та спробуйте відкрити файл ще раз.") == QMessageBox::Ok)
            {
                openForEditing = true;
            }
            break;
        case MARKS_ERROR:
            if (QMessageBox::warning(0,"Упс...","Було знайдено помилку у оцінках під час читання файлу у рядку"
                                     " " + QString::number(lineCount) + ".\n"
                                     "Виправте помилку та спробуйте відкрити файл ще раз.") == QMessageBox::Ok)
            {
                openForEditing = true;
            }
            break;
        case ITEMS_COUNT_ERROR:
            if (QMessageBox::warning(0,"Упс...","Було знайдено помилку під час читання файлу у рядку"
                                     " " + QString::number(lineCount) + ".\n"
                                     "Виправте помилку та спробуйте відкрити файл ще раз.") == QMessageBox::Ok)
            {
                openForEditing = true;
            }
            break;
        }
        */
    }
    if(openForEditing)
    {
        file->close();
        QDesktopServices::openUrl(QUrl(file->fileName()));
    }
}

void BikeList::saveToFile(QFile *file)
{
    file->resize(0);
    QTextStream out(&*file);
    for (int i = 0; i < getLength(); ++i)
    {
        out << m_list[i].getBrand() << " ";
        out << m_list[i].getModel() << " ";
        out << m_list[i].getTypeString() << " ";
        out << m_list[i].getBrand() << " ";
        out << m_list[i].getColor() << " ";
        out << m_list[i].getTyreDiameter() << " ";
        out << m_list[i].getFrameSizeString() << " ";
        out << m_list[i].getStateString() << " ";
        out << m_list[i].getPrice();
        if (i != (getLength()-1)) out << '\n';
    }
}

void BikeList::addNewElement(Bicycle bike)
{
    m_list.append(bike);
}

void BikeList::clear()
{
    m_list.clear();
}

void BikeList::removeAt(int index)
{
    m_list.removeAt(index);
}

bool BikeList::isEmpty()
{
    return m_list.isEmpty();
}

void BikeList::sortByMarks(bool descending)
{
    int length = m_list.length();
    int j, step = length/2;
    while (step > 0)
    {
        for (int i = 0; i < (length - step); ++i)
        {
            j = i;
            while((j>=0) && (m_list[j].getPrice() > m_list[j+step].getPrice()))
            {
                std::swap(m_list[j], m_list[j+step]);
                j--;
            }
        }
        step /= 2;
    }
    if (descending)
        std::reverse(m_list.begin(), m_list.end());
}

QVector<Bicycle> BikeList::findByBrand(QString brand)
{
    QVector<Bicycle> vector;
    for (int i = 0; i < m_list.length(); ++i)
    {
        if (m_list[i].getBrand() == brand)
            vector.append(m_list[i]);
    }
    return vector;
}

QVector<Bicycle> BikeList::findByType(BicycleType type)
{
    QVector<Bicycle> vector;
    for (int i = 0; i < m_list.length(); ++i)
    {
        if (m_list[i].getType() == type)
            vector.append(m_list[i]);
    }
    return vector;
}

QVector<Bicycle> BikeList::findByTyreDiameter(unsigned tyreDiam)
{
    QVector<Bicycle> vector;
    for (int i = 0; i < m_list.length(); ++i)
    {
        if (m_list[i].getTyreDiameter() == tyreDiam)
            vector.append(m_list[i]);
    }
    return vector;
}

QVector<Bicycle> BikeList::findByFrameSize(FrameSize size)
{
    QVector<Bicycle> vector;
    for (int i = 0; i < m_list.length(); ++i)
    {
        if (m_list[i].getFrameSize() == size)
            vector.append(m_list[i]);
    }
    return vector;
}

QString BikeList::findMostCommonColour()
{
    if (isEmpty())
    {
        QMessageBox::warning(nullptr, "Ехххх:(", "Список порожній.");
        return "";
    }
    QVector<QString> colours;
    QVector<int> indeces(m_list.length());
    indeces.fill(0);
    for (int i = 0; i < m_list.length(); ++i)
    {
        QString colour = m_list[i].getColor();
        if (!colours.contains(colour))
            colours.push_back(colour);
        indeces[colours.indexOf(colour)]++;
    }
    int max = indeces[0];
    for (int i = 1; i < indeces.length(); ++i)
    {
        if (indeces[i] > max)
        {
            max = indeces[i];
        }
    }
    return colours.at(indeces.indexOf(max));
}

int BikeList::getLength()
{
    return m_list.length();
}
