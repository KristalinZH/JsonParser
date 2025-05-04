#ifndef JSONARRAY
#define JSONARRAY

#include <vector>
#include "JsonValue.hpp"

class JsonArray{
    public:
        JsonArray();
        explicit JsonArray(const std::vector<JsonValue>& _objectData);
        JsonArray(const JsonArray& other);
        JsonArray& operator=(const JsonArray& other);
        JsonArray(JsonArray&& other) noexcept;
        JsonArray& operator=(JsonArray&& other) noexcept;
        ~JsonArray();

        size_t getSize() const;
        JsonValue& operator[](const size_t index);
        const JsonValue& operator[](const size_t index) const;
        void addValue(const JsonValue& value);

        friend std::ostream& operator<<(std::ostream& os, const JsonArray& jsonArray);
    private:
        std::vector<JsonValue> arrayData;
};

#endif