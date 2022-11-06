#include "FormatParser.h"

QString FormatParser::serializeToJson(const Example::Student& student)
{
    QJsonObject object;

    object.insert("Name", student.name);
    object.insert("Speciality", student.speciality);
    object.insert("Age", student.age);
    object.insert("Course", student.course);

    return QJsonDocument(object).toJson();
}

QString FormatParser::serializeToXml(const Example::Student& student)
{
    QDomDocument doc("xml");
    QDomElement root = doc.createElement("student");
    doc.appendChild(root);

    root.appendChild(createNodeWithName("Name", student.name));
    root.appendChild(createNodeWithName("Speciality", student.speciality));
    root.appendChild(createNodeWithName("Age", student.age));
    root.appendChild(createNodeWithName("Course", student.course));

    return doc.toString();
}

bool FormatParser::validJson(const QString& data)
{
    return !QJsonDocument::fromJson(data.toUtf8()).isNull();
}

bool FormatParser::validXml(const QString& data)
{
    return QDomDocument().setContent(data);
}

QDomElement FormatParser::createNodeWithName(const QString& name, const QString& value)
{
    QDomElement element = QDomDocument().createElement(name);
    element.appendChild(QDomDocument().createTextNode(value));

    return element;
}

QDomElement FormatParser::createNodeWithName(const QString& name, const int value)
{
    QDomElement element = QDomDocument().createElement(name);
    element.appendChild(QDomDocument().createTextNode(QString::number(value)));

    return element;
}
