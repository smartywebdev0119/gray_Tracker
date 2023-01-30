#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QWidget>
#include <QtGui>

#include <QDebug>
#include <QPushButton>
#include <QGraphicsOpacityEffect>

#include <QVector>

namespace Ui {
class Activity;
}

class PicItem{
public:
    int x, y, w, h, alpha;
    QPixmap pix;
    QPushButton *view, *trash;
    PicItem(){ alpha = 0; }
    ~PicItem(){
        delete trash;
        delete view;
    }
    bool isMouseOver(QPoint pt){
        return QRect(x, y, w, h).contains(pt);
    }
    void refresh(){

        //trash set;
        trash->setGeometry(x+w-20, y+4, 16, 16);
        trash->setStyleSheet("QPushButton{\n	background-color:rgba(0, 0, 0, 0);\nborder: none;\nbackground-image: url(:/img/waste_hover.png);\n}\nQPushButton:hover{\n	background-color:rgba(255, 255, 255, 200);\nborder: none;\n	background-image: url(:/img/waste_normal.png);\n}");

        view->setGeometry(x+w*100/425, y+h/2, w*225/425, h*2/9);
        view->setStyleSheet("QPushButton{\nbackground-color:rgb(255, 255, 255);\ncolor:rgb(29,29,29);border-radius:3px;\n}\nQPushButton:hover{\nbackground-color:rgba(255, 255, 255, 200);\ncolor:rgb(29,29,29);border-radius:3px;\n}\n");
    }
    void drawItem(QPainter& painter){
        painter.drawPixmap(x, y, w, h, pix);
        QBrush br;
        br.setColor(QColor(0, 0, 0, alpha*255/100));
        br.setStyle(Qt::SolidPattern);
        painter.setBrush(br);
        QPen pen;
        pen.setColor(QColor(0, 0, 0, 0));
        pen.setWidth(0);
        painter.setPen(pen);
        painter.drawRect(x, y, w, h);
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
    int maxSize;
private:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
public:
    void addItem(QString path, QString time);
private slots:
    void btnClick();
    void trashClick();
private:
    Ui::Activity *ui;
};

#endif // ACTIVITY_H
