#include "playertrack.h"

PlayerTrack::PlayerTrack()
{

}

QString PlayerTrack::getArtist() const
{
    return artist;
}

void PlayerTrack::setArtist(const QString &value)
{
    artist = value;
}

QString PlayerTrack::getAlbum() const
{
    return album;
}

void PlayerTrack::setAlbum(const QString &value)
{
    album = value;
}

QString PlayerTrack::getTitle() const
{
    return title;
}

void PlayerTrack::setTitle(const QString &value)
{
    title = value;
}

