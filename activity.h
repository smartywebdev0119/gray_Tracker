#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QWidget>
#include <QtGui>

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsOpacityEffect>

#include <QScrollBar>

#include <QVector>

#include "imagedlg.h"

namespace Ui {
class Activity;
}

class PicItem{
public:
    int x, y, w, h, alpha;
    QString path;
    QPixmap pix;
    QPushButton *view, *trash;
    QLabel *stime;
    PicItem(){ alpha = 0; }
    ~PicItem(){
        delete stime;
        delete trash;
        delete view;
    }
    bool isMouseOver(QPoint pt, int delta){
        return QRect(x, y-(h+30)*delta, w, h).contains(pt);
    }
    void refresh(int delta){

        //trash set;
        trash->setGeometry(x+w-20, y+4-(h+30)*delta, 16, 16);
        trash->setStyleSheet("QPushButton{\n	background-color:rgba(0, 0, 0, 0);\nborder: none;\nbackground-image: url(:/img/waste_hover.png);\n}\nQPushButton:hover{\n	background-color:rgba(255, 255, 255, 200);\nborder: none;\n	background-image: url(:/img/waste_normal.png);\n}");

        stime->setGeometry(x+w*50/425, y+3*h/4-(h+30)*delta, w*325/425, h*2/9);
        stime->setStyleSheet("QLabel{\ncolor: rgb(250, 250, 250);background-color: rgba(0, 0, 0, 0);\n}");

        view->setGeometry(x+w*100/425, y+h/2-(h+30)*delta, w*225/425, h*2/9);
        view->setStyleSheet("QPushButton{\nbackground-color:rgb(255, 255, 255);\ncolor:rgb(29,29,29);border-radius:3px;\n}\nQPushButton:hover{\nbackground-color:rgba(255, 255, 255, 200);\ncolor:rgb(29,29,29);border-radius:3px;\n}\n");
    }
    void drawItem(QPainter& painter, int delta){
        painter.drawPixmap(x, y-(h+30)*delta, w, h, pix);
        QBrush br;
        br.setColor(QColor(0, 0, 0, alpha*255/100));
        br.setStyle(Qt::SolidPattern);
        painter.setBrush(br);
        QPen pen;
        pen.setColor(QColor(0, 0, 0, 0));
        pen.setWidth(0);
        painter.setPen(pen);
        painter.drawRect(x, y-(h+30)*delta, w, h);
    }
};

class Activity : public QWidget
{
    Q_OBJECT

public:
    explicit Activity(QWidget *parent = nullptr);
    ~Activity();
public:
    QVector<PicItem*> items;
    int normalHeight;
    int delta, isSll;
    QScrollBar *sll;
    int isShowAll;
    ImageDlg *imgDlg;
private:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
public:
    void addItem(QString path, QString time);
    void refreshItems();
    void viewAllActivity();
private slots:
    void btnClick();
    void trashClick();
signals:
    void wheelEvent(int d);
private:
    Ui::Activity *ui;
};

#endif // ACTIVITY_H
