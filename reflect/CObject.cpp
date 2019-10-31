#include "CObject.h"

CObject::CObject() {

}

CObject::~CObject() {

}

void CObject::clear()
{
    for(auto it : m_keyCVal) {
        CValue* tmp = it.second;
        if(tmp->isSet) {
            tmp->isSet = false;
        }
    }
}

unordered_map<string, CValue *> CObject::getKeyCVal() const
{
    return m_keyCVal;
}

ostream &operator <<(ostream &os, const CObject *msg) {
    for(auto it : msg->m_keyCVal) {
        string key = it.first;
        CValue* val = it.second;
        if (val->value.type() == typeid(bool))
        {
            os<<key<<" : "<<boost::get<bool>(val->value)<<endl;
        }
        else if (val->value.type() == typeid(int))
        {
            os<<key<<" : "<<boost::get<int>(val->value)<<endl;
        }
        else if (val->value.type() == typeid(float))
        {
            os<<key<<" : "<<boost::get<float>(val->value)<<endl;
        }
        else if (val->value.type() == typeid(double))
        {
            os<<key<<" : "<<boost::get<double>(val->value)<<endl;
        }
        else if (val->value.type() == typeid(string))
        {
            os<<key<<" : "<<boost::get<string>(val->value)<<endl;
        }
    }
    return os;
}
