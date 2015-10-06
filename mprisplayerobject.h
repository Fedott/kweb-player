#ifndef MPRISPLAYEROBJECT_H
#define MPRISPLAYEROBJECT_H

#include "googlemusicplayer.h"

#include <QObject>

#include <amarok/DBusAbstractAdaptor.h>

class MprisPlayerObject : public DBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")

    Q_PROPERTY( QString PlaybackStatus READ PlaybackStatus )
    Q_PROPERTY( QVariantMap Metadata READ Metadata )
    Q_PROPERTY( qlonglong Position READ Position )
    Q_PROPERTY( bool CanGoNext READ CanGoNext )
    Q_PROPERTY( bool CanGoPrevious READ CanGoPrevious )
    Q_PROPERTY( bool CanPlay READ CanPlay )
    Q_PROPERTY( bool CanPause READ CanPause )
    Q_PROPERTY( bool CanControl READ CanControl )
    Q_PROPERTY( double Rate READ Rate )
    Q_PROPERTY( double Volume READ Volume WRITE setVolume )

public:
    MprisPlayerObject(GoogleMusicPlayer *player, QObject *parent);

signals:

public slots:
    void Next();
    void Previous();
    void Pause();
    void Play();
    void PlayPause();
    void Seek(qlonglong Offset);
    QString PlaybackStatus();
    QVariantMap Metadata();
    qlonglong Position();
    double Rate();
    double Volume();
    void setVolume(double volume);
    bool CanPlay();
    bool CanPause();
    bool CanGoNext();
    bool CanGoPrevious();
    bool CanOpen();
    bool CanControl();
    bool CanSeek();
protected:
    GoogleMusicPlayer *player;

protected slots:
    void metadataChanged();
    void playbackStatusChanged();
    void canPlayChanged();
    void canPauseChanged();
    void canGoNextChanged();
    void canGoPreviousChanged();
    void positionChanged();
    void volumeChanged();
};

class MprisObject : public DBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2")

    Q_PROPERTY(bool CanRaise READ CanRaise)
    Q_PROPERTY(bool CanQuit READ CanQuit)
    Q_PROPERTY(QString Identity READ Identity)
    Q_PROPERTY(QString DesktopEntry READ DesktopEntry)

public:
    MprisObject(QObject *parent);

public slots:
    void Raise();
    void Quit();
    bool CanRaise();
    bool CanQuit();
    QString Identity();
    QString DesktopEntry();
};

#endif // MPRISPLAYEROBJECT_H
