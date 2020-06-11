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
    QObject::connect(model,SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)),this, SLOT(reprint(const QModelIndex &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: Folder()
{
  strat=new folderSrtategy();
  strat->DoStrategy(ui->treeView->currentIndex(), model, obj);
  if(ui->comboBox_2->currentText()=="таблица")
      PrintTable(ui, obj);
  if(ui->comboBox_2->currentText()=="диаграмма")
      PrintPieChart(ui, obj);
  if(ui->comboBox_2->currentText()=="гистограмма")
      PrintBarChart(ui,obj);
  delete strat;
}

void MainWindow:: FileType()
{
    strat=new fileTypeStrategy();
    strat->DoStrategy(ui->treeView->currentIndex(), model, obj);
    if(ui->comboBox_2->currentText()=="таблица")
        PrintTable(ui, obj);
    if(ui->comboBox_2->currentText()=="диаграмма")
        PrintPieChart(ui, obj);
    if(ui->comboBox_2->currentText()=="гистограмма")
        PrintBarChart(ui,obj);
    delete strat;
}

void MainWindow:: on_treeView(const QModelIndex &index)
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

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
   on_treeView(index);
}

void MainWindow::PrintTable(Ui::MainWindow *ui, Object obj)
{

    print= new TableBridge();
    print->UpdateData(obj, hlayout, vlayout);
    ui->widget->setLayout(vlayout);
}

void MainWindow::PrintPieChart(Ui::MainWindow *ui,Object obj)
{
    print= new PieBridge();
    print->UpdateData(obj, hlayout, vlayout);
    ui->widget->setLayout(vlayout);
}

//вывод инвормации в виде гистограммы
void MainWindow::PrintBarChart(Ui::MainWindow *ui,Object obj)
{
    print= new BarBridge();
    print->UpdateData(obj, hlayout, vlayout);
    ui->widget->setLayout(vlayout);
}

//изменение вида вывода информации
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

void MainWindow::reprint(const QModelIndex & index)
{
   on_treeView(index);
}
