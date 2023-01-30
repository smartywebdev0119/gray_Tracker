#include "dialog.h"
#include "ui_dialog.h"

#include <QtGui>
#include <QFile>
#include <QRegion>
#include <QDebug>
#include <QDateTime>

#define BR 7

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    dlg = new MyLoginDlg();
    dlg->exec();

    actWid = new Activity;
    ui->tab_logging->addTab(actWid, "Activity");

    quickLog = new QuickLogging;
    ui->tab_logging->addTab(quickLog, "Quick Logging");

    QRegion rgn1(0, BR, width(), height()-BR*2, QRegion::Rectangle);
    QRegion rgn2(BR, 0, width()-BR*2, height(), QRegion::Rectangle);
    QRegion rgn3(0, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn4(0, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn5(width()-BR*2, 0, BR*2, BR*2, QRegion::Ellipse);
    QRegion rgn6(width()-BR*2, height()-BR*2, BR*2, BR*2, QRegion::Ellipse);
    this->setMask(rgn1+rgn2+rgn3+rgn4+rgn5+rgn6);

    isRecord = 0, iscollapse = 0;
    isDrag = false;    

    recordTime = 5;

    ui->tab_logging->hide();

    on_tab_logging_tabBarClicked(0);

    setMouseTracking(true);
    this->startTimer(1000);

    curTime = 0;

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
        ui->btn_collapse_below->setStyleSheet("QPushButton {\n	background-image: url(:/img/collapse_top.png);\nborder: 0px solid;\nborder-radius: 5px;\n}\nQPushButton:hover{\n	background-color: rgb(200, 200, 200, 100);\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\nborder-radius: 5px;\n}\nQPushButton:pressed{\n	background-color: rgb(100, 100, 100, 100);\nborder-radius: 5px;\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\n}");
        this->setGeometry(this->x(), this->y(), this->width(), 250);
        ui->fm_statusbar->setGeometry(ui->fm_titlebar->x(), this->height()-ui->fm_statusbar->height()-2, ui->fm_statusbar->width(), ui->fm_statusbar->height());
        isBegin = 1;
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
        file.setFileName("logs\\screenshots\\" + curTime.date().toString("yyyy-MM-dd") + "-"
                         + curTime.time().toString("hhmmss") + QString("-%1").arg(i) + ".jpg");
        file.open(QIODevice::WriteOnly);
        pix.save(&file, "JPG");
        actWid->addItem("logs\\screenshots\\" + curTime.date().toString("yyyy-MM-dd") + "-"
                        + curTime.time().toString("hhmmss") + QString("-%1").arg(i) + ".jpg", "");
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
    } else {
        ui->btn_collapse_below->setStyleSheet("QPushButton {\n	background-image: url(:/img/collapse_top.png);\nborder: 0px solid;\nborder-radius: 5px;\n}\nQPushButton:hover{\n	background-color: rgb(200, 200, 200, 100);\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\nborder-radius: 5px;\n}\nQPushButton:pressed{\n	background-color: rgb(100, 100, 100, 100);\nborder-radius: 5px;\nborder: 0px solid;\n	background-image: url(:/img/collapse_top_hover.png);\n}");
        this->setGeometry(this->x(), this->y(), this->width(), 250);
        ui->fm_statusbar->setGeometry(ui->fm_titlebar->x(), this->height()-ui->fm_statusbar->height()-2, ui->fm_statusbar->width(), ui->fm_statusbar->height());
        ui->tab_logging->hide();
    }
}


void Dialog::on_tab_logging_tabBarClicked(int index)
{
    if(index == 0){
        ui->btn_viewAllAct->show();
        ui->btn_submit->hide();
        ui->fm_totalTime->hide();
        ui->scroll_log->hide();

    } else {
        ui->btn_viewAllAct->hide();
        ui->btn_submit->show();
        ui->fm_totalTime->show();
        ui->scroll_log->show();
    }
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

