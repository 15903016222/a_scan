#include "mythread.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <QDebug>
#include <QTime>

MyThread::MyThread() :
    QThread()
{
    m_dma = Dma::instance();
    m_flag = true;
    srand((unsigned)time(NULL));
}

void MyThread::draw_a_scan()
{
    QByteArray data;
    static int index = 0;
    const int pointQty = 512;
    char temp[512] = {0};

    for (index = 0; index < 512; ++index) {
        temp[index] = rand() % 600;
    }


    data = QByteArray(temp/* + index*/, pointQty);
    emit draw_data(data);
}

void MyThread::run()
{
    m_dma->set_frame_count (128);
    while (m_flag) {
        draw_a_scan();
        usleep(5000);
    }
}

MyThread::~MyThread()
{
}
