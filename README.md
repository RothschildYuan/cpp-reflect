![](./res/cpp-reflect.png)

**cpp-reflect 完美实现 cpp 反射机制，解决通过类名创建类，获取类中的成员属性（类型，值，成员名）**

# Features
* 使用c++11新特性，使用到可变模块参数传参
* 完美实现 cpp 反射机制，依赖于 boost 库
* 采用宏定义方式实现 cpp 反射，需支持反射的类必须继承于 CObject 反射类
* 支持Linux和windows（目前所有文件都是跨平台的，后续添加windows编译文件）

**WARNING: **
> 实现必须依赖 boost 库，所以在使用前必须先提供 boost 库，并指定 boost 动态库路径地址
> 下载并提供 boost 库，修改 Makefile 文件，继续修改下面三步骤即可 make 编译
> 指定 boost 头文件路径： INCLUDES += -I ../include 
> 指定 boost 动态库路径： LIBS += -L. ../lib/libboost/libboost_serialization.so
> 						  LIBS += -L. ../lib/libboost/libboost_system.so

# Building
```
make
```

# Test
测试前需要修改 test/main.cpp 中的数据库账号密码
```
cd cpp-reflect  
make  
./CppReflect
```

# Usage
使用libevent-cpp能够非常方便的创建一个http服务器，比如如下例子创建一个简单的静态http文件服务器
```c++
# seaport_passenger.h
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

# seaport_passenger.cpp
seaport_passenger::seaport_passenger()
{
    INIT_VALUE(id);
    INIT_VALUE(passengerName);
    INIT_VALUE(passengerCardType);
    INIT_VALUE(passengerIdCard);
    INIT_VALUE(passengerAddr);
    INIT_VALUE(passengerBirthDay);
    INIT_VALUE(passengerGender);
    INIT_VALUE(passengerMobile);
    INIT_VALUE(passengerEmail);
}


#include <iostream>
#include <stdio.h>

#include "seaport_car_info.h"
#include "seaport_passenger.h"
#include "CJsonParse.h"

using namespace std;

int main() {
    // 根据类名创建对象
    seaport_passenger* pref = (seaport_passenger*)CreateObject("seaport_passenger");
    if(pref != nullptr) {
        // 获取该对象类名（字符串）
        cout<<endl<<pref->className()<<"\n\n";

        int    id                   = 2;
        string passengerName        = "qianwang";
        string passengerCardType    = "1";
        string passengerIdCard      = "429001199311197766";
        string passengerAddr        = "湖北天门";
        string passengerBirthDay    = "1992-11-13";
        string passengerGender      = "1";
        string passengerMobile      = "13048896858";
        string passengerEmail       = "1294870180@qq.com";

        pref->setid                 (id);
        pref->setpassengerName      (passengerName);
        pref->setpassengerCardType  (passengerCardType);
        pref->setpassengerIdCard    (passengerIdCard);
        pref->setpassengerAddr      (passengerAddr);
        pref->setpassengerBirthDay  (passengerBirthDay);
        pref->setpassengerGender    (passengerGender);
        pref->setpassengerMobile    (passengerMobile);
        pref->setpassengerEmail     (passengerEmail);

        // 打印对象所有字段和值
        cout << endl << pref << endl;

        string rep;
        // 通过cpp反射实现 对象转换为 json
        CJsonParse::GetInstance().object2Json(pref, rep);
        cout<<rep<<endl;
        seaport_passenger tmp;
        // 通过cpp反射实现 json 转换为 对象
        CJsonParse::GetInstance().json2Object(&tmp, rep);
        cout << endl << &tmp << endl;

        delete pref;
    }

    cout<<"\n 11111111111111111111111111111 \n\n";

    // 没有定义对应的 Step 类，所有创建对象失败，nullptr
    CObject* pref2 = CreateObject("Step", string("Step"), 1002);
    if(pref2 != nullptr) {
        // 如果定义了 Step 类，则创建成功，获取该对象类名（字符串）
        cout<<pref2->className()<<endl;
        delete pref2;
    } else {
        cout<<"\n\n 没有定义对应的 Step 类，所有创建对象失败，nullptr"<<endl<<endl;
    }

    cout<<"\n 2222222222222222222222222222222 \n\n";

    // 没有定义对应的 Step 类，所有创建对象失败，nullptr
    CObject* pCar_info = CreateObject("seaport_car_info");
    if(pCar_info != nullptr) {
        // 如果定义了 Step 类，则创建成功，获取该对象类名（字符串）
        cout<<pCar_info->className()<<endl<<endl;
        cout<<pCar_info<<endl;
        delete pCar_info;
    }
	return 0;
}
```
