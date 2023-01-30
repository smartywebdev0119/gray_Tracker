#ifndef QUICKLOGGING_H
#define QUICKLOGGING_H

#include <QWidget>

namespace Ui {
class QuickLogging;
}

class QuickLogging : public QWidget
{
    Q_OBJECT

public:
    explicit QuickLogging(QWidget *parent = nullptr);
    ~QuickLogging();


private:
    Ui::QuickLogging *ui;
};

#endif // QUICKLOGGING_H
