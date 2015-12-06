#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFontDialog"
#include "QFile"
#include "QFileDialog"
#include <QTextCodec>
#include "QTextStream"
#include <QSettings>
#include "QDebug"
#include "QColorDialog"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\Notebook",QSettings::NativeFormat);
    if(reg->value("isstart").toBool())
    {
        this->resize(reg->value("start_height").toInt(),reg->value("start_width").toInt());
        this->move(reg->value("start_x").toInt(),reg->value("start_y").toInt());
        delete reg;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_acAbout_triggered()
{
    QMessageBox::information(NULL,"About","Notebook version 1.0\nThe author of this software : Accelerate");
}

void MainWindow::on_acFont_triggered()
{
    bool ok;
    QFont qf= QFontDialog::getFont(&ok,this);
    if(ok)ui->txtcontext->setFont(qf);
}

void MainWindow::on_acOpen_triggered()
{
    QString q_filename = QFileDialog::getOpenFileName(this,"Open","","Text Files (*.txt)");
    if(!q_filename.isNull())
    {
       this->setWindowTitle("Notebook - " + q_filename);
       QFile files(q_filename);
       filename = q_filename;
       if(files.open(QIODevice::ReadWrite|QIODevice::Text))
       {
           QTextCodec* gbk_codec = QTextCodec::codecForName("gbk");
           QString gbk_string = gbk_codec->toUnicode(files.readAll());
           ui->txtcontext->setText(gbk_string);
           this->signal = 1;
       }
    }

}

void MainWindow::on_acNew_triggered()
{
    this->setWindowTitle("Notebook");
    ui->txtcontext->setText("");
    this->signal = 0;
}

void MainWindow::on_acSaveas_triggered()
{
     saveas();
}
void MainWindow::on_acSave_triggered()
{
    if(signal == 1)
         savein();
}
void MainWindow::closeEvent(QCloseEvent *)
{
    if (QMessageBox::Yes == QMessageBox::question(this,"提示","你要保存吗？",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes))
  {
    if(signal == 1)
    {
          savein();
    }
    else if (signal == 0)
    {
          saveas();
    }
 }
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\Notebook",QSettings::NativeFormat);
        reg->setValue("start_height",this->width());
        reg->setValue("start_width",this->height());
        reg->setValue("start_x",this->x());
        reg->setValue("start_y",this->y());
        reg->setValue("isstart",true);
        delete reg;
    this->close();
}
void MainWindow::saveas()
{
    QString q_filename = QFileDialog::getSaveFileName(this,"File Dialog","","Text Files (*.txt)");
    if(!q_filename.isNull())
    {
        QFile qf(q_filename);
        if(qf.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QTextStream in(&qf);
            in<<ui->txtcontext->toPlainText();
            qf.close();
        }
    }
}
void MainWindow::savein()
{
    QFile qf(filename);
    if(qf.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qf.resize(0);
        QTextStream in(&qf);
        in<<ui->txtcontext->toPlainText();
        qf.close();
    }
}

void MainWindow::on_acColor_triggered()
{
    QPalette qp = ui->txtcontext->palette();
    const QColor qc = QColorDialog::getColor(Qt::white,this,"Color dialog");
    if(qc.isValid())
    {
       qp.setColor(QPalette::Text,qc);
       ui->txtcontext->setPalette(qp);
    }
}
