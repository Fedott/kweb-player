#ifndef MPRISPLAYEROBJECT_H
#define MPRISPLAYEROBJECT_H

#include "googlemusicplayer.h"

#include <QObject>

#include <amarok/DBusAbstractAdaptor.h>

struct MprisStatus;

class MprisPlayerObject : public DBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.MediaPlayer2.Player")

    Q_PROPERTY( QString PlaybackStatus READ PlaybackStatus )
    Q_PROPERTY( QVariantMap Metadata READ Metadata )
    Q_PROPERTY( qlonglong Position READ Position )
    Q_PROPERTY( bool CanGoNext READ CanGoNext )
    Q_PROPERTY( bool CanGoPrevious READ CanGoPrevious )
    Q_PROPERTY( bool CanPlay READ CanPlay )
    Q_PROPERTY( bool CanPause READ CanPause )
    Q_PROPERTY( bool CanControl READ CanControl )

public:
    MprisPlayerObject(GoogleMusicPlayer *player, QObject *parent);

signals:

public slots:
    void Next();
    void Previous();
    void Pause();
    void Play();
    void PlayPause();
    QString PlaybackStatus();
    QVariantMap Metadata();
    qlonglong Position();
    bool CanPlay();
    bool CanPause();
    bool CanGoNext();
    bool CanGoPrevious();
    bool CanOpen();
    bool CanControl();
protected:
    GoogleMusicPlayer *player;

protected slots:
    void metadataChanged();
    void playbackStatusChanged();
    void canPlayChanged();
    void canPauseChanged();
    void canGoNextChanged();
    void canGoPreviousChanged();
};

#endif // MPRISPLAYEROBJECT_H
