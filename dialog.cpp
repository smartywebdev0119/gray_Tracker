#include "dialog.h"
#include "ui_dialog.h"

#include <QtGui>
#include <QRegion>
#include <QDebug>

#define BR 7

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    dlg = new MyLoginDlg();
    dlg->exec();

    QRegion rgn1(0, BR, width(), height()-BR*2, QRegion::Rectangle);
    QRegion rgn2(BR, 0, width()-BR*2, height(), QRegion::Rectangle);
    QRegion rgn3(0, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn4(0, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn5(width()-BR*2, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn6(width()-BR*2, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    this->setMask(rgn1+rgn2+rgn3+rgn4+rgn5+rgn6);

    isRecord = 0, iscollapse = 0;
    isDrag = false;    

    ui->tab_logging->hide();

    setMouseTracking(true);
}

Dialog::~Dialog()
{
    delete dlg;
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *){
    QPainter painter(this);
}

void Dialog::drawTitleBar(QPainter &painter){
}



void Dialog::on_btn_minimize_clicked()
{
    this->showMinimized();
}


void Dialog::on_btn_close_clicked()
{
    exit(0);
}

void Dialog::showEvent(QShowEvent *){
    ui->btn_collapse_below->setStyleSheet("QPushButton {\n	background-image: url(:/img/collapse_top.png);\nborder: 0px solid;\nborder-radius: 5px;\n}\nQPushButton:hover{\n	background-color: rgb(200, 200, 200, 100);\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\nborder-radius: 5px;\n}\nQPushButton:pressed{\n	background-color: rgb(100, 100, 100, 100);\nborder-radius: 5px;\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\n}");
    this->setGeometry(this->x(), this->y(), this->width(), 250);
    ui->fm_statusbar->setGeometry(ui->fm_titlebar->x(), this->height()-ui->fm_statusbar->height()-2, ui->fm_statusbar->width(), ui->fm_statusbar->height());
}


void Dialog::mousePressEvent(QMouseEvent *e){
    if(ui->fm_titlebar->rect().contains(e->pos())){
        tst = e->globalPos();
        bPos = this->pos();
        isDrag = 1;
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *e){
    isDrag = 0;
}

void Dialog::mouseMoveEvent(QMouseEvent *e){
    if(isDrag){
        this->move(bPos.x()+e->globalPos().x()-tst.x(), bPos.y()+e->globalPos().y()-tst.y());
    }
}

void Dialog::on_btn_stop_play_clicked()
{
    isRecord = 1 - isRecord;
    if(isRecord){
        ui->btn_stop_play->setStyleSheet("QPushButton {\n	background-image: url(:/img/stop_64px.png);\n	background-color: rgb(190, 95, 29);\nbackground-image: url(:/img/stop_64px.png);\nborder-radius: 32px;\nborder: 0px solid;\n}");
    } else {
        ui->btn_stop_play->setStyleSheet("QPushButton {\n	background-image: url(:/img/play_64x.png);\n	background-color: rgb(29, 95, 190);\nbackground-image: url(:/img/play_64px.png);\nborder-radius: 32px;\nborder: 0px solid;\n}");
    }
}

void Dialog::on_btn_collapse_below_clicked()
{
    iscollapse = 1 - iscollapse;
    if(iscollapse){
        ui->btn_collapse_below->setStyleSheet("QPushButton {\n	background-image: url(:/img/collapse_bottom.png);\nborder: 0px solid;\nborder-radius: 5px;\n}\nQPushButton:hover{\n	background-color: rgb(200, 200, 200, 100);\nborder: 0px solid;\n	background-image: url(:/img/collapse_bottom_hover.png);\nborder-radius: 5px;\n}\nQPushButton:pressed{\n	background-color: rgb(100, 100, 100, 100);\nborder-radius: 5px;\nborder: 0px solid;\n	background-image: url(:/img/collapse_bottom_hover.png);\n}");
        this->setGeometry(this->x(), this->y(), this->width(), 700);
        ui->fm_statusbar->setGeometry(ui->fm_titlebar->x(), this->height()-ui->fm_statusbar->height()-2, ui->fm_statusbar->width(), ui->fm_statusbar->height());
        ui->tab_logging->show();
    } else {
        ui->btn_collapse_below->setStyleSheet("QPushButton {\n	background-image: url(:/img/collapse_top.png);\nborder: 0px solid;\nborder-radius: 5px;\n}\nQPushButton:hover{\n	background-color: rgb(200, 200, 200, 100);\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\nborder-radius: 5px;\n}\nQPushButton:pressed{\n	background-color: rgb(100, 100, 100, 100);\nborder-radius: 5px;\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\n}");
        this->setGeometry(this->x(), this->y(), this->width(), 250);
        ui->fm_statusbar->setGeometry(ui->fm_titlebar->x(), this->height()-ui->fm_statusbar->height()-2, ui->fm_statusbar->width(), ui->fm_statusbar->height());
        ui->tab_logging->hide();
    }
}

