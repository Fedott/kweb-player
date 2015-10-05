#include "mprisplayerobject.h"

MprisPlayerObject::MprisPlayerObject(GoogleMusicPlayer *player, QObject *parent) : QObject(parent)
{
    this->player = player;
}

void MprisPlayerObject::Next()
{
    player->next();
}

void MprisPlayerObject::Prev()
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

MprisStatus MprisPlayerObject::getStatus()
{
    MprisStatus status;

    return status;
}
