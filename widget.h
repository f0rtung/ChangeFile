#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileInfoList>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_check_clicked();

private:
    Ui::Widget *ui;
    QFileInfoList* files;
};

#endif // WIDGET_H
