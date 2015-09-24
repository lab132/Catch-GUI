#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QMessageBox>
#include "CatchTest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Process(nullptr),
    m_TagModel(new QStandardItemModel(this)),
    m_TestModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->andTagFilter->ListView()->setModel(m_TagModel);
    ui->orTagFilter->ListView()->setModel(m_TestModel);
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

    if(list.size() < 0 || !list[0].startsWith("All available test cases:"))
    {
        QMessageBox errorBox;
        errorBox.setText(tr("The selected exe is not a Catch exe!"));
        errorBox.setIcon(QMessageBox::Critical);
        errorBox.exec();
        return;
    }

    list.removeFirst();

    QStringList tags;

    while(list.size() > 0 && list[0].startsWith("  "))
    {
        QStringList toParse = list.mid(0,2);

        CatchTest test = CatchTest::ParseFromCommandLine(toParse);
        list.removeFirst();

        if(test.Tags().size() != 0)
        {
            list.removeFirst();
        }

        QStandardItem* testName = new QStandardItem(test.Name());
        testName->setCheckable(true);

        tags << test.Tags();
        m_TestModel->appendRow(testName);

    }

    tags.removeDuplicates();

    for(auto& string : tags)
    {
        QStandardItem* tag = new QStandardItem("[" + string + "]");
        tag->setCheckable(true);

        m_TagModel->appendRow(tag);
    }


}
