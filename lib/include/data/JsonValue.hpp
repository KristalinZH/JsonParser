#ifndef JSONVALUE
#define JSONVALUE

#include<iostream>
#include<string>

class JsonObject;
class JsonArray;

enum class ValueType{
    Null,
    Boolean,
    Int,
    Double,
    String,
    Array,
    Object
};

class JsonValue{
    public:
        JsonValue();
        explicit JsonValue(const bool _value);
        explicit JsonValue(const int _value);
        explicit JsonValue(const double _value);
        explicit JsonValue(const char* const _value);
        explicit JsonValue(const std::string& _value);
        explicit JsonValue(const JsonArray& _value);
        explicit JsonValue(const JsonObject& _value);
        JsonValue(const JsonValue& other);
        JsonValue& operator=(const JsonValue& other);
        JsonValue(JsonValue&& other) noexcept;
        JsonValue& operator=(JsonValue&& other) noexcept;
        ~JsonValue();

        ValueType getType()const;
        void setType(const ValueType& _type);

        bool getBValue()const;
        int getIValue()const;
        double getDValue()const;
        std::string getSValue()const;
        JsonArray getAValue()const;
        JsonObject getOValue()const;
        
        void setBValue(const bool _value);
        void setIValue(const int _value);
        void setDValue(const double _value);
        void setSValue(const std::string& _value);
        void setAValue(const JsonArray& _value);
        void setOValue(const JsonObject& _value);

        friend std::ostream& operator<<(std::ostream& os, const JsonValue& jsonValue);
    private:
        ValueType type;
        union {
            bool* booleanValue;
            int* inumValue;
            double* dnumValue;
            std::string* strValue;
            JsonArray* jsonArrayValue;
            JsonObject* jsonObjectValue;
        } value;

        void clearValue();
        void setValue(const JsonValue& other);
};

#endif