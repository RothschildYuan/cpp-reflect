#ifndef CJSONPARSE_H
#define CJSONPARSE_H

#include "CObject.h"
#include "config.h"
#include "configure.h"

#include "json/reader.h"
#include "json/writer.h"

class ACT_CPP_DLL_API CJsonParse
{
    string& sqlValue(string& sqlvalue, const string& value);
    string& sqlValue(string& sqlvalue, const int& value);
    string& sqlValue(string& sqlvalue, const uint32_t& value);
    string& sqlValue(string& sqlvalue, const float& value);
    string& sqlValue(string& sqlvalue, const double& value);
    string& sqlValue(string& sqlvalue, const bool& value);
    string& sqlValue(string& sqlvalue, const int64_t& value);
    string& sqlValue(string& sqlvalue, const uint64_t& value);

    string& sqlValue(string& sqlvalue, const string& key, const string& value);
    string& sqlValue(string& sqlvalue, const string& key, const int& value);
    string& sqlValue(string& sqlvalue, const string& key, const uint32_t& value);
    string& sqlValue(string& sqlvalue, const string& key, const float& value);
    string& sqlValue(string& sqlvalue, const string& key, const double& value);
    string& sqlValue(string& sqlvalue, const string& key, const bool& value);
    string& sqlValue(string& sqlvalue, const string& key, const int64_t& value);
    string& sqlValue(string& sqlvalue, const string& key, const uint64_t& value);
public:

    bool json2Object(CObject* message, const string& req);
    void object2Json(const CObject* message, string& rep);

    static CJsonParse& GetInstance();
private:
    CJsonParse();
    CJsonParse(const CJsonParse&);
    CJsonParse& operator=(const CJsonParse&);

    Json::FastWriter m_write;
    Json::Reader* m_read;
};

#endif // PROTOBUFPARSE_H
