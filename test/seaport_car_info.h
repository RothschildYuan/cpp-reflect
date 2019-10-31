#ifndef SEAPORT_CAR_INFO_H
#define SEAPORT_CAR_INFO_H

#include "stdtype.h"
#include "CObjectFactory.h"
#include "CDynamicCreator.h"

class seaport_car_info: public CObject, public CDynamicCreator<seaport_car_info>
{
public:
    seaport_car_info();

    IMPLEMENT_CLASS_NAME(seaport_car_info)

    PROPERTY_BUILDER_BY_NAME(int, id, private)
    PROPERTY_BUILDER_BY_NAME(int, optor_id, private)
    PROPERTY_BUILDER_BY_NAME(string, optor_code, private)
    PROPERTY_BUILDER_BY_NAME(string, optor_name, private)
    PROPERTY_BUILDER_BY_NAME(string, car_no, private)
    PROPERTY_BUILDER_BY_NAME(string, car_color, private)
    PROPERTY_BUILDER_BY_NAME(string, car_type, private)
    PROPERTY_BUILDER_BY_NAME(float, car_length, private)
    PROPERTY_BUILDER_BY_NAME(float, car_width, private)
    PROPERTY_BUILDER_BY_NAME(float, car_height, private)
    PROPERTY_BUILDER_BY_NAME(float, car_weight, private)
    PROPERTY_BUILDER_BY_NAME(string, crea_time, private)
};

#endif // seaport_car_info_H
