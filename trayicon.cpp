#include "trayicon.h"

#include <qicon.h>

TrayIcon::TrayIcon(QObject *parent)
    : KStatusNotifierItem(parent)
{
    setIconByPixmap(QIcon(":/icon/icon64.png"));
    setStatus(KStatusNotifierItem::Active);
}
