#include "Json.hpp"

JsonEditor Json::editor;
JsonParser Json::parser;
JsonPrinter Json::printer;
JsonSearcher Json::searcher;
JsonSerializer Json::serializer;
JsonValidator Json::validator; 

// static Json parse(std::istream& stream);

// static std::pair<bool, std::string> validate(std::istream& stream);

// std::string print();

// std::pair<bool, std::string> search(const std::regex& reg);

// std::pair<bool, std::string> set(const std::string& path, const std::string value);

// std::pair<bool, std::string> create(const std::string& path, const std::string value);

// std::pair<bool, std::string> erase(const std::string& path);

// std::pair<bool, std::string> move(const std::string& from, const std::string& to);

// std::pair<bool, std::string> save(std::ostream& stream, const std::string& path = "");