#ifndef seaport_passenger_H
#define seaport_passenger_H

#include "stdtype.h"
#include "CObjectFactory.h"
#include "CDynamicCreator.h"

/**
  设备详细表
 * @brief The seaport_passenger class
 */
class seaport_passenger: public CObject, public CDynamicCreator<seaport_passenger>
{
public:
    seaport_passenger();

    IMPLEMENT_CLASS_NAME(seaport_passenger)

    PROPERTY_BUILDER_BY_NAME(int, id, private)
    PROPERTY_BUILDER_BY_NAME(string, passengerName, private)
    PROPERTY_BUILDER_BY_NAME(string, passengerCardType, private)
    PROPERTY_BUILDER_BY_NAME(string, passengerIdCard, private)
    PROPERTY_BUILDER_BY_NAME(string, passengerAddr, private)
    PROPERTY_BUILDER_BY_NAME(string, passengerBirthDay, private)
    PROPERTY_BUILDER_BY_NAME(string, passengerGender, private)
    PROPERTY_BUILDER_BY_NAME(string, passengerMobile, private)
    PROPERTY_BUILDER_BY_NAME(string, passengerEmail, private)
};

#endif // seaport_passenger_H
