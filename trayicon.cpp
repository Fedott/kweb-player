#include "trayicon.h"

#include <qicon.h>

TrayIcon::TrayIcon(QObject *parent)
    : KStatusNotifierItem(parent)
{
    setIconByPixmap(QIcon(":/icon.png"));
    setStatus(KStatusNotifierItem::Active);
}
