#include "bicycle.h"

Bicycle::Bicycle(const Bicycle &copy)
{
    m_brand = copy.m_brand;
    m_model = copy.m_model;
    m_type = copy.m_type;
    m_color = copy.m_color;
    m_tyreDiameterInches = copy.m_tyreDiameterInches;
    m_frameSize = copy.m_frameSize;
    m_state = copy.m_state;
    m_price = copy.m_price;
}

QString Bicycle::getTypeString()
{
    switch (m_type)
    {
    case ROAD_BIKE:
        return QString("Шоссе");
    case MOUNTAIN_BIKE:
        return QString("Гірський");
    case GRAVEL_BIKE:
        return QString("Гравійний");
    case CITY_BIKE:
        return QString("Міський");
    case BMX:
        return QString("BMX");
    }
}

QString Bicycle::getFrameSizeString()
{
    switch(m_frameSize)
    {
    case XS_SIZE:
        return QString("XS");
    case S_SIZE:
        return QString("S");
    case M_SIZE:
        return QString("M");
    case L_SIZE:
        return QString("L");
    case XL_SIZE:
        return QString("XL");
    case XXL_SIZE:
        return QString("XXL");
    }
}

bool Bicycle::isNew()
{
    if (m_state == NEW)
        return true;
    else return false;
}

QString Bicycle::getStateString()
{
    if (m_state == NEW)
        return QString("Новий");
    else
        return QString("Б/В");
}

BicycleType BicycleTypeFromString(QString str)
{
    if (str == "Шоссе")
        return ROAD_BIKE;
    if (str == "Гірський")
        return MOUNTAIN_BIKE;
    if (str == "Гравійний")
        return GRAVEL_BIKE;
    if (str == "Міський")
        return CITY_BIKE;
    if (str == "BMX")
        return BMX;
    else return INVALID_TYPE;
}

FrameSize FrameSizeFromString(QString str)
{
    if (str == "XS")
        return XS_SIZE;
    if (str == "S")
        return S_SIZE;
    if (str == "M")
        return M_SIZE;
    if (str == "L")
        return L_SIZE;
    if (str == "XL")
        return XL_SIZE;
    if (str == "XXL")
        return XXL_SIZE;
    else return INVALID_SIZE;
}

BikeState BikeStateFromString(QString str)
{
    if (str == "Новий")
        return NEW;
    if (str == "Б/В")
        return USED;
    else return INVALID_STATE;
}
