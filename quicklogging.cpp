#include "quicklogging.h"
#include "ui_quicklogging.h"

QuickLogging::QuickLogging(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickLogging)
{
    ui->setupUi(this);
}

QuickLogging::~QuickLogging()
{
    delete ui;
}
