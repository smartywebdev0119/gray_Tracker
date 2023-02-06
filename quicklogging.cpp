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

int isBeginShow = 0;

void QuickLogging::showEvent(QShowEvent *){
}

void QuickLogging::addProject(int box1=-1, int box2=-1, int isSelected=-1, int time=-1){
    TASK *item = new TASK;

    item->box1 = new QComboBox(this);
    item->box1->setStyleSheet(" QComboBox {\n	background-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");

    item->box1->addItem("Project 1");
    item->box1->addItem("Project 2");
    item->box1->addItem("Project 3");
    item->box1->addItem("Project 4");
    item->box1->setEditText("");
    if(box1!=-1){
        item->box1->setCurrentIndex(box1);
    }

    item->box2 = new QComboBox(this);
    item->box2->setStyleSheet(" QComboBox {\n	background-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");

    item->box2->addItem("GM Insights");
    item->box2->addItem("GM Insights App");
    item->box2->setEditText("");

    item->btn_edit = new QPushButton(this);
    item->btn_edit->setText("Edit");
    item->btn_edit->setIcon(QIcon(":/edit"));
    item->btn_edit->setStyleSheet("QPushButton{\nborder: none;\nbackground-color: rgba(0, 0, 0, 0);\ncolor: rgb(200, 56, 56);\npadding: 2px;\n}\n\nQPushButton:hover{\nbackground-color: rgba(0, 0, 0, 10);\nborder-radius: 5px;\n}");

    item->btn_delete = new QPushButton(this);
    item->btn_delete->setText("Delete");
    item->btn_delete->setStyleSheet("QPushButton{\nborder: none;\nbackground-color: rgba(0, 0, 0, 0);\npadding: 2px;\n}\n\nQPushButton:hover{\nbackground-color: rgba(0, 0, 0, 10);\nborder-radius: 5px;\n}");
    item->btn_delete->setIcon(QIcon(":/trash"));

    if(box2!=-1){
        item->box2->setCurrentIndex(box2);
    }

    if(isSelected!=-1){
        item->isSlected = isSelected;
    }

    item->aTime = new QLabel(this);
    item->aTime->setStyleSheet("background-color: rgb(255, 255, 255);\nfont: 12pt \"Yu Gothic UI\";\npadding: 5px;\nborder-radius: 3px;");

    item->aTime->setAlignment(Qt::AlignCenter);
    item->aTime->setText("00:00");
    if(time != -1){
        item->aTime->setText(QString("%1%2:%3%4").arg(time/36000).arg(time%36000/3600).arg(time%3600/600).arg(time%600/60));
        item->time = time;
    }

    item->btn_play_stop = new QPushButton(this);
    item->btn_play_stop->setStyleSheet("border-radius:12px;\nbackground-color: rgb(244, 165, 48);\nbackground-image: url(:/img/play_small.png);");

    connect(item->btn_play_stop, SIGNAL(clicked()), this, SLOT(startopRecord()));

    items.push_back(item);

    if(items.size()>=6){
        sll->setMaximum((items.size()-5)*5);
        sll->show();
    }

    refreshItems();

    if(isSelected == 1){
        item->box1->setStyleSheet(" QComboBox {\n	border: 1px solid rgb(60,173,33);\nbackground-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");
        item->box2->setStyleSheet(" QComboBox {\n	border: 1px solid rgb(60,173,33);\nbackground-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");
        item->aTime->setStyleSheet("border: 1px solid rgb(60,173,33);\nbackground-color: rgb(255, 255, 255);\nfont: 12pt \"Yu Gothic UI\";\npadding: 5px;\nborder-radius: 3px;");
    }

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

        items[i]->btn_edit->setGeometry(210, 65+(i)*65-delta*13+35, 57, 20);
        items[i]->btn_delete->setGeometry(270, 65+(i)*65-delta*13+35, 57, 20);

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
    if(items.size() >= 20) return;
    addProject();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("logs\\gray.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
    }

    QSqlQuery query;
    qDebug() << query.exec("INSERT INTO history (box1, box2, isSelected, time) VALUES ("+QString("%1,%2,%3,%4").arg(items[items.size()-1]->box1->currentIndex())
            .arg(items[items.size()-1]->box2->currentIndex())
            .arg(items[items.size()-1]->isSlected)
            .arg(items[items.size()-1]->time) + ")");

    db.close();

    if(items.size()>5){
        sll->setValue(sll->maximum());
    }
}

void QuickLogging::saveTasks(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("logs\\gray.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
    }

    // Create table if not exists
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS history (id INTEGER PRIMARY KEY AUTOINCREMENT, box1 INTEGER, box2 INTEGER, isSelected INTEGER, time INTEGER)");

    for(int i=0; i<items.size(); i++){
        QSqlQuery query;
        query.prepare("UPDATE history SET box1=?, box2=?, isSelected=?, time=? WHERE id=?");
        query.addBindValue(items[i]->box1->currentIndex());
        query.addBindValue(items[i]->box2->currentIndex());
        query.addBindValue(items[i]->isSlected);
        query.addBindValue(items[i]->time);
        query.addBindValue(i+1);
        if (!query.exec()) {
            qDebug() << "Error updating entry";
        } else {
            qDebug() << "Entry updated!";
        }
    }
    db.close();
}

void QuickLogging::startopRecord(){
    QObject *sender = QObject::sender();
    int index;
    for(int i=0; i<items.size(); i++){
        if(sender == items[i]->btn_play_stop){
            index = i;
        }
    }
    buttonPress(index);
}

void QuickLogging::buttonPress(int index){
    if(items[index]->isSlected){
        items[index]->isSlected = 1;
        items[index]->isRecord = 1 - items[index]->isRecord;
        if(items[index]->isRecord){
            items[index]->btn_play_stop->setStyleSheet("border-radius:12px;\nbackground-color: rgb(244, 165, 48);\nbackground-image: url(:/img/pause_small.png);");
            btn_tps->setStyleSheet("QPushButton {\n	background-image: url(:/img/stop_64px.png);\n	background-color: rgb(190, 95, 29);\nbackground-image: url(:/img/stop_64px.png);\nborder-radius: 32px;\nborder: 0px solid;\n}");
            btn_tps_collapse->setStyleSheet("QPushButton {\n	background-image: url(:/img/stop_64px.png);background-position:center;\n	background-color: rgb(190, 95, 29);\nbackground-image: url(:/img/stop_64px.png);\nborder-radius: 24px;\nborder: 0px solid;\n}");
        } else {
            items[index]->btn_play_stop->setStyleSheet("border-radius:12px;\nbackground-color: rgb(244, 165, 48);\nbackground-image: url(:/img/play_small.png);");
            btn_tps->setStyleSheet("QPushButton {\n	background-image: url(:/img/play_64x.png);\n	background-color: rgb(29, 95, 190);\nbackground-image: url(:/img/play_64px.png);\nborder-radius: 32px;\nborder: 0px solid;\n}");
            btn_tps_collapse->setStyleSheet("QPushButton {\n	background-image: url(:/img/play_64x.png);\nbackground-position:center;\n	background-color: rgb(29, 95, 190);\nbackground-image: url(:/img/play_64px.png);\nborder-radius: 24px;\nborder: 0px solid;\n}");
        }

        //items[index]->box1->setStyleSheet(" QComboBox {\nbackground-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");
        //items[index]->box2->setStyleSheet(" QComboBox {\nbackground-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");
        //items[index]->aTime->setStyleSheet("background-color: rgb(255, 255, 255);\nfont: 12pt \"Yu Gothic UI\";\npadding: 5px;\nborder-radius: 3px;");
    } else {
        for(int i=0; i<items.size(); i++){
            items[i]->isSlected = 0;
            items[i]->btn_play_stop->setStyleSheet("border-radius:12px;\nbackground-color: rgb(244, 165, 48);\nbackground-image: url(:/img/play_small.png);");
            items[i]->box1->setStyleSheet(" QComboBox {\nbackground-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");
            items[i]->box2->setStyleSheet(" QComboBox {\nbackground-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");
            items[i]->aTime->setStyleSheet("background-color: rgb(255, 255, 255);\nfont: 12pt \"Yu Gothic UI\";\npadding: 5px;\nborder-radius: 3px;");
            items[i]->isRecord = false;
        }
        items[index]->isSlected = 1;
        items[index]->isRecord = true;
        btn_tps->setStyleSheet("QPushButton {\n	background-image: url(:/img/stop_64px.png);\n	background-color: rgb(190, 95, 29);\nbackground-image: url(:/img/stop_64px.png);\nborder-radius: 32px;\nborder: 0px solid;\n}");
        btn_tps_collapse->setStyleSheet("QPushButton {\n	background-position:center;\nbackground-image: url(:/img/stop_64px.png);\n	background-color: rgb(190, 95, 29);\nbackground-image: url(:/img/stop_64px.png);\nborder-radius: 24px;\nborder: 0px solid;\n}");
        items[index]->btn_play_stop->setStyleSheet("border-radius:12px;\nbackground-color: rgb(244, 165, 48);\nbackground-image: url(:/img/pause_small.png);");
        items[index]->box1->setStyleSheet(" QComboBox {\n	border: 1px solid rgb(60,173,33);\nbackground-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");
        items[index]->box2->setStyleSheet(" QComboBox {\n	border: 1px solid rgb(60,173,33);\nbackground-color: rgb(255,255,255);\nfont: 12px;\n     border-radius: 3px;\n     padding: 1px 10px 1px 3px;\n     min-width: 6em;\n }\n\n QComboBox:editable {\n     background: white;\n }\n\n QComboBox:!editable, QComboBox::drop-down:editable {\n }\n\n QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n }\n\n QComboBox:on {\n     padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     subcontrol-origin: padding;\n     subcontrol-position: top right;\n     width: 15px;\n     border-left-color: darkgray;\n     border-left-style: solid;\n     border-top-right-radius: 3px;\n     border-bottom-right-radius: 3px;\n }\n\n QComboBox::down-arrow {\n	image: url(:/img/combo_arrow.png);\n }\n\n QComboBox::down-arrow:on {\n     image: url(:/img/combo_up_arrow.png);\n }");
        items[index]->aTime->setStyleSheet("border: 1px solid rgb(60,173,33);\nbackground-color: rgb(255, 255, 255);\nfont: 12pt \"Yu Gothic UI\";\npadding: 5px;\nborder-radius: 3px;");
    }

}

void QuickLogging::showTime(){
    int index=-1;
    for(int i=0; i<items.size(); i++){
        if(items[i]->isSlected){
            index = i;
        }
    }
    if(index!=-1){
        int curTime = items[index]->time;
        le_time->setText(QString("%1%2: %3%4: %5%6").arg(curTime/36000).arg(curTime%36000/3600).arg(curTime%3600/600).arg(curTime%600/60).arg(curTime%60/10).arg(curTime%10));
        le_time_collapse->setText(le_time->text());
    } else {
        le_time->setText("Check In");
        le_time_collapse->setText(le_time->text());
    }
}
