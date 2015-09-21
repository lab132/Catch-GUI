#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Process(nullptr),
    m_TagModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->andTagFilter->ListView()->setModel(m_TagModel);
    m_FetchArguments << "-l";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FetchTestsAndTags()
{
    if(ui->exePicker->FilePath().exists())
    {
        m_Process = new QProcess(this);
        connect( m_Process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(OnFetchFinished(int,QProcess::ExitStatus)));
        m_Process->start(ui->exePicker->FilePath().absoluteFilePath(), m_FetchArguments);
    }
}

void MainWindow::OnFetchFinished(int, QProcess::ExitStatus)
{
    QString output = QString(m_Process->readAllStandardOutput());

    qDebug( output.toStdString().c_str() );

    m_TagModel->clear();

    QStringList list = output.split("\n");

    for(QString string : list)
    {
        // The model becomes the owner of the created items, so no delete needed
        auto* item = new QStandardItem(string);
        m_TagModel->appendRow(item);
    }


}
