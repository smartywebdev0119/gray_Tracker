#include "mylogindlg.h"
#include "ui_mylogindlg.h"

#include <QUrl>
#include <QRegion>
#include <QDebug>
#include <QDesktopServices>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

#define BR 6

MyLoginDlg::MyLoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyLoginDlg)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    QRegion rgn1(0, BR, width(), height()-BR*2, QRegion::Rectangle);
    QRegion rgn2(BR, 0, width()-BR*2, height(), QRegion::Rectangle);
    QRegion rgn3(0, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn4(0, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn5(width()-BR*2, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn6(width()-BR*2, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    this->setMask(rgn1+rgn2+rgn3+rgn4+rgn5+rgn6);

    isDrag = false;

    setMouseTracking(true);

}

MyLoginDlg::~MyLoginDlg()
{
    delete ui;
}

void MyLoginDlg::on_btn_forgot_pass_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/WebTop"));
}


void MyLoginDlg::mousePressEvent(QMouseEvent *e){
    if(ui->fm_titlebar->rect().contains(e->pos())){
        tst = e->globalPos();
        bPos = this->pos();
        isDrag = 1;
    }
}

void MyLoginDlg::mouseReleaseEvent(QMouseEvent *e){
    isDrag = 0;
}

void MyLoginDlg::mouseMoveEvent(QMouseEvent *e){
    if(isDrag){
        this->move(bPos.x()+e->globalPos().x()-tst.x(), bPos.y()+e->globalPos().y()-tst.y());
    }
}


void MyLoginDlg::on_btn_close_clicked()
{
    exit(0);
}


void MyLoginDlg::on_btn_minimize_clicked()
{
    this->showMinimized();
}

