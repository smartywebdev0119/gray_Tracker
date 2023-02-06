#ifndef QUICKLOGGING_H
#define QUICKLOGGING_H

#include <QWidget>
#include <QScrollBar>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

#include <QVector>

#include <QtSql>

namespace Ui {
class QuickLogging;
}

class TASK{
public:
    QComboBox *box1, *box2;
    QLabel *aTime;
    QPushButton *btn_play_stop;
    QPushButton *btn_edit, *btn_delete;
    int isSlected, isRecord;

    int time;

    TASK(){
        isSlected = 0;
        isRecord = 0;
        time = 0;
    }
    ~TASK(){
        delete box1;
        delete box2;
        delete aTime;
        delete btn_play_stop;
        delete btn_edit;
        delete btn_delete;
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
    QPushButton *btn_tps, *btn_tps_collapse;
    QLabel *le_time, *le_time_collapse;
    void showTime();
    void refreshItems();
public:
    void addProject(int box1, int box2, int isSelected, int time);
    void saveTasks();
public slots:
    void startopRecord();
    void buttonPress(int index);
public slots:
    void on_btn_addTask_clicked();

private:
    void showEvent(QShowEvent*);
    void wheelEvent(QWheelEvent*);
    bool eventFilter(QObject *obj, QEvent *ev) override;
private:
    Ui::QuickLogging *ui;
};

#endif // QUICKLOGGING_H
