#include "CJsonParse.h"

#include <stdio.h>

//#include "Poco/JSON/Parser.h"
//#include "Poco/JSON/ParseHandler.h"
//#include "Poco/JSON/JSONException.h"
//#include "Poco/StreamCopier.h"
//#include "Poco/Dynamic/Var.h"
//#include "Poco/JSON/Query.h"
//#include "Poco/JSON/PrintHandler.h"

//using namespace Poco;

string& CJsonParse::sqlValue(string& sqlvalue, const string& value)
{
    sqlvalue += "'";
    sqlvalue += value;
    sqlvalue += "', ";
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const int& value)
{
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%d, ", value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const uint32_t& value)
{
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%ud, ", value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const float& value)
{
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%.2f, ", value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const double& value)
{
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%.2f, ", value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const bool& value)
{
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%d, ", value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const int64_t& value)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%ld, ", value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const uint64_t& value)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%lud, ", value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const string& key, const string& value)
{
    sqlvalue += key;
    sqlvalue += "='";
    sqlvalue += value;
    sqlvalue += "', ";
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const string& key, const int& value)
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "%s=%d, ", key.c_str(), value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const string& key, const uint32_t& value)
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "%s=%ud, ", key.c_str(), value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const string& key, const float& value)
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "%s=%.2f, ", key.c_str(), value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const string& key, const double& value)
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "%s=%.2f, ", key.c_str(), value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const string& key, const bool& value)
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "%s=%d, ", key.c_str(), value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const string& key, const int64_t& value)
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "%s=%ld, ", key.c_str(), value);
    sqlvalue += buf;
    return sqlvalue;
}

string& CJsonParse::sqlValue(string& sqlvalue, const string& key, const uint64_t& value)
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "%s=%lud, ", key.c_str(), value);
    sqlvalue += buf;
    return sqlvalue;
}

bool CJsonParse::json2Object(CObject *message, const string &req)
{
    try
    {
        Json::Value value;
        int ret = m_read->parse(req, value);
        if(ret == 0) {
            return false;
        }
        for(auto it : message->getKeyCVal()) {
            string key = it.first;
            CValue* val = it.second;

            if (val->value.type() == typeid(bool))
            {
                val->value = value[key].asBool();
            }
            else if (val->value.type() == typeid(int))
            {
                val->value = value[key].asInt();
            }
            else if (val->value.type() == typeid(float))
            {
                val->value = value[key].asDouble();
            }
            else if (val->value.type() == typeid(double))
            {
                val->value = value[key].asDouble();
            }
            else if (val->value.type() == typeid(string))
            {
                val->value = value[key].asString();
            }
        }
        return true;
    }
    catch (exception& exc)
    {
        std::cerr << exc.what() << std::endl;
    }
    return false;

    /*
    try
    {
        JSON::Parser parser;
        Dynamic::Var result;
        parser.reset();

        result = parser.parse(req);
        JSON::Object::Ptr pObj = result.extract<JSON::Object::Ptr>();

        for(auto it : message->getKeyCVal()) {
            string key = it.first;
            Dynamic::Var query_type = pObj->get(key);
            if (query_type.isEmpty()) {
                continue;
            }
            if(query_type.isBoolean()) {
                it.second->value = query_type.convert<bool>();
                continue;
            }
            if(query_type.isInteger()) {
                it.second->value = query_type.convert<int>();
                continue;
            }
            if(query_type.isNumeric()) {
                it.second->value = query_type.convert<float>();
                continue;
            }
            if(query_type.isString()) {
                it.second->value = query_type.toString();
                continue;
            }
        }
        return true;
    }
    catch (Poco::Exception& exc)
    {
        std::cerr << exc.displayText() << std::endl;
    }
*/
}

void CJsonParse::object2Json(const CObject *message, string &rep)
{
    Json::Value value;
    Json::Value obj;
    for(auto it : message->getKeyCVal()) {
        string key = it.first;
        CValue* val = it.second;
        if (val->value.type() == typeid(bool))
        {
            value[key] = boost::get<bool>(val->value);
        }
        else if (val->value.type() == typeid(int))
        {
            value[key] = boost::get<int>(val->value);
        }
        else if (val->value.type() == typeid(double))
        {
            value[key] = boost::get<double>(val->value);
        }
        else if (val->value.type() == typeid(string))
        {
            string tmp = boost::get<string>(val->value);
            if(tmp.empty()) {
                value[key] = obj;
            } else {
                value[key] = tmp;
            }
        }
    }
    rep = value.toStyledString();

    /*
    JSON::Object jsnObj;
    for(auto it : message->getKeyCVal()) {
        string key = it.first;
        CValue* val = it.second;
        if (val->value.type() == typeid(bool))
        {
            jsnObj.set(key, boost::get<bool>(val->value));
        }
        else if (val->value.type() == typeid(int))
        {
            jsnObj.set(key, boost::get<int>(val->value));
        }
        else if (val->value.type() == typeid(double))
        {
            jsnObj.set(key, boost::get<double>(val->value));
        }
        else if (val->value.type() == typeid(string))
        {
            string value = boost::get<string>(val->value);
            if(value.empty()) {
                jsnObj.set(key, Dynamic::Var());
            } else {
                jsnObj.set(key, value);
            }
        }
    }
    Dynamic::Var json(jsnObj);
    rep = json.toString();
*/
}

CJsonParse& CJsonParse::GetInstance()
{
    static CJsonParse ins;
    return ins;
}

CJsonParse::CJsonParse()
{
    m_read = new Json::Reader(Json::Features::strictMode());
}
