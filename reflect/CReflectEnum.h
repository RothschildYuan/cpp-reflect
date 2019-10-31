#ifndef REFLECTENUM_H
#define REFLECTENUM_H

#include "common.h"
#include "stdtype.h"

#define _countof(x) (sizeof((x))/sizeof((x)[0]))

template <typename Enum_T> class EnumHelper
{
public:
    static const char * ToString(Enum_T e)
    {
        for(size_t i = 0; i < _countof(s_allEnums); i++)
        {
            if( s_allEnums[i] == e)
                return s_allEnumNames[i];
        }
        return nullptr;
    }

public:
    static const char * s_typeName;
    static Enum_T s_allEnums[];
    static char s_singleEnumStr[];
    static const char * s_allEnumNames[];

    static void SplitEnumDefString()
    {
        char * p = s_singleEnumStr;
        while( isspace(*p) ) p++;
        for(size_t i = 0; i < _countof(s_allEnums); i++)
        {
            s_allEnumNames[i] = p;
            while( *p == '_' || isdigit(*p) || isalpha(*p) ) p++;
            bool meet_comma = ( *p == ',' );
            *p++ = '\0';
            if( !meet_comma )
            {
                while( *p && *p != ',') p++;
                if( *p ) p++;
            }
            while( *p && isspace(*p) ) p++;
        }
    }
};

#define TO_ENUM_ITEM(...)  __VA_ARGS__
#define STRINGIZE(...)  #__VA_ARGS__

#define REFLECT_ENUM(enum_type_name, enum_list)                                                                         \
template<> enum_type_name EnumHelper<enum_type_name>::s_allEnums[] =                                                    \
{                                                                                                                       \
    TO_ENUM_ITEM(enum_list)                                                                                             \
};                                                                                                                      \
template<> const char* EnumHelper<enum_type_name>::s_allEnumNames[_countof(EnumHelper<enum_type_name>::s_allEnums)] = {0};  \
template<> char EnumHelper<enum_type_name>::s_singleEnumStr[] = STRINGIZE(enum_list) ;                                  \
template<> const char * EnumHelper<enum_type_name>::s_typeName = (EnumHelper<enum_type_name>::SplitEnumDefString(), #enum_type_name);

#endif // REFLECTENUM_H


