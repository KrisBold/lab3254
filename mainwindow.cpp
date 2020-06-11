#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "QTableView"
#include "QList"
#include "QBarSet"
#include "QBarSeries"
#include "QBarCategoryAxis"
#include "QValueAxis"
#include <QVector>
#include "strategy.h"
#include "foldersrtategy.h"
#include "filetypestrategy.h"
#include "methodprint.h"
#include <QAbstractItemModel>
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries|QDir::NoDotAndDotDot);
    model->setRootPath(QDir::rootPath());
    ui->treeView->setModel(model);

    ui->comboBox->addItem("по папкам");
    ui->comboBox->addItem("по файлам");

    ui->comboBox_2->addItem("таблица");
    ui->comboBox_2->addItem("диаграмма");
    ui->comboBox_2->addItem("гистограмма");

    ui->widget->setContentsMargins(0,0,0,0);
    ui->treeView->model()->dataChanged(ui->treeView->currentIndex(), ui->treeView->currentIndex());
    QObject::connect(model,SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)),this, SLOT(on_treeView_clicked(const QModelIndex &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: Folder()
{
  strat1->DoStrategy(ui->treeView->currentIndex(), model, obj);
  switch(ui->comboBox_2->currentIndex())
  {
  case Table:
      return PrintTable(ui, obj);
  case Pie:
      return PrintPieChart(ui, obj);
  case Bar:
      return PrintBarChart(ui,obj);
  }
}

void MainWindow:: FileType()
{
    strat2->DoStrategy(ui->treeView->currentIndex(), model, obj);
    switch(ui->comboBox_2->currentIndex())
    {
    case Table:
       return  PrintTable(ui, obj);
    case Pie:
       return  PrintPieChart(ui, obj);
    case Bar:
       return  PrintBarChart(ui,obj);
    }
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QFileInfo fileinfo = model->fileInfo(index);
    if(ui->comboBox->currentText()=="по папкам")
    {
        Folder();
    }
    if(ui->comboBox->currentText()=="по файлам")
    {
        FileType();
    }
}

void MainWindow::PrintTable(Ui::MainWindow *ui, Object obj)
{
    print1->UpdateData(obj, hlayout, vlayout);
    ui->widget->setLayout(vlayout);
}

void MainWindow::PrintPieChart(Ui::MainWindow *ui,Object obj)
{
    print2->UpdateData(obj, hlayout, vlayout);
    ui->widget->setLayout(vlayout);
}

void MainWindow::PrintBarChart(Ui::MainWindow *ui,Object obj)
{
    print3->UpdateData(obj, hlayout, vlayout);
    ui->widget->setLayout(vlayout);
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1=="таблица")
    {
        PrintTable(ui, obj);
    }
    if(arg1=="диаграмма")
    {
        PrintPieChart(ui, obj);
    }
    if(arg1=="гистограмма")
    {
        PrintBarChart(ui,obj);
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="по папкам")
    {
        Folder();
    }
    if(arg1=="по файлам")
    {
       FileType();
    }
}

