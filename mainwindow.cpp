#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMouseEvent>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_filename(QString()),
    m_player(this)
{
    ui->setupUi(this);
    this->setWindowTitle("QMusic");
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | 
        Qt::WindowStaysOnTopHint);

    connect(&m_player, 
        SIGNAL(positionChanged(qint64)), this, 
        SLOT(positionChanged(qint64)));
    connect(&m_player,
        SIGNAL(durationChanged(qint64)), this,
        SLOT(durationChanged(qint64)));

    connect(ui->positionSlider,
        SIGNAL(sliderMoved(int)), this,
        SLOT(sliderMoved(int)));

    connect(ui->exitBtn,
        SIGNAL(clicked()), this,
        SLOT(exitBtnClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openBtn_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Music/Song (*.mp3)"));
    dialog.setViewMode(QFileDialog::ViewMode::Detail);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList filesList;
    if (dialog.exec()) {
        filesList = dialog.selectedFiles();
    }

    if (filesList.size() > 0) {
        m_filename = filesList[0];
        QFileInfo info(m_filename);
        ui->titleLbl->setText("QMusic - " + info.baseName());
        ui->playBtn->setEnabled(true);

        m_player.setMedia(QUrl::fromLocalFile(m_filename));
    }
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    ui->volumeLbl->setText(QString::number(value) + " %");
    m_player.setVolume(value);
}

void MainWindow::on_playBtn_clicked()
{
    if (m_player.state() != QMediaPlayer::State::PlayingState) {
        m_player.play();
        ui->pauseBtn->setEnabled(true);
        ui->playBtn->setEnabled(false);
    }
}

void MainWindow::on_pauseBtn_clicked()
{
    if (m_player.state() == QMediaPlayer::State::PlayingState) {
        m_player.pause();
        ui->pauseBtn->setEnabled(false);
        ui->playBtn->setEnabled(true);
    }
}

void MainWindow::positionChanged(qint64 p)
{
    int seconds = ui->positionSlider->maximum() - p;
    seconds /= 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    ui->durationLbl->setText(
        QString("%1").arg(minutes, 2, 10, QChar('0')) + ":" +
        QString("%1").arg(seconds, 2, 10, QChar('0')));

    ui->positionSlider->setValue(p);
}

void MainWindow::durationChanged(qint64 duration)
{
    int seconds = duration / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    ui->positionSlider->setMaximum(duration);
    ui->durationLbl->setText(
        QString("%1").arg(minutes, 2, 10, QChar('0')) + ":" +
        QString("%1").arg(seconds, 2, 10, QChar('0')));
}

void MainWindow::sliderMoved(int p)
{
    m_player.setPosition(p);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    m_lastPosition = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() && Qt::LeftButton) {
        QPoint diff = event->pos() - m_lastPosition;
        QPoint newPos = this->pos() + diff;
        this->move(newPos);
    }
}

void MainWindow::exitBtnClicked()
{
    QApplication::instance()->exit();
}
