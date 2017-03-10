#include "dialog.h"
#include "ui_dialog.h"
#include<linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include <cv.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

      capture = cvCreateCameraCapture(0);
     //打开摄像头

      connect(&timer,SIGNAL(timeout()),this,SLOT(showImage()));
      //当Qtime调用timeout时，调用showImage

      sender = new QUdpSocket(this);

      sender->bind(6667,QUdpSocket::ShareAddress);
      //绑定6667端口

      sender1 = new QUdpSocket(this);

      sender1->bind(6666,QUdpSocket::ShareAddress);
     //sender1绑定6666端口
      format.setSampleRate(8000);
      format.setChannelCount(1);
      format.setSampleSize(8);
      format.setCodec("audio/pcm");
      format.setByteOrder(QAudioFormat::LittleEndian);
      format.setSampleType(QAudioFormat::SignedInt);
     //设置采集格式
      info =QAudioDeviceInfo::defaultInputDevice();
      if (!info.isFormatSupported(format))
          format = info.nearestFormat(format);
      info = QAudioDeviceInfo::defaultOutputDevice();
      if (!info.isFormatSupported(format))
          format = info.nearestFormat(format);
      //找到输入输出驱动

      input = new QAudioInput(format,this);
      //创建语音输入
      output = new QAudioOutput(format,this);
      //创建语音输出
      input->setBufferSize(2000);
      //设置输入缓冲区大小为1024

       x=input->start();
       //开启输入，从输入设备读取
      connect(x,SIGNAL(readyRead()),this,SLOT(audioDataReady()));
      //当有输入信号时调用audioDataReady

      y=output->start();
      //同理

}

Dialog::~Dialog()
{
    delete ui;

}
void Dialog::showImage()
{

       im = cvQueryFrame(capture);
       //捕获当前摄像头的图像
       update();
       //刷新
       sender->writeDatagram(data,data.length(),QHostAddress::Broadcast,6667);
       //udp以广播形式向6667端口发送信息



       if(!datagram.isEmpty())
       {
          y->write(datagram);//把数据写入声卡，播放
       }
      sender1->writeDatagram(datagram,datagram.length(),QHostAddress::Broadcast,6666);
      //传输二进制声音

}
void Dialog::paintEvent(QPaintEvent *)
{


        QBuffer buf(&data);
        buf.open(QIODevice::WriteOnly);
        //buf用只写方式打开
        QImage img =ConvertToQImage(im);
        //调用ConvertToQImage方法，把IplImage（opencv的格式）转化成QImage格式
        QPainter painter(this);
        painter.drawImage(-1,-1,img);
        //Qpainter显示img
        img.save(&buf,"jpg",-1);
        //img通过Qbuffer保存到data中（QByteArray）
}

void Dialog::on_send_clicked()
{

   timer.start(33);
   //33毫秒一次，30帧\s，超时调用timeout（）;




}
QImage Dialog::ConvertToQImage(IplImage *iplImg)//格式转换
{

    QImage img;
    int nChannel=iplImg->nChannels;

    if(nChannel==3)
    {
     // cvConvertImage(iplImg,iplImg,CV_BGR2RGB);
   // cvConvertImage(iplImg,iplImg,CV_CVTIMG_SWAP_RB);
    img = QImage((const unsigned char*)iplImg->imageData,iplImg->width,iplImg->height,QImage::Format_RGB888).rgbSwapped();
    }
    else if(nChannel==4||nChannel==1)
    {
      //  cvConvertImage(iplImg,iplImg,CV_CVTIMG_SWAP_RB);
    img = QImage((const unsigned char*)iplImg->imageData,iplImg->width,iplImg->height,QImage::Format_ARGB32).rgbSwapped();
       //  img = QImage((const unsigned char*)iplImg->imageData,iplImg->width,iplImg->height,QImage::Format_RGB888);

    }
    return img;
}
void Dialog::audioDataReady()
{
    datagram.clear();
   //datagram = x->readAll();
    len1 = input->bytesReady();
    //获得读取数据的长度

    if(2000 <= len1)
    {
       x->read(datagram.data(), 2000);
       //长度大于缓冲区，只读缓存区大小
    }else
    {
     datagram=  x->readAll();
     //读取全部
    }

}

void Dialog::on_end_clicked()//点击结束按钮
{
  timer.stop();//停止计时，不会再调用timeout（）;
  input->stop();//停止输入
}
