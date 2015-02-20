#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QStringList>
#include <QDateTime>
#include <QMessageBox>
#include <QHash>
#include <QTextStream>

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
    path = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(path);
    QDir dir(path);
    files = new QFileInfoList(dir.entryInfoList(QDir::Files));
    int count = files->count();
    for(int i = 0; i < count; i++){
        ui->textEdit_2->append(files->at(i).fileName());
        ui->textEdit->append(files->at(i).lastModified().toString());
    }
    ui->check->setEnabled(true);
}

void Widget::on_check_clicked()
{
    if(!files->contains(QFileInfo("checkchangefile.txt"))){
        QMessageBox::information(this,"Внимание!", "Наблюдение за каталогом не производилось. Сейчас будет произведено первое сканирование");
        QString savefile = QFileDialog::getSaveFileName(this, "Save file", path);
        QFile file(savefile);
        if(file.open(QIODevice::WriteOnly)){
            QTextStream txt(&file);
            int count = files->count();
            for(int i = 0; i < count; ++i){
                txt << files->at(i).fileName() + ";" + files->at(i).lastModified().toString(Qt::ISODate) + '\n';
            }
            file.close();
        }
        else
            QMessageBox::information(this, "Ошибка!", "Не возможно открыть файл!");


    }
}
