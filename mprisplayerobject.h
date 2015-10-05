#ifndef MPRISPLAYEROBJECT_H
#define MPRISPLAYEROBJECT_H

#include "googlemusicplayer.h"

#include <QObject>

struct MprisStatus;

class MprisPlayerObject : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.MediaPlayer")
public:
    MprisPlayerObject(GoogleMusicPlayer *player, QObject *parent);

signals:

public slots:
    void Next();
    void Prev();
    void Pause();
    void Play();
    void PlayPause();
    MprisStatus getStatus();
protected:
    GoogleMusicPlayer *player;
};

struct MprisStatus
{
    int state;
    int random;
};

#endif // MPRISPLAYEROBJECT_H
