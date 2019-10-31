#ifndef _COBJECT_H
#define _COBJECT_H

#include "config.h"
#include "stdtype.h"
#include "CReflectClass.h"

class CObject
{
    friend ostream &operator <<(ostream &os, const CObject* msg);
public:
    CObject();
    virtual ~CObject();

    virtual string className() = 0;

public:
    void clear();

    unordered_map<string, CValue*> getKeyCVal() const;
protected:
    unordered_map<string, CValue*> m_keyCVal;
};

ostream &operator <<(ostream &os, const CObject* msg);

#endif // COBJECT_H
