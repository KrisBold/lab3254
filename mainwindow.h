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

public slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_comboBox_2_currentTextChanged();
    void  FileType();
    void  Folder();
    void changePercentageDisplay();
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    enum NamePrint {
       Table,
       Pie,
       Bar
    };

    enum NamePrint2 {
        FOLDER,
        FILETYPE
    };

    Ui::MainWindow *ui;
    QFileSystemModel *model;
    Object obj;
    QVBoxLayout *vlayout;
    Strateg *strat2;
    Strateg *strat1;
    QStandardItemModel *Tmodel;
    AbstractBridge *print1;
    AbstractBridge *print2;
    AbstractBridge *print3;
    QtCharts::QValueAxis *axisY;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    QTableView * tableView ;
};

#endif // MAINWINDOW_H
