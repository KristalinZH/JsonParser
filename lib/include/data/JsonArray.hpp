#ifndef JSONARRAY
#define JSONARRAY

#include <vector>
#include "JsonValue.hpp"

class JsonArray : public JsonValue {
    public:
        ValueType getType() const override;
        JsonValue* clone() const override;
        void print(std::ostream& stream) const override;
        void accept(JsonValueVisitor& visitor) override;

        JsonArray() = default;
        JsonArray(const std::vector<JsonValue*>& _arrayData);
        JsonArray(const JsonArray& other);
        JsonArray& operator=(const JsonArray& other);
        JsonArray(JsonArray&& other) noexcept;
        JsonArray& operator=(JsonArray&& other) noexcept;
        ~JsonArray();

        size_t getSize() const;
        JsonValue* operator[](const size_t index);
        const JsonValue* operator[](const size_t index) const;
        void addValue(const JsonValue* const value);     
    private:
        std::vector<JsonValue*> values;

        void copyData(const std::vector<JsonValue*>& _arrayData);
        void resetData(std::vector<JsonValue*>& _arrayData);
        void deleteData();
};


#endif