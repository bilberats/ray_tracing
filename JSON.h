//
// Created by leroy on 29/05/2023.
//
#include <cstring>
#include <vector>

#ifndef RAY_TRACING_JSON_H
#define RAY_TRACING_JSON_H


class JSON {
    typedef struct{
        JSON* j;
        std::string name;
    }jsonCont;
private:
    bool onlyValue;
    bool isList;
    std::string value;
    std::vector<jsonCont> contained;
    std::vector<JSON> list;

    void addContained(const std::string& text,std::string name,bool isOnlyValue);
    void addList(const std::string& text,bool isOnlyValue);
    void resetValues();

public:
    //constructors
    JSON();
    explicit JSON(std::string text);
    JSON(const std::string& text,bool _onlyValue);
    //destructor
    ~JSON()=default;

    //methods
    void parseFile(const std::string& filePath);
    void parseChars(std::string text);
    void parseCharsSingleValue(const std::string& text);
    void printContent(int depth);
    void setValue(std::string newValue);
    int getLength();
    std::string getValue();

    //operators
    JSON& operator=(std::string text);
    JSON& operator[](const char *name);
    JSON& operator[](int index);
};



#endif //RAY_TRACING_JSON_H
