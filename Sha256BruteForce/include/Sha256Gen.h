#pragma once

#include <QObject>
#include <QString>
#include <QFile>

struct Task;

class Sha256Gen : public QObject
{
Q_OBJECT

public:
    Sha256Gen() = default;
    ~Sha256Gen() = default;

public:
    static QMultiMap<QString, QString> bruteForce(const QStringList& hashes, int threadCount);

private:
    static QString bruteForceImpl(const QString& hash, int threadCount, QFile* file);
    static QString threadForce(const Task& task);
    static void reduceResult(QString& result, const QString& local);
};
