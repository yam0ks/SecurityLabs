#pragma once

#include <QStorageInfo>

class DiskManager
{
public:
    DiskManager() = default;
    ~DiskManager() = default;

public:
    static QList<QStorageInfo> volumesInfo();
    static QString logicDisksInfoToStr();
};
