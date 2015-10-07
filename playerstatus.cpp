#include "playerstatus.h"
#include <QDebug>

PlayerStatus::PlayerStatus(QObject *parent)
    : QObject(parent)
{
    connect(this, SIGNAL(playbackStatusChanged()), SLOT(changeCanPlayPause()));
}

PlayerStatus::~PlayerStatus()
{
}

QString PlayerStatus::getState()
{
    if (disabled) {
        return QLatin1String("Stopped");
    } else if (playing) {
        return QLatin1String("Playing");
    } else {
        return QLatin1String("Paused");
    }
}

PlayerStatus *PlayerStatus::setCanControl(bool value)
{
    canControl = value;
    return this;
}

PlayerStatus *PlayerStatus::setVolume(int value)
{
    double normalizeValue = (double) value / 100;
    if (volume != normalizeValue) {
        volume = (double) normalizeValue;
        emit volumeChanged();
    }

    return this;
}

PlayerStatus *PlayerStatus::changeCanPlayPause()
{
    setCanPause(playing);
    setCanPlay(!disabled && !playing);

    return this;
}

PlayerStatus *PlayerStatus::setCanOpen(bool value)
{
    if (canOpen != value) {
        canOpen = value;
        emit canOpenChanged();
    }

    return this;
}

PlayerStatus *PlayerStatus::setCanPrev(bool value)
{
    if (canPrev != value) {
        canPrev = value;
        emit canPrevChanged();
    }

    return this;
}

PlayerStatus *PlayerStatus::setCanNext(bool value)
{
    if (canNext != value) {
        canNext = value;
        emit canNextChanged();
    }

    return this;
}

PlayerStatus *PlayerStatus::setCanPause(bool value)
{
    if (canPause != value) {
        canPause = value;
        emit canPauseChanged();
    }

    return this;
}

PlayerStatus *PlayerStatus::setCanPlay(bool value)
{
    if (canPlay != value) {
        canPlay = value;
        emit canPlayChanged();
    }

    return this;
}

void PlayerStatus::setProgressMin(const qlonglong &value)
{
    if (progressMin != value) {
        progressMin = value;
        emit metadataChanged();
    }
}

PlayerStatus *PlayerStatus::setProgressNow(const qlonglong &value)
{
    if (progressNow != value) {
        progressNow = value;
//        emit positionChanged();
    }

    return this;
}

void PlayerStatus::setProgressMax(const qlonglong &value)
{
    if (progressMax != value) {
        progressMax = value;
        emit metadataChanged();
    }
}

void PlayerStatus::setArt(const QString &value)
{
    if (art != value) {
        art = value;
        emit metadataChanged();
    }
}

void PlayerStatus::setAlbum(const QString &value)
{
    if (album != value) {
        album = value;
        emit metadataChanged();
    }
}

void PlayerStatus::setArtist(const QString &value)
{
    if (artist != value) {
        artist = value;
        emit metadataChanged();
    }
}

void PlayerStatus::setTitle(const QString &value)
{
    if (title != value) {
        title = value;
        emit metadataChanged();
    }
}

PlayerStatus *PlayerStatus::setMetadata(
        QString songTitle,
        QString songArtist,
        QString songAlbum,
        QString songArt,
        qlonglong songProgressMax,
        qlonglong songProgressMin
) {
    if (title != songTitle) {
        title = songTitle;
        artist = songArtist;
        album = songAlbum;
        art = songArt;
        progressMax = songProgressMax;
        progressMin = songProgressMin;

        emit metadataChanged();
    }

    return this;
}

PlayerStatus *PlayerStatus::setPlaying(bool value)
{
    if (playing != value) {
        playing = value;
        emit playbackStatusChanged();
    }

    return this;
}

PlayerStatus *PlayerStatus::setDisabled(bool value)
{
    if (disabled != value) {
        disabled = value;
        emit playbackStatusChanged();
    }

    return this;
}
