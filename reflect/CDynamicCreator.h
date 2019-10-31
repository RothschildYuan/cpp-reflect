#ifndef CDYNAMICCREATOR_H
#define CDYNAMICCREATOR_H

#include "CObjectFactory.h"

template<typename T, typename ...Targs>
class CDynamicCreator
{
public:
    struct Register
    {
        Register()
        {
            char* szDemangleName = nullptr;
            string szRegistName;
#ifdef __GNUC__
#include <cxxabi.h>
            szDemangleName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
			if (nullptr == szDemangleName) {
				return;
			}
			szRegistName = szDemangleName;
			free(szDemangleName);
#else
            //in this format?:     
            const char* pname = typeid(T).name();
			if (strcasestr(pname, "class") != nullptr) {
				szRegistName = pname + 6;
			}
			else {
				szRegistName = pname;
			}
            cout<<"\n\n***************\n szDemangleName: "<< szRegistName <<"\n\n";
            //szDemangleName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
#endif
			CObjectFactory<Targs...>::GetInstance()->Regist(szRegistName, CreateObject);
        }
        inline void do_nothing() const {

        }
    };

    CDynamicCreator()
    {
        m_oRegister.do_nothing();
    }

    virtual ~CDynamicCreator(){
        m_oRegister.do_nothing();
    }

    static T* CreateObject(Targs&&... args)
    {
        return new T(std::forward<Targs>(args)...);
    }

private:
    static Register m_oRegister;
};

template<typename T, typename ...Targs>
typename CDynamicCreator<T, Targs...>::Register CDynamicCreator<T, Targs...>::m_oRegister;

#endif // CDYNAMICCREATOR_H
