#ifndef IMAGEDLG_H
#define IMAGEDLG_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class ImageDlg;
}

class ImageDlg : public QDialog
{
    Q_OBJECT
public:
    QString path;
public:
    explicit ImageDlg(QWidget *parent = nullptr);
    ~ImageDlg();
public:
    void paintEvent(QPaintEvent*);
private:
    Ui::ImageDlg *ui;
};

#endif // IMAGEDLG_H
