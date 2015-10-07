#ifndef TRAYICON_H
#define TRAYICON_H

#include "kstatusnotifieritem.h"

class TrayIcon : public KStatusNotifierItem
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = 0);

signals:

public slots:
};

#endif // TRAYICON_H
