#include "activity.h"
#include "ui_activity.h"

#include <QDate>
#include <QTime>
#include <QDebug>
#include <QCursor>
#include <QDateTime>

QPixmap smoothResize(const QPixmap &pixmap, int width, int height);

int max(int a, int b){
    return a>b?a:b;
}

int min(int a, int b){
    return a<b?a:b;
}

Activity::Activity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Activity)
{
    ui->setupUi(this);
    delta = 0;
    this->startTimer(10);
    setMouseTracking(true);

    QDir dir("logs\\screenshots\\");
    QStringList files = dir.entryList(QDir::Files);

    isShowAll = 0;
    isSll = 0;

    for(int i=max(0, files.size()-60); i<files.size(); i++){

        QString path = files[i];
        path.resize(path.size()-4);
        QStringList list = path.split("-");
        QDateTime t;
        t.setDate(QDate(list[0].toInt(), list[1].toInt(), list[2].toInt()));
        t.setTime(QTime(list[3].toInt(), list[4].toInt(), list[5].toInt()));
        addItem("logs\\screenshots\\"+files[i], t.toString());
    }

    imgDlg = new ImageDlg();

}

Activity::~Activity()
{
    delete imgDlg;
    delete ui;
}

void Activity::btnClick(){
    int index;
    QPoint mousePos = this->mapFromGlobal(QCursor::pos());
    for(int i=0; i<items.size(); i++){
        if(items[i]->isMouseOver(mousePos, delta)){
            index = i;
        }
    }
    imgDlg->path = items[index]->path;
    imgDlg->showFullScreen();
}

void Activity::trashClick(){
    int index;
    QPoint mousePos = this->mapFromGlobal(QCursor::pos());
    for(int i=0; i<items.size(); i++){
        if(items[i]->isMouseOver(mousePos, delta)){
            index = i;
        }
    }
    remove(items[index]->path.toStdString().c_str());
    PicItem *item = items[index];
    items.remove(index);
    delete item;
    refreshItems();
    update();
    int t = items.size()/2+items.size()%2;
    if(t>3){
        sll->setMaximum(t-3);
    }
}

QPixmap smoothResize(const QPixmap &pixmap, int width, int height)
{
    QImage image = pixmap.toImage();
    QImage result(width, height, image.format());
    QPainter painter(&result);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawImage(0, 0, image.scaled(width, height));

    return QPixmap::fromImage(result);
}

void Activity::paintEvent(QPaintEvent *){
    QPainter painter(this);
    for(int i=items.size()-1-delta*2; i>=0&&i>=items.size()-6-delta*2; i--){
        items[i]->drawItem(painter, delta);
    }
}

void Activity::mouseMoveEvent(QMouseEvent *e){

}

void Activity::timerEvent(QTimerEvent *){
    QPoint mousePos = this->mapFromGlobal(QCursor::pos());
    int index = -1;
    for(int i=0; i<items.size(); i++){
        if(items[i]->isMouseOver(mousePos, delta)){
            items[i]->alpha = items[i]->alpha+60<=60?items[i]->alpha+60:60;
            index = i;

            ui->btn_trash->setGeometry(items[i]->x+items[i]->w-20, items[i]->y+4-(items[i]->h+30)*delta, 16, 16);
            ui->le_time->setGeometry(items[i]->x+items[i]->w*50/425, items[i]->y+3*items[i]->h/4-(items[i]->h+30)*delta, items[i]->w*325/425, items[i]->h*2/9);
            ui->btn_viewfile->setGeometry(items[i]->x+items[i]->w*100/425, items[i]->y+items[i]->h/2-(items[i]->h+30)*delta, items[i]->w*225/425, items[i]->h*2/9);

            ui->btn_trash->show();
            ui->btn_viewfile->show();
            ui->le_time->show();
            ui->le_time->setText(items[i]->timeTxt);
        } else {
            items[i]->alpha = items[i]->alpha-60>=0?items[i]->alpha-60:0;
        }
    }
    if(index == -1){
        ui->btn_trash->hide();
        ui->btn_viewfile->hide();
        ui->le_time->hide();
    }
    update();
}

void Activity::addItem(QString path, QString time, Activity *parent){
    PicItem *item = new PicItem();

    item->path = path;

    QPixmap pix;
    pix.load(path);

    //int w = this->width()/2-15;
    //int h = pix.height()*(this->width()/2-15)/pix.width();

    int w = 370/2-15;
    int h = pix.height()*(370/2-15)/pix.width();

    normalHeight = h;

    item->pix = smoothResize(pix, w, h);

    item->timeTxt = time;

    /*if(parent == NULL){
        parent = this;
    }

    item->view = new QPushButton(parent);
    item->view->setText("View Screen");

    item->stime = new QLabel(parent);
    item->stime->setText(time);

    item->trash = new QPushButton(parent);*/

    item->w = w;
    item->h = h;

    items.push_back(item);

    refreshItems();

    //connect(item->view, SIGNAL(clicked()), parent, SLOT(btnClick()));
    //connect(item->trash, SIGNAL(clicked()), parent, SLOT(trashClick()));

    if(isShowAll){
        int t = items.size()/2+items.size()%2;
        if(t>3){
            sll->setMaximum(t-3);
        }
    }

}

void Activity::wheelEvent(QWheelEvent *event){
    if(isShowAll){
        if(event->delta() == 120){
            sll->setValue(max(sll->value()-3, 0));
        }
        if(event->delta() == -120){
            sll->setValue(min(sll->value()+3, sll->maximum()));
        }
    }
}

void Activity::refreshItems(){
    for(int i=items.size()-1; i>=0; i--){
        items[i]->x=((items.size()-1-i))%2==0?0:370/2+15;
        items[i]->y=((items.size()-1-i))/2*(normalHeight+30)+20;
    }
}

void Activity::saveScreenshots(){
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
        addItem("logs\\screenshots\\" + curTime.toString("yyyy-MM-dd-hh-mm-ss") + QString("-%1").arg(i) + ".jpg", curTime.toString());
    }
    update();
}

void Activity::viewAllActivity(){
    isShowAll = 1 - isShowAll;
    if(isShowAll && items.size() > 6){
        sll->show();
        sll->setMaximum(items.size()/2+items.size()%2-3);
        isSll = 1;
        delta = 0;
    } else {
        isSll = 0;
        sll->hide();
        delta = 0;
    }
    refreshItems();
}

void Activity::on_btn_viewfile_clicked()
{
    btnClick();
}


void Activity::on_btn_trash_clicked()
{
    trashClick();
}

