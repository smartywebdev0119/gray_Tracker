#ifndef MYLOGINDLG_H
#define MYLOGINDLG_H

#include <QDialog>

namespace Ui {
class MyLoginDlg;
}

class MyLoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MyLoginDlg(QWidget *parent = nullptr);
    ~MyLoginDlg();

private slots:
    void on_btn_forgot_pass_clicked();
    void on_btn_close_clicked();

    void on_btn_minimize_clicked();

private: //
    int isDrag;
    QPoint tst, bPos;
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
private:
    Ui::MyLoginDlg *ui;
};

#endif // MYLOGINDLG_H
