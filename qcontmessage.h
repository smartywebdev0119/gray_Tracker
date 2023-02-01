#ifndef QCONTMESSAGE_H
#define QCONTMESSAGE_H

#include <QDialog>

namespace Ui {
class QContMessage;
}

class QContMessage : public QDialog
{
    Q_OBJECT
public:
    void setRoundWid();
public:
    explicit QContMessage(QWidget *parent = nullptr);
    ~QContMessage();
public:
    void showEvent(QShowEvent*);
    void timerEvent(QTimerEvent*);
private slots:
    void on_btn_notWorking_clicked();

    void on_btn_working_clicked();
private:
    int isDrag;
    QPoint tst, bPos;
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
private:
    Ui::QContMessage *ui;
};

#endif // QCONTMESSAGE_H
