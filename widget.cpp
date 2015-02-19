#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QStringList>
#include <QDateTime>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(path);
    QDir dir(path);
    files = new QFileInfoList(dir.entryInfoList(QDir::Files));
    for(int i = 0; i < files->count(); i++){
        ui->textEdit_2->append(files->at(i).fileName());
        ui->textEdit->append(files->at(i).lastModified().toString());
    }
    ui->check->setEnabled(true);
}

void Widget::on_check_clicked()
{
    if(!files->contains(QFileInfo("checkchangefile.txt"))){
        QMessageBox::information(this,"Внимание!", "Наблюдение за каталогом не производилось. Сейчас будет произведено первое сканирование");
    }
}
