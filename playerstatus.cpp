#include "playerstatus.h"

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

void PlayerStatus::setCanControl(bool value)
{
    canControl = value;
}

void PlayerStatus::setVolume(int value)
{
    double normalizeValue = (double) value / 100;
    if (volume != normalizeValue) {
        volume = (double) normalizeValue;
        emit volumeChanged();
    }
}

void PlayerStatus::changeCanPlayPause()
{
    setCanPause(playing);
    setCanPlay(!disabled && !playing);
}

void PlayerStatus::setCanOpen(bool value)
{
    if (canOpen != value) {
        canOpen = value;
        emit canOpenChanged();
    }
}

void PlayerStatus::setCanPrev(bool value)
{
    if (canPrev != value) {
        canPrev = value;
        emit canPrevChanged();
    }
}

void PlayerStatus::setCanNext(bool value)
{
    if (canNext != value) {
        canNext = value;
        emit canNextChanged();
    }
}

void PlayerStatus::setCanPause(bool value)
{
    if (canPause != value) {
        canPause = value;
        emit canPauseChanged();
    }
}

void PlayerStatus::setCanPlay(bool value)
{
    if (canPlay != value) {
        canPlay = value;
        emit canPlayChanged();
    }
}

void PlayerStatus::setProgressMin(const qlonglong &value)
{
    if (progressMin != value) {
        progressMin = value;
        emit metadataChanged();
    }
}

void PlayerStatus::setProgressNow(const qlonglong &value)
{
    if (progressNow != value) {
        progressNow = value;
//        emit positionChanged();
    }
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

void PlayerStatus::setPlaying(bool value)
{
    if (playing != value) {
        playing = value;
        emit playbackStatusChanged();
    }
}

void PlayerStatus::setDisabled(bool value)
{
    if (disabled != value) {
        disabled = value;
        emit playbackStatusChanged();
    }
}
