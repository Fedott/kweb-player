#include "mprisplayerobject.h"

MprisPlayerObject::MprisPlayerObject(GoogleMusicPlayer *player, QObject *parent)
    : DBusAbstractAdaptor(parent)
{
    this->player = player;

    connect(player->getStatus(), SIGNAL(metadataChanged()), SLOT(metadataChanged()));
    connect(player->getStatus(), SIGNAL(playbackStatusChanged()), SLOT(playbackStatusChanged()));
    connect(player->getStatus(), SIGNAL(positionChanged()), SLOT(positionChanged()));
    connect(player->getStatus(), SIGNAL(canPlayChanged()), SLOT(CanPlay()));
    connect(player->getStatus(), SIGNAL(canPauseChanged()), SLOT(CanPause()));
    connect(player->getStatus(), SIGNAL(canNextChanged()), SLOT(canGoNextChanged()));
    connect(player->getStatus(), SIGNAL(canPrevChanged()), SLOT(canGoPreviousChanged()));
    connect(player->getStatus(), SIGNAL(volumeChanged()), SLOT(volumeChanged()));
}

void MprisPlayerObject::Next()
{
    qDebug() << "Next";
    player->next();
}

void MprisPlayerObject::Previous()
{
    qDebug() << "Previous";
    player->prev();
}

void MprisPlayerObject::Pause()
{
    qDebug() << "Pause";
    player->playPause();
}

void MprisPlayerObject::Play()
{
    qDebug() << "Play";
    player->playPause();
}

void MprisPlayerObject::PlayPause()
{
    qDebug() << "PlayPause";
    player->playPause();
}

void MprisPlayerObject::Seek(qlonglong Offset)
{
    qDebug() << "Seek" << Offset;
}

QString MprisPlayerObject::PlaybackStatus()
{
    qDebug() << "PlaybackStatus";
    return player->getStatus()->getState();
}

QVariantMap MprisPlayerObject::Metadata()
{
    PlayerStatus* status = player->getStatus();
    QVariantMap metadata = QVariantMap();
    metadata.insert("mpris:length", status->progressMax);
    metadata.insert("mpris:artUrl", status->art);
    metadata.insert("xesam:album", status->album);
    metadata.insert("xesam:artist", status->artist);
    metadata.insert("xesam:title", status->title);

    return metadata;
}

qlonglong MprisPlayerObject::Position()
{
    return player->getStatus()->progressNow;
}

double MprisPlayerObject::Rate()
{
    return 1.0;
}

double MprisPlayerObject::Volume()
{
    return player->getStatus()->volume;
}

void MprisPlayerObject::setVolume(double volume)
{
    player->setVolume(volume);
}

bool MprisPlayerObject::CanPlay()
{
    return player->getStatus()->canPlay;
}

bool MprisPlayerObject::CanPause()
{
    return player->getStatus()->canPause;
}

bool MprisPlayerObject::CanGoNext()
{
    return player->getStatus()->canNext;
}

bool MprisPlayerObject::CanGoPrevious()
{
    return player->getStatus()->canPrev;
}

bool MprisPlayerObject::CanOpen()
{
    return true; // FIXME
}

bool MprisPlayerObject::CanControl()
{
    return true; // FIXME
}

bool MprisPlayerObject::CanSeek()
{
    return false; // FIXME
}

void MprisPlayerObject::metadataChanged()
{
    qDebug() << "metadataChanged";
    signalPropertyChange("Metadata", Metadata());
    signalPropertyChange("Position", Position());
}

void MprisPlayerObject::playbackStatusChanged()
{
    signalPropertyChange("PlaybackStatus", PlaybackStatus());
}

void MprisPlayerObject::canPlayChanged()
{
    signalPropertyChange("CanPlay", CanPlay());
}

void MprisPlayerObject::canPauseChanged()
{
    signalPropertyChange("CanPause", CanPause());
}

void MprisPlayerObject::canGoNextChanged()
{
    signalPropertyChange("CanGoNext", CanGoNext());
}

void MprisPlayerObject::canGoPreviousChanged()
{
    signalPropertyChange("CanGoPrevious", CanGoPrevious());
}

void MprisPlayerObject::positionChanged()
{
    signalPropertyChange("Position", Position());
}

void MprisPlayerObject::volumeChanged()
{
    signalPropertyChange("Volume", Volume());
}

MprisObject::MprisObject(QObject *parent)
    : DBusAbstractAdaptor(parent)
{

}

void MprisObject::Raise()
{
    qDebug() << "Raise";
}

void MprisObject::Quit()
{
    qDebug() << "Quit";
}

bool MprisObject::CanRaise()
{
    return false; // FEXME
}

bool MprisObject::CanQuit()
{
    return false; // FIXME
}

QString MprisObject::Identity()
{
    return QString("KWeb-player");
}

QString MprisObject::DesktopEntry()
{
    return QLatin1String("kweb-player");
}
