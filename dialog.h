#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mylogindlg.h"
#include "activity.h"
#include "quicklogging.h"

#include "mysavethread.h"

#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    MyLoginDlg *dlg;
    Activity *actWid;
    QuickLogging *quickLog;
private:
    int isRecord, iscollapse;
    int curTime;

public:
    MySaveThread *saveTread;

    int prevHeight;
    void collapseMode();
    void showMode();
private:
    int recordTime;
public:
    void saveScreenshots();
    void setRoundWid();
private slots:
    void on_btn_minimize_clicked();
    void on_btn_close_clicked();
    void on_btn_stop_play_clicked();
    void on_btn_collapse_below_clicked();
    void on_tab_logging_tabBarClicked(int index);

    void on_btn_viewAllAct_clicked();

    void on_scroll_log_valueChanged(int value);

    void on_scroll_activity_valueChanged(int value);

    void on_tab_logging_currentChanged(int index);

    void on_btn_collapse_clicked();

    void on_btn_collapse_a_clicked();

    void on_btn_stop_play_collapse_clicked();

private: //
    int isDrag;
    QPoint tst, bPos;
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent*);
    void timerEvent(QTimerEvent*);
    void closeEvent(QCloseEvent*);
private:
    void paintEvent(QPaintEvent*);
private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
