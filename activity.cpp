#include "activity.h"
#include "ui_activity.h"

#include <QDebug>

QPixmap smoothResize(const QPixmap &pixmap, int width, int height);

Activity::Activity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Activity)
{
    ui->setupUi(this);
    maxSize = 6;
    this->startTimer(10);

}

Activity::~Activity()
{
    delete ui;
}

void Activity::btnClick(){
    qDebug() << "clicked";
}

void Activity::trashClick(){
    qDebug() << "deleted";
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
    for(int i=items.size()-1; i>=0&&items.size()-maxSize; i--){
        items[i]->drawItem(painter);
    }
}

void Activity::timerEvent(QTimerEvent *){
    QPoint mousePos = this->mapFromGlobal(QCursor::pos());
    for(int i=0; i<items.size(); i++){
        if(items[i]->isMouseOver(mousePos)){
            items[i]->alpha = items[i]->alpha+2<=60?items[i]->alpha+2:60;
            items[i]->view->show();
            items[i]->trash->show();
        } else {
            items[i]->alpha = items[i]->alpha-2>=0?items[i]->alpha-2:0;
            if(items[i]->alpha == 0){
                items[i]->view->hide();
                items[i]->trash->hide();
            }
        }
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
        effect->setOpacity(((double)items[i]->alpha/60)); // Set opacity to 50%
        items[i]->view->setGraphicsEffect(effect);
        items[i]->trash->setGraphicsEffect(effect);
    }


    update();
}

void Activity::addItem(QString path, QString time){
    PicItem *item = new PicItem();

    QPixmap pix;
    pix.load(path);

    int w = this->width()/2-15;
    int h = pix.height()*(this->width()/2-15)/pix.width();

    item->pix = smoothResize(pix, w, h);

    item->view = new QPushButton(this);
    item->view->setText("View Screen");

    item->trash = new QPushButton(this);

    for(int i=items.size()-1; i>=1; i--){
        items[i]->x = items[i-1]->x;
        items[i]->y = items[i-1]->y;
        items[i]->w = items[i-1]->w;
        items[i]->h = items[i-1]->h;
        items[i]->refresh();
    }

    if(items.size()){
        items[0]->x=(items.size()+1)%2==0?this->width()/2+15:0;
        items[0]->y=(items.size())/2*(h+30)+20;
        items[0]->refresh();
    }

    item->x = 0;
    item->y = 20;
    item->w = w;
    item->h = h;

    item->refresh();

    connect(item->view, SIGNAL(clicked()), this, SLOT(btnClick()));
    connect(item->trash, SIGNAL(clicked()), this, SLOT(trashClick()));

    items.push_back(item);

}
