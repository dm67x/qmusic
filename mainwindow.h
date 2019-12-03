#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow* ui;
    QString m_filename;
    QMediaPlayer m_player;
    QPoint m_lastPosition;
    std::vector<QString> m_musics;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openBtn_clicked();
    void on_volumeSlider_valueChanged(int value);
    void on_playBtn_clicked();
    void on_pauseBtn_clicked();
    void positionChanged(qint64);
    void durationChanged(qint64);
    void sliderMoved(int);
    void exitBtnClicked();
    void itemDoubleClicked(QListWidgetItem*);

private:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
};
#endif // MAINWINDOW_H
