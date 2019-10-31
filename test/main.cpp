#include <iostream>
#include <stdio.h>

#include "seaport_car_info.h"
#include "seaport_passenger.h"
#include "CJsonParse.h"

using namespace std;

void cppreflect() {
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

    cout<<"\n 33333333333333333333333333333333 \n\n";

    string rep;
    seaport_car_info car_info;
    car_info.setid(15);
    car_info.setoptor_id(12);
    car_info.setoptor_code("12345");
    car_info.setoptor_name("987645");
    car_info.setcar_no("粤A12345");
    car_info.setcar_color("2");
    car_info.setcar_type("1");
    car_info.setcar_length(1.5);
    car_info.setcar_width(2.5);
    car_info.setcar_height(3.5);
    car_info.setcar_weight(4.5);
    car_info.setcrea_time("2019-10-31 10:29:00");
    cout<<&car_info;
    CJsonParse::GetInstance().object2Json(&car_info, rep);
    cout << "\n**" << rep << "**\n\n\n";
}

int main() {
    cppreflect();
    return 0;
}
