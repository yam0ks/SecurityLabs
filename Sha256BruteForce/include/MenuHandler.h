#pragma once

#include <QStringList>

class MenuHandler
{
public:
    MenuHandler() = default;
    ~MenuHandler() = default;

public:
    static void execStartMenu();

private:
    enum InputType
    {
        Stream,
        File,
    };

private:
    static void execBruteForce(InputType type);

    static QStringList readFromFile();
    static QStringList readFromStream();
};
