#include "DiskManager.h"

QList<QStorageInfo> DiskManager::volumesInfo()
{
    return QStorageInfo::mountedVolumes();
}

QString DiskManager::logicDisksInfoToStr()
{
    QString result;

    const auto volumes = volumesInfo();

    for (const QStorageInfo& volume : volumes)
    {
        result += volume.name() + '\n';
        result += volume.rootPath() + '\n';
        result += QString::number(volume.bytesTotal()) + '\n';
        result += volume.fileSystemType() + "\n\n";
    }

    return result;
}
