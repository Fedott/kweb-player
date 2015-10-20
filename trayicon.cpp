#include "trayicon.h"

#include <qicon.h>

TrayIcon::TrayIcon(QObject *parent)
    : KStatusNotifierItem(parent)
{
    setIconByPixmap(QIcon(":/icon/kweb-player-icon-flat-headphones.png"));
    setStatus(KStatusNotifierItem::Active);
}
