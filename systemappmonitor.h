#ifndef SYSTEMAPPMONITOR_H
#define SYSTEMAPPMONITOR_H

#include <QObject>
#include "systemappitem.h"

class SystemAppMonitor : public QObject
{
    Q_OBJECT
public:
    explicit SystemAppMonitor(QObject *parent = nullptr);
    ~SystemAppMonitor();

    static SystemAppMonitor *self();

    SystemAppItem *find(const QString &filePath);
    QList<SystemAppItem *> applications() const { return m_items; }
signals:
    void refreshed();
private:
    void refresh();
    void addApplication(const QString &filePath);
    void removeApplication(SystemAppItem *item);
public:
    QList <SystemAppItem *> m_items;
};

#endif // SYSTEMAPPMONITOR_H
