#include "dialog.h"
#include "ui_dialog.h"

#include <QtGui>
#include <QFile>
#include <QRegion>
#include <QDebug>
#include <QDateTime>
#include <QThread>

#define BR 7

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    dlg = new MyLoginDlg();
    dlg->exec();

    if(dlg->isLogin == 0) exit(0);

    actWid = new Activity;
    ui->tab_logging->addTab(actWid, "Activity");

    actWid->sll = ui->scroll_activity;

    quickLog = new QuickLogging;
    ui->tab_logging->addTab(quickLog, "Quick Logging");

    quickLog->sll = ui->scroll_log;

    ui->scroll_log->hide();

    /*for(int i=0; i<10; i++){
        quickLog->addProject();
    }*/

    setRoundWid();

    isRecord = 0, iscollapse = 0;
    isDrag = false;    

    recordTime = 1;

    ui->tab_logging->hide();
    ui->scroll_log->hide();

    on_tab_logging_tabBarClicked(0);

    setMouseTracking(true);
    this->startTimer(1000);

    curTime = 0;

}

void Dialog::setRoundWid(){
    QRegion rgn1(0, BR, width(), height()-BR*2, QRegion::Rectangle);
    QRegion rgn2(BR, 0, width()-BR*2, height(), QRegion::Rectangle);
    QRegion rgn3(0, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn4(0, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn5(width()-BR*2, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn6(width()-BR*2, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    this->setMask(rgn1+rgn2+rgn3+rgn4+rgn5+rgn6);
}

Dialog::~Dialog()
{
    delete quickLog;
    delete actWid;
    delete dlg;
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *){
    QPainter painter(this);
}

void Dialog::on_btn_minimize_clicked()
{
    this->showMinimized();
}


void Dialog::on_btn_close_clicked()
{
    exit(0);
}

int isBegin = 0;

void Dialog::showEvent(QShowEvent *){
    if(!isBegin){
        ui->scroll_log->hide();
        ui->scroll_activity->hide();
        ui->btn_collapse_below->setStyleSheet("QPushButton {\n	background-image: url(:/img/collapse_top.png);\nborder: 0px solid;\nborder-radius: 5px;\n}\nQPushButton:hover{\n	background-color: rgb(200, 200, 200, 100);\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\nborder-radius: 5px;\n}\nQPushButton:pressed{\n	background-color: rgb(100, 100, 100, 100);\nborder-radius: 5px;\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\n}");
        this->setGeometry(this->x(), this->y(), this->width(), 250);
        ui->fm_statusbar->setGeometry(ui->fm_titlebar->x(), this->height()-ui->fm_statusbar->height()-2, ui->fm_statusbar->width(), ui->fm_statusbar->height());
        isBegin = 1;
        setRoundWid();
    }
}

void Dialog::mousePressEvent(QMouseEvent *e){
    if(ui->fm_titlebar->rect().contains(e->pos())){
        tst = e->globalPos();
        bPos = this->pos();
        isDrag = 1;
    }
}

void Dialog::saveScreenshots(){

    QDateTime curTime = QDateTime::currentDateTime();
    QString dirPath = "logs\\screenshots\\";
    QDir dir;
    if(!dir.exists(dirPath)){
        dir.mkpath(dirPath);
    }

    QList<QScreen *> screens = QGuiApplication::screens();
    for(int i=0; i<screens.size(); i++){
        QPixmap pix;
        pix = screens[i]->grabWindow(0);

        QFile file;
        file.setFileName("logs\\screenshots\\" + curTime.toString("yyyy-MM-dd-hh-mm-ss") + QString("-%1").arg(i) + ".jpg");
        file.open(QIODevice::WriteOnly);
        pix.save(&file, "JPG");
        actWid->addItem("logs\\screenshots\\" + curTime.toString("yyyy-MM-dd-hh-mm-ss") + QString("-%1").arg(i) + ".jpg", curTime.toString());
    }
    actWid->update();
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
        if(actWid->isSll == 1 && ui->tab_logging->currentIndex() == 0){
            ui->scroll_activity->show();
        }
        if(quickLog->items.size()>6 && ui->tab_logging->currentIndex() == 1){
            ui->scroll_log->show();
        }
    } else {
        ui->btn_collapse_below->setStyleSheet("QPushButton {\n	background-image: url(:/img/collapse_top.png);\nborder: 0px solid;\nborder-radius: 5px;\n}\nQPushButton:hover{\n	background-color: rgb(200, 200, 200, 100);\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\nborder-radius: 5px;\n}\nQPushButton:pressed{\n	background-color: rgb(100, 100, 100, 100);\nborder-radius: 5px;\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\n}");
        this->setGeometry(this->x(), this->y(), this->width(), 250);
        ui->fm_statusbar->setGeometry(ui->fm_titlebar->x(), this->height()-ui->fm_statusbar->height()-2, ui->fm_statusbar->width(), ui->fm_statusbar->height());
        ui->tab_logging->hide();
        ui->scroll_log->hide();
        ui->scroll_activity->hide();
    }
    setRoundWid();
}


void Dialog::on_tab_logging_tabBarClicked(int index)
{

}

void Dialog::timerEvent(QTimerEvent *){
    curTime += isRecord;
    if(isRecord){
        ui->le_curTime->setText(QString("%1%2: %3%4: %5%6").arg(curTime/36000).arg(curTime%36000/3600).arg(curTime%3600/600).arg(curTime%600/60).arg(curTime%60/10).arg(curTime%10));
        if(curTime % recordTime == 0){
            saveScreenshots();
        }
    }
}

void Dialog::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Escape){
        return;
    }
}


void Dialog::on_btn_viewAllAct_clicked()
{
    if(ui->btn_viewAllAct->text()=="View All Activity"){
        ui->btn_viewAllAct->setText("Hide Acivity");
    } else {
        ui->btn_viewAllAct->setText("View All Activity");
        ui->scroll_activity->setValue(0);
    }
    actWid->viewAllActivity();
}


void Dialog::on_scroll_log_valueChanged(int value)
{
    quickLog->delta = value;
    quickLog->refreshItems();
}


void Dialog::on_scroll_activity_valueChanged(int value)
{
    actWid->delta=value;
    actWid->refreshItems();
    actWid->update();
}


void Dialog::on_tab_logging_currentChanged(int index)
{
    if(index == 0){
        ui->btn_viewAllAct->show();
        ui->btn_submit->hide();
        ui->fm_totalTime->hide();
        if(actWid->isSll){
            ui->scroll_activity->show();
        }
        ui->scroll_log->hide();

    } else {
        ui->btn_viewAllAct->hide();
        ui->btn_submit->show();
        ui->fm_totalTime->show();
        ui->scroll_activity->hide();
        if(quickLog->items.size()>=6){
            ui->scroll_log->show();
        }
    }
}

