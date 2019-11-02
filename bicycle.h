#ifndef BICYCLE_H
#define BICYCLE_H
#include <QString>
enum BicycleType
{
    MOUNTAIN_BIKE,
    ROAD_BIKE,
    GRAVEL_BIKE,
    CITY_BIKE,
    BMX,
    INVALID_TYPE
};

enum FrameSize
{
    XS_SIZE,
    S_SIZE,
    M_SIZE,
    L_SIZE,
    XL_SIZE,
    XXL_SIZE,
    INVALID_SIZE
};

enum BikeState
{
    NEW,
    USED,
    INVALID_STATE
};

class Bicycle
{
private:
    QString m_brand;
    QString m_model;
    BicycleType m_type;
    QString m_color;
    unsigned m_tyreDiameterInches; //possible values [16;29]
    FrameSize m_frameSize;
    BikeState m_state;
    unsigned m_price; //currency - USD
public:
    Bicycle(const Bicycle &copy);
    Bicycle(QString brand, QString model, BicycleType type, QString color,
            unsigned tyreDiameter, FrameSize size, BikeState state, unsigned price)
        :m_brand(brand), m_model(model), m_type(type), m_color(color),
          m_tyreDiameterInches(tyreDiameter), m_frameSize(size), m_state(state), m_price(price) {}
    QString getBrand() { return m_brand; }
    QString getModel() { return m_model; }
    BicycleType getType() { return m_type; }
    QString getTypeString();
    QString getColor() { return  m_color; }
    unsigned getTyreDiameter() { return m_tyreDiameterInches; }
    FrameSize getFrameSize() { return m_frameSize; }
    QString getFrameSizeString();
    bool isNew();
    QString getStateString();
    unsigned getPrice() { return m_price; }
};

BicycleType BicycleTypeFromString(QString str);
FrameSize FrameSizeFromString(QString str);
BikeState BikeStateFromString(QString str);
#endif // BICYCLE_H
