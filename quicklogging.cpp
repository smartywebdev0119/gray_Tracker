#include "quicklogging.h"
#include "ui_quicklogging.h"

#include <QDebug>
#include <QMouseEvent>

int max1(int a, int b){
    return a>b?a:b;
}

int min1(int a, int b){
    return a<b?a:b;
}

QuickLogging::QuickLogging(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickLogging)
{
    ui->setupUi(this);
    delta = 0;
    installEventFilter(this);

}

QuickLogging::~QuickLogging()
{
    delete ui;
}

void QuickLogging::addProject(){
    TASK *item = new TASK;

    item->box1 = new QComboBox(this);
    item->box1->setStyleSheet(" QComboBox {\n	background-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 18px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");

    item->box1->addItem("123123");
    item->box1->addItem("123123");

    item->box2 = new QComboBox(this);
    item->box2->setStyleSheet(" QComboBox {\n	background-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 18px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");

    item->box2->addItem("123123");
    item->box2->addItem("123123");

    item->aTime = new QLabel(this);
    item->aTime->setStyleSheet("background-color: rgb(255, 255, 255);\nfont: 12pt \"Yu Gothic UI\";\npadding: 5px;\nborder-radius: 3px;");

    item->aTime->setAlignment(Qt::AlignCenter);
    item->aTime->setText("02:00");

    item->btn_play_stop = new QPushButton(this);
    item->btn_play_stop->setStyleSheet("border-radius:12px;\nbackground-color: rgb(244, 165, 48);\nbackground-image: url(:/img/play_small.png);");

    items.push_back(item);

    if(items.size()>=6){
        sll->setMaximum((items.size()-5)*5);
        sll->show();
    }

    refreshItems();

}

void QuickLogging::refreshItems(){
    /*20 60 130 30
    160 60 120 30
    290 60 47 30
    345 64 24 24*/
    for(int i=0; i<items.size(); i++){
        items[i]->box1->setGeometry(20, 65+(i)*65-delta*13, 115, 30);
        items[i]->box2->setGeometry(145, 65+(i)*65-delta*13, 115, 30);
        items[i]->aTime->setGeometry(270, 65+(i)*65-delta*13, 67, 30);
        items[i]->btn_play_stop->setGeometry(345, 69+(i)*65-delta*13, 24, 24);

        items[i]->box1->show();
        items[i]->box2->show();
        items[i]->aTime->show();
        items[i]->btn_play_stop->show();

        items[i]->box1->stackUnder(ui->fm_header);
        items[i]->box2->stackUnder(ui->fm_header);
        items[i]->aTime->stackUnder(ui->fm_header);
        items[i]->btn_play_stop->stackUnder(ui->fm_header);

        items[i]->box1->installEventFilter(this);
        items[i]->box2->installEventFilter(this);

    }
}

void QuickLogging::wheelEvent(QWheelEvent *e){
    if(e->delta() == -120){
        sll->setValue(min1(sll->maximum(), sll->value()+1));
    }
    if(e->delta() == 120){
        sll->setValue(max1(0, sll->value()-1));
    }
}

bool QuickLogging::eventFilter(QObject *o, QEvent *e){
    static int cnt=0;
    if(e->type() == QEvent::Wheel && o != this){
        return true;
    }
    return QObject::eventFilter(o, e);
}

void QuickLogging::on_btn_addTask_clicked()
{
    addProject();
}

