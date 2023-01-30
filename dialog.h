#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mylogindlg.h"
#include "activity.h"
#include "quicklogging.h"

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
private:
    int recordTime;
    void saveScreenshots();
private slots:
    void on_btn_minimize_clicked();
    void on_btn_close_clicked();
    void on_btn_stop_play_clicked();
    void on_btn_collapse_below_clicked();
    void on_tab_logging_tabBarClicked(int index);

private: //
    int isDrag;
    QPoint tst, bPos;
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent*);
    void timerEvent(QTimerEvent*);
private:
    void paintEvent(QPaintEvent*);
private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
