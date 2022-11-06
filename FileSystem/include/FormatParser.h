#pragma once

#include <QString>

#include <QJsonDocument>
#include <QJsonObject>

#include <QDomDocument>
#include <QDomElement>

enum Formats
{
   Json,
   Xml,
   Txt,
};

namespace Example
{
    struct Student
    {
        QString name;
        QString speciality;
        int age;
        int course;
    };
}

class FormatParser
{
public:
    FormatParser() = default;
    ~FormatParser() = default;

public:
    static QString serializeToJson(const Example::Student& student);
    static QString serializeToXml (const Example::Student& student);

    static bool validJson(const QString& data);
    static bool validXml (const QString& data);

private:
    static QDomElement createNodeWithName(const QString& name, const QString& value);
    static QDomElement createNodeWithName(const QString& name, const int value);
};
