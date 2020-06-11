#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFileSystemModel"
#include "QDir"
#include "QGridLayout"
#include "QPieSeries"
#include "QChartView"
#include "QChart"
#include "strategy.h"
#include "filetypestrategy.h"
#include "foldersrtategy.h"
#include "methodprint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void PrintTable(Ui::MainWindow *ui,Object obj);
    void PrintPieChart(Ui::MainWindow *ui,Object obj);
    void PrintBarChart(Ui::MainWindow *ui,Object obj);
public slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_comboBox_2_currentTextChanged(const QString &arg1);
    void  FileType();
    void  Folder();
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    Object obj;
    QList<QString> DirList;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;
    Strateg *strat;
    AbstractBridge *print;
};

#endif // MAINWINDOW_H
