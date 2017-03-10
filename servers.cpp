#include "servers.h"
#include "ui_servers.h"
#include <cv.h>
#include <QPixmap>
//#pragma comment(lib,"ws2_32.lib")
servers::servers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::servers)
{
    ui->setupUi(this);
    receiver = new QUdpSocket(this);
    receiver->bind(6667,QUdpSocket::ShareAddress);
    //udp绑定6667端口

    receiver1 = new QUdpSocket(this);
    receiver1->bind(6666,QUdpSocket::ShareAddress);

    connect(receiver, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
    //当有数据传来，调用readPendingDatagrams()

    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    //设置采集格式

    info2 = QAudioDeviceInfo::defaultOutputDevice();
    if (!info2.isFormatSupported(format))
        format = info2.nearestFormat(format);
    //找输出设备

     output = new QAudioOutput(info2,format);
     y = output->start();

}

servers::~servers()
{
    delete ui;
}
void servers::readPendingDatagrams()
{

    while (receiver->hasPendingDatagrams())
    {
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(), datagram.size());
        //读取传来的数据到datagram中

        QPixmap im ;
        im.loadFromData(datagram);
        //datagram转换成QPixmap格式
        ui->label->setPixmap(im);
        //label显示im
        ui->label->resize(ui->label->pixmap()->size());
        //设置label的大小


    }
    emit hasdata();
}

void servers::hasdata()
{
    while (receiver1->hasPendingDatagrams())
    {

        addata.resize(receiver1->pendingDatagramSize());
        receiver1->readDatagram(addata.data(), addata.size());
        if(addata.size()>2000)
        {
            y->write(addata.data(),2000);

        }else{
         y->write(addata.data());
         //写入声卡，播放
        }

    }

}
