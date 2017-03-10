#ifndef SERVERS_H
#define SERVERS_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<QtNetwork>
#include<QPainter>
#include<QtMultimedia>
#include <QAudioBuffer>
#include<QIODevice>

namespace Ui {
class servers;
}

class servers : public QWidget
{
    Q_OBJECT

public:
    explicit servers(QWidget *parent = 0);
    ~servers();
    //void paintEvent(QPaintEvent *);

private:
    Ui::servers *ui;
    QUdpSocket *receiver;
    QUdpSocket *receiver1;
    QByteArray datagram;
    CvCapture *capture;
    QByteArray addata;
    QIODevice *y;
    QAudioOutput *output;
     QAudioDeviceInfo info2;
     QAudioFormat format;

private slots:
    void readPendingDatagrams();
    void hasdata();
};

#endif // SERVERS_H
