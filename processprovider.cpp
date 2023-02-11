#include "processprovider.h"
#include <QProcess>

ProcessProvider::ProcessProvider(QObject *parent)
    : QObject{parent}
{

}

bool ProcessProvider::startDetached(const QString &exec, QStringList args)
{
    QProcess process;
    process.startDetached(exec, args);
    return process.isOpen();
}
