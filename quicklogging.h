#ifndef QUICKLOGGING_H
#define QUICKLOGGING_H

#include <QWidget>
#include <QScrollBar>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

#include <QVector>

namespace Ui {
class QuickLogging;
}

class TASK{
public:
    QComboBox *box1, *box2;
    QLabel *aTime;
    QPushButton *btn_play_stop;
    int isSlected;
    TASK(){
        isSlected = 0;
    }
    ~TASK(){
        delete box1;
        delete box2;
        delete aTime;
        delete btn_play_stop;
    }
};

class QuickLogging : public QWidget
{
    Q_OBJECT

public:
    explicit QuickLogging(QWidget *parent = nullptr);
    ~QuickLogging();
public:
    int delta;
    QScrollBar *sll;
    QVector<TASK*> items;
    void refreshItems();
public:
    void addProject();

private slots:
    void on_btn_addTask_clicked();

private:
    void wheelEvent(QWheelEvent*);
    bool eventFilter(QObject *obj, QEvent *ev) override;
private:
    Ui::QuickLogging *ui;
};

#endif // QUICKLOGGING_H
