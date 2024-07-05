#include <iostream>
#include <string>
#include <vector>
#include "tinyxml2.h"

using namespace tinyxml2;

class XmlSerializer {
public:
    template <typename T>
    static void writeElement(XMLElement* parentElem, const std::string& elementName, const T& value) {
        XMLElement* elem = parentElem->GetDocument()->NewElement(elementName.c_str());
        elem->SetText(value);
        parentElem->InsertEndChild(elem);
    }

    template <>
    static void writeElement(XMLElement* parentElem, const std::string& elementName, const std::string& value) {
        XMLElement* elem = parentElem->GetDocument()->NewElement(elementName.c_str());
        elem->SetText(value.c_str());
        parentElem->InsertEndChild(elem);
    }

    template <typename T>
    static void readElement(XMLElement* parentElem, const std::string& elementName, T& value) {
        XMLElement* elem = parentElem->FirstChildElement(elementName.c_str());
        if (elem) {
            value = std::stoi(elem->GetText());
        }
    }

    template <>
    static void readElement(XMLElement* parentElem, const std::string& elementName, std::string& value) {
        XMLElement* elem = parentElem->FirstChildElement(elementName.c_str());
        if (elem) {
            value = elem->GetText();
        }
    }

    template <typename T>
    static void writeElementArray(XMLElement* parentElem, const std::string& elementName, const T& object) {
        XMLElement* elem = parentElem->GetDocument()->NewElement(elementName.c_str());
        object.toXml(elem);
        parentElem->InsertEndChild(elem);
    }

    template <typename T>
    static void writeElementArray(XMLElement* parentElem, const std::string& elementName, const std::vector<T>& objects) {
        XMLElement* vectorElem = parentElem->GetDocument()->NewElement(elementName.c_str());
        for (const auto& object : objects) {
            writeElementArray(vectorElem, elementName + "Item", object);
        }
        parentElem->InsertEndChild(vectorElem);
    }

    template <typename T>
    static void readElementArray(XMLElement* parentElem, const std::string& elementName, T& object, bool array = false) {
        XMLElement* elem;
        if (array)
        {
            elem = parentElem;
        } 
        else
        {
           elem = parentElem->FirstChildElement(elementName.c_str());
        }
        if (elem) {
            object.fromXml(elem);
        }
    }

    template <typename T>
    static void readElementArray(XMLElement* parentElem, const std::string& elementName, std::vector<T>& objects) {
       XMLElement* objectElem = parentElem->FirstChildElement(elementName.c_str());
       for (XMLElement* elem = objectElem->FirstChildElement(); elem; elem = elem->NextSiblingElement())
       {
           T object;
           readElementArray(elem, elem->Name(), object, true);
           objects.push_back(object);
       }
    }

    template <typename T>
    static std::string Serialize(const T& object) {
        XMLDocument doc;
        XMLElement* rootElem = doc.NewElement("Root");
        object.toXml(rootElem);
        doc.InsertEndChild(rootElem);

        XMLPrinter printer;
        doc.Accept(&printer);

        return printer.CStr();
    }

    template <typename T>
    static void Deserialize(const std::string& xml, T& object) {
        XMLDocument doc;
        doc.Parse(xml.c_str());

        XMLElement* rootElem = doc.RootElement();
        if (rootElem) {
            object.fromXml(rootElem);
        }
    }
};