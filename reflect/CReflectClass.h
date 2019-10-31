#ifndef CREFLECTCLASS_H
#define CREFLECTCLASS_H

#include <boost/variant.hpp>

#include "config.h"
#include "stdtype.h"
#include "CObject.h"

#define DECLARE_CLASS_CREATE(class_name) \
CObject* CreateClass## class_name ();

#define IMPLEMENT_CLASS_CREATE(class_name) \
static CObject* CreateClass## class_name(){ \
    return new class_name; \
};

#define REGISTERED_CLASS_CREATE(class_name) \
ClassInfo* class_name::m_cInfo = new ClassInfo(#class_name, class_name::CreateClass## class_name);

//typedef decltype(nullptr)	nullptr_t;
#define Class2String(str) #str

#define IMPLEMENT_CLASS_NAME(class_name)    \
    virtual string className() override {   \
        return Class2String(class_name);    \
    }

#define INIT_VALUE(name)        init##name()

#define OBJECT(TYPE)            \
    public:                     \
    IMPLEMENT_CLASS_NAME(TYPE)  \
    private:                    \
    IMPLEMENT_CLASS_CREATE(TYPE)\
    static ClassInfo* m_cInfo;

class CValue
{
    typedef boost::variant<string, bool, int, float, double> CType;	//数据表中的值类型
public:
    CValue() {
        isSet = false;
        isQuery = false;
    }
    template<typename _T>
    void setVal(const _T& val) {
        value = val;
        isSet = true;
    }

public:
    bool    isSet;
    bool    isQuery;
    CType   value;
};

#define PROPERTY_BUILDER_BY_NAME(type, valname, access_permission) \
    access_permission:                              \
        CValue m_##valname;                         \
    public:                                         \
    inline void init##valname() {                   \
        m_keyCVal[#valname] = &m_##valname;         \
        if(strcasecmp(typeid(type).name(),          \
                      typeid(string).name()) != 0)  \
        {                                           \
            m_##valname.value = (type)0;            \
        }                                           \
    }                                               \
    inline void set##valname(const type& v) {       \
        m_##valname.value = v;                      \
        m_##valname.isSet = true;                   \
    }                                               \
    inline type get##valname() const {              \
        return boost::get<type>(m_##valname.value); \
    }                                               \
    inline void clear##valname() {                  \
        m_##valname.isSet = false;                  \
    }                                               \
    inline void set##valname##Query(const bool& b) {\
        m_##valname.isQuery = b;                    \
    }

#endif // CREFLECT_H
