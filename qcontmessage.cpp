#include "qcontmessage.h"
#include "ui_qcontmessage.h"

#include <QRegion>
#include <QMouseEvent>

#define BR 7

QContMessage::QContMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QContMessage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

QContMessage::~QContMessage()
{
    delete ui;
}

void QContMessage::setRoundWid(){
    QRegion rgn1(0, BR, width(), height()-BR*2, QRegion::Rectangle);
    QRegion rgn2(BR, 0, width()-BR*2, height(), QRegion::Rectangle);
    QRegion rgn3(0, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn4(0, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn5(width()-BR*2, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn6(width()-BR*2, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    this->setMask(rgn1+rgn2+rgn3+rgn4+rgn5+rgn6);
}

int m=0;

void QContMessage::showEvent(QShowEvent *){
    m = 0;
    setRoundWid();
    timerEvent(NULL);
    this->startTimer(60000);
    isworking = 0;
}

void QContMessage::mousePressEvent(QMouseEvent *e){
    if(ui->fm_titlebar->rect().contains(e->pos())){
        tst = e->globalPos();
        bPos = this->pos();
        isDrag = 1;
    }
}

void QContMessage::mouseReleaseEvent(QMouseEvent *e){
    isDrag = 0;
}

void QContMessage::mouseMoveEvent(QMouseEvent *e){
    if(isDrag){
        this->move(bPos.x()+e->globalPos().x()-tst.x(), bPos.y()+e->globalPos().y()-tst.y());
    }
}

void QContMessage::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Escape){
        return;
    }
}

void QContMessage::on_btn_notWorking_clicked()
{
    close();
}


void QContMessage::on_btn_working_clicked()
{
    isworking = 1;
    close();
}

void QContMessage::timerEvent(QTimerEvent *){
    m ++;
    ui->le_hTime->setText(QString("%1 mins of Idle Time").arg(m));
}
