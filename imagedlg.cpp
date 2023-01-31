#include "imagedlg.h"
#include "ui_imagedlg.h"

ImageDlg::ImageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDlg)
{
    ui->setupUi(this);
}

ImageDlg::~ImageDlg()
{
    delete ui;
}

void ImageDlg::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(path);
    painter.drawPixmap(0, 0, width(), height(), pix, 0, 0, pix.width(), pix.height());
}
