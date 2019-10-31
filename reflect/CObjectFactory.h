#ifndef COBJECTFACTORY_H
#define COBJECTFACTORY_H

#include "CObject.h"

template<typename ...Targs>
class CObjectFactory
{
public:
    static CObjectFactory* GetInstance()
    {
        if (nullptr == m_pCObjectFactory)
        {
            m_pCObjectFactory = new CObjectFactory();
        }
        return(m_pCObjectFactory);
    }

    virtual ~CObjectFactory() {

    }

    bool Regist(const string& strTypeName, function<CObject*(Targs&&... args)> pFunc)
    {
        if (nullptr == pFunc)
        {
            return false;
        }
        string strRealTypeName = strTypeName;
        bool bReg = m_mapCreateFunction.insert(make_pair(strRealTypeName, pFunc)).second;
        cout << "Init Class " << strRealTypeName << " RegistAllCount: " << m_mapCreateFunction.size() << endl;
        return bReg;
    }

    CObject* CreateObject(const string& strTypeName, Targs&&... args)
    {
        auto iter = m_mapCreateFunction.find(strTypeName);
        if (iter == m_mapCreateFunction.end())
        {
            return nullptr;
        }
        else
        {
            return iter->second(forward<Targs>(args)...);
        }
    }

private:
    CObjectFactory() {}
    static CObjectFactory<Targs...>* m_pCObjectFactory;
    unordered_map<string, function<CObject*(Targs&&...)> > m_mapCreateFunction;
};

template<typename ...Targs>
CObjectFactory<Targs...>* CObjectFactory<Targs...>::m_pCObjectFactory = nullptr;

template<typename ...Targs>
CObject* CreateObject(const string& strTypeName, Targs&&... args)
{
    CObject* p = CObjectFactory<Targs...>::GetInstance()->CreateObject(strTypeName, forward<Targs>(args)...);
    return p;
}

#endif // COBJECTFACTORY_H
