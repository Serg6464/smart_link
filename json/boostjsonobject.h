#ifndef BOOSTJSONOBJECT_H
#define BOOSTJSONOBJECT_H

#include <ijsonobject.h>

class BoostJsonObject;
using BoostJsonObjectPtr = std::shared_ptr<BoostJsonObject>;

class BoostJsonObject : public IJsonObject
{
    JsonPtr _json;
public:
    BoostJsonObject(JsonPtr json)
        :_json(json)
    { };
    static inline BoostJsonObjectPtr Create()
    {
        return std::make_shared<BoostJsonObject>(std::make_shared<Json>(boost::json::object()) );
    }

    // IJsonObject interface
public:
    JsonPtr getJson()
    {
        return _json;
    }
};

#endif // BOOSTJSONOBJECT_H
