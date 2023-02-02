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
    QString path, timeTxt;
    QPixmap pix;
    PicItem(){ alpha = 0; }
    ~PicItem(){
    }
    bool isMouseOver(QPoint pt, int delta){
        return QRect(x, y-(h+30)*delta, w, h).contains(pt);
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

public:
    void saveScreenshots();
private:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
public:
    void addItem(QString path, QString time, Activity *parent=NULL);
    void refreshItems();
    void viewAllActivity();
private slots:
    void btnClick();
    void trashClick();
    void on_btn_viewfile_clicked();

    void on_btn_trash_clicked();

signals:
    void wheelEvent(int d);
private:
    Ui::Activity *ui;
};

#endif // ACTIVITY_H
