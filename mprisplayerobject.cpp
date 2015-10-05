#include "mprisplayerobject.h"

MprisPlayerObject::MprisPlayerObject(GoogleMusicPlayer *player, QObject *parent)
    : DBusAbstractAdaptor(parent)
{
    this->player = player;

    connect(player->getStatus(), SIGNAL(metadataChanged()), SLOT(metadataChanged()));
    connect(player->getStatus(), SIGNAL(playbackStatusChanged()), SLOT(playbackStatusChanged()));
    connect(player->getStatus(), SIGNAL(canPlayChanged()), SLOT(CanPlay()));
    connect(player->getStatus(), SIGNAL(canPauseChanged()), SLOT(CanPause()));
    connect(player->getStatus(), SIGNAL(canNextChanged()), SLOT(canGoNextChanged()));
    connect(player->getStatus(), SIGNAL(canPrevChanged()), SLOT(canGoPreviousChanged()));
}

void MprisPlayerObject::Next()
{
    player->next();
}

void MprisPlayerObject::Previous()
{
    player->prev();
}

void MprisPlayerObject::Pause()
{
    player->playPause();
}

void MprisPlayerObject::Play()
{
    player->playPause();
}

void MprisPlayerObject::PlayPause()
{
    player->playPause();
}

QString MprisPlayerObject::PlaybackStatus()
{
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

void MprisPlayerObject::metadataChanged()
{
    signalPropertyChange("Metadata", Metadata());
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
