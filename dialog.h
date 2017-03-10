#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<linux/videodev2.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "libv4l2.h"
#include "libv4lconvert.h"
#include <QImage>
#include <QTimer>
#include <QPainter>
#include<QtNetwork>
#include<QByteArray>
#include<QtMultimedia>
#include <QAudioBuffer>
#include<QIODevice>
using namespace cv;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void paintEvent(QPaintEvent *);

    QImage ConvertToQImage(IplImage *iplImg);
private:
      Ui::Dialog *ui;
      QTimer timer;
      QUdpSocket *sender;
       QUdpSocket *sender1;
      QByteArray datagram;
      IplImage *frame;
      CvCapture *capture;
      IplImage *image ;
      IplImage  *im;
      QByteArray data;
      QAudioFormat format;
      QAudioDeviceInfo info;
      QAudioInput *input;
      QAudioOutput *output;
      QIODevice *x;
      QIODevice *y;
      char *buffer;

       qint64 len1;
private slots:
    void showImage();
    void on_send_clicked();
    void audioDataReady();

    void on_end_clicked();
};

#endif // DIALOG_H
