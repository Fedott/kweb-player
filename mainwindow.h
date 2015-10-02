#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QWebEngineView *browser;

protected slots:
    void playPausePlayer();
    void initWebPlayer();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
