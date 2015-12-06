#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QEvent"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int signal = 0;
    QString filename;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void saveas();

    void savein();
private slots:
    void on_acAbout_triggered();

    void on_acFont_triggered();

    void on_acOpen_triggered();

    void on_acNew_triggered();

    void on_acSaveas_triggered();

    void on_acSave_triggered();

    void closeEvent(QCloseEvent *);

    void on_acColor_triggered();

private:
    Ui::MainWindow *ui;
    QAction *qaMain;
};

#endif // MAINWINDOW_H
