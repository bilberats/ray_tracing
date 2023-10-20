//
// Created by leroy on 29/05/2023.
//

#include <iostream>
#include "JSON.h"

JSON::JSON()
        :onlyValue(true),
         isList(false)
{}

JSON::JSON(std::string text)
        :onlyValue(false),
         isList(false)
{
    parseChars(std::move(text));
}

JSON::JSON(const std::string& text,bool _onlyValue)
        :onlyValue(_onlyValue),
         isList(false)
{
    if(_onlyValue){
        parseCharsSingleValue(text);
    }else{
        parseChars(text);
    }
}


void JSON::parseFile(const std::string& filePath) {
    std::cout<<filePath<<std::endl;
    resetValues();
    FILE* f =fopen(filePath.c_str(), "r+");

    std::string text;
    int length=1;
    char c;
    if(f!= nullptr){
        c=(char)fgetc(f);
        while(c != EOF){
            text += c;
            c=(char)fgetc(f);
            length++;
        }
        parseChars(text);
    }else{
        printf("Can't open file");
    }
}


void JSON::parseChars(std::string text) {
    resetValues();
    int i=0,depth=0,normalDepth;

    bool nameStart=false;
    bool valueStart=false;
    bool isOnlyValue=true;
    bool quoteOpened=false;

    std::string name;
    std::string jsonCache;

    normalDepth=0;
    if(text[0]=='{'){
        normalDepth = 1;
    }
    if(text[0]=='['){
        isList=true;
        normalDepth = 1;
        depth++;
        i++;
    }
    while(i<text.length()){
        switch(text[i]){
            case '\n':i++;continue;
            case '{':depth++;if(i!=0)isOnlyValue=false;break;
            case '}':
                depth--;
                if(depth<=normalDepth && text[i+1]!=',' && !quoteOpened){
                    if(!isOnlyValue){
                        jsonCache += '}';
                    }
                    valueStart=false;
                    if(isList){
                        addList(jsonCache,isOnlyValue);
                    }else{
                        addContained(jsonCache,name,isOnlyValue);
                    }
                    name="";
                    jsonCache= "";

                    isOnlyValue=true;
                }
                break;
            case '[':
                depth++;
                if(depth<=normalDepth){
                    valueStart=true;
                }
                if(i!=0)isOnlyValue=false;
                break;
            case ']':
                depth--;
                if(depth<=normalDepth && text[i+1]!=',' && !quoteOpened){
                    if(!isOnlyValue){
                        jsonCache += ']';
                    }
                    valueStart=false;

                    if(isList){
                        if(text[i-1]!='}'){
                            addList(jsonCache,isOnlyValue);
                        }
                    }else{
                        addContained(jsonCache,name,isOnlyValue);
                    }
                    name= "";
                    jsonCache= "";

                    isOnlyValue=true;
                }
                break;
            case '"':
                //check if quotes opens
                quoteOpened=!quoteOpened;
                if(!valueStart){
                    nameStart=!nameStart;
                }
                break;
            case ':':valueStart=true;break;
            case ',':
                //check if it is the end of an argument the depth is the most important parameter
                if(depth<=normalDepth && !quoteOpened){
                    valueStart=false;
                    if(isList){
                        addList(jsonCache,isOnlyValue);
                    }else{
                        addContained(jsonCache,name,isOnlyValue);
                    }

                    name= "";
                    jsonCache= "";

                    isOnlyValue=true;
                }
                break;
        }
        if(text[i]==' ' && !quoteOpened){
            i++;
            continue;
        }
        //add chars to the json cache of sill defining it
        if((valueStart || isList) && !((text[i]==':' || text[i]==',') && depth==normalDepth)){
            jsonCache += text[i];
        }
        //add chars to the name if still defining the name
        if(nameStart){
            name+=text[i];
        }

        //increments i
        i++;
    }
}

void JSON::parseCharsSingleValue(const std::string& text) {
    for(char i : text){
        if(i!='"'){
            value += i;
        }
    }
}


void JSON::setValue(std::string newValue) {
    value = std::move(newValue);
}

void JSON::addContained(const std::string& text,std::string name,bool isOnlyValue) {
    std::string noQuoteName;
    for(char i : name){
        if(i!='"'){
            noQuoteName += i;
        }
    }

    jsonCont newCont;
    JSON *newJson = new JSON(text,isOnlyValue);
    newCont.j = newJson;
    newCont.name = std::move(noQuoteName);

    contained.push_back(newCont);
}


void JSON::addList(const std::string& text,bool isOnlyValue) {
    JSON newEl=JSON(text,isOnlyValue);
    list.push_back(newEl);
}


void JSON::resetValues() {
    onlyValue=false;
    isList=false;
    value="";
    contained.clear();
    list.clear();
}

void JSON::printContent(int depth) {
    if(onlyValue){
        std::cout<<value;
    }else if(isList){
        std::cout<<"[";
        for(int i=0;i<list.size();i++){
            std::cout<<"\n";
            for(int j=0;j<depth;j++){
                std::cout<<"    ";
            }
            list[i].printContent(depth);
            if(i!=list.size()-1){
                std::cout<<",";
            }
        }
        std::cout<<"\n";
        for(int j=0;j<depth;j++){
            std::cout<<"    ";
        }
        std::cout<<"]";
    }else{
        std::cout<<"{";
        for(int i=0;i<contained.size();i++){
            std::cout<<"\n";
            for(int j=0;j<depth+1;j++){
                std::cout<<"    ";
            }
            std::cout<<"\""<<contained[i].name<<"\": ";
            contained[i].j->printContent(depth+1);
            if(i!=contained.size()-1){
                std::cout<<",";
            }
        }
        std::cout<<"\n";
        for(int j=0;j<depth;j++){
            std::cout<<"    ";
        }
        std::cout<<"}";
    }
}

std::string JSON::getValue() {
    if(!onlyValue){
        std::cout<<"This JSON is not a single value"<<std::endl;
        exit(1);
    }
    return value;
}

JSON &JSON::operator=(std::string text) {
    parseChars(std::move(text));
    return *this;
}

JSON &JSON::operator[](const char *name) {
    if(isList){
        std::cout<<"This JSON is a list"<<std::endl;
        exit(1);
    }
    for(int i = 0;i<contained.size();i++){
        if(contained[i].name==name){
            return *contained[i].j;
        }
    }
    std::cout<<"No "<<name<<" found in this JSON"<<std::endl;
    exit(1);
}

JSON &JSON::operator[](int index) {
    if(!isList){
        std::cout<<"This JSON isn't a list"<<std::endl;
        exit(1);
    }else if(index<list.size()){
        return list[index];
    }else{
        std::cout<<"Index out of bound"<<std::endl;
        exit(139);
    }
}

int JSON::getLength() {
    if(!list.empty()){
        return list.size();
    }else{
        return -1;
    }
}
