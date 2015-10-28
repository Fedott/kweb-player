#include "googlemusicplayer.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

GoogleMusicPlayer::GoogleMusicPlayer(QWebEngineView *browser)
    : QObject(browser)
{
    this->browser = browser;
    this->status = new PlayerStatus(this->browser);

    QFile file;
    file.setFileName(":/google-play-music.js");
    file.open(QIODevice::ReadOnly);
    playerControlCode = file.readAll();
    file.close();

    connect(browser, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    this->browser->load(QUrl("https://play.google.com/music/listen"));
}

void GoogleMusicPlayer::finishLoading(bool)
{
    getPage()->runJavaScript(playerControlCode);

    qDebug() << "PageLoaded";

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(updateStatus()));
    timer->start(500);
}

void GoogleMusicPlayer::playPause()
{
    jsClickButton("play-pause");
}

void GoogleMusicPlayer::next()
{
    jsClickButton("forward");
}

void GoogleMusicPlayer::prev()
{
    jsClickButton("rewind");
}

void GoogleMusicPlayer::trumbsUp()
{
    jsQuerySelectorClick(".player-rating-container paper-icon-button[data-rating=5]");
}

void GoogleMusicPlayer::trumbsDown()
{
    jsQuerySelectorClick(".player-rating-container paper-icon-button[data-rating=1]");
}

void GoogleMusicPlayer::shuffle()
{
    jsClickButton("shuffle");
}

void GoogleMusicPlayer::setVolume(double volume)
{
    int normalizeVolume = (int) (volume * 100);
    QString action = QString("value = %1").arg(normalizeVolume);
    QString code = getJsQuerySelectorAction("#material-vslider", action);

    getPage()->runJavaScript(code);
}

void GoogleMusicPlayer::updateStatus()
{
    QString code = QString("GPMgetPlayerStatus();");
    getPage()->runJavaScript(code, [this](const QVariant &result){
        if (result.isValid()) {
            QJsonDocument jsonDocument = QJsonDocument::fromJson(result.toString().toUtf8());
            QJsonObject json = jsonDocument.object();

            this->getStatus()->setMetadata(
                    json["songTitle"].toString(),
                    json["songArtist"].toString(),
                    json["songAlbum"].toString(),
                    json["artLocation"].toString(),
                    json["progressMax"].toString().toLongLong(),
                    json["progressMin"].toString().toLongLong()
                )
                ->setCanNext(json["canNext"].toBool())
                ->setCanPrev(json["canPrev"].toBool())
                ->setDisabled(json["disabled"].toBool())
                ->setPlaying(json["playing"].toBool())
                ->setVolume(json["volume"].toInt())
                ->setProgressNow(json["progressNow"].toString().toLongLong())
            ;
        }
    });
}

PlayerStatus* GoogleMusicPlayer::getStatus()
{
    return status;
}

QWebEnginePage *GoogleMusicPlayer::getPage()
{
    return browser->page();
}

QString GoogleMusicPlayer::getJsQuerySelectorAction(QString selector, QString actionCode)
{
    QString code = QString("document.querySelector('%1').%2;").arg(selector, actionCode);
    return code;
}

void GoogleMusicPlayer::jsQuerySelectorClick(QString selector)
{
    QString code = getJsQuerySelectorAction(selector, "click()");
    getPage()->runJavaScript(code);
}

QString GoogleMusicPlayer::getJsButtonSelector(QString button)
{
    return QString("paper-icon-button[data-id=%1]").arg(button);
}

void GoogleMusicPlayer::jsClickButton(QString button)
{
    QString selector = getJsButtonSelector(button);
    jsQuerySelectorClick(selector);
}
