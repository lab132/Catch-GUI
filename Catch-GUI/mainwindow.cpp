#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QMessageBox>
#include "CatchTest.h"
#include <QDebug>
#include <QtXml>
#include <QDomDocument>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Process(nullptr),
    m_TagModel(new QStandardItemModel(this)),
    m_TestModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->testList->ListView()->setModel(m_TestModel);
    ui->orTagFilter->ListView()->setModel(m_TagModel);
    connect(m_TagModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(OnItemChanged(QStandardItem*)));
    connect(m_TestModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(OnItemChanged(QStandardItem*)));
    m_FetchArguments << "-l";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BuildCommandLine()
{
    m_RunArguments.clear();

    //m_RunArguments << ui->exePicker->FilePath().absoluteFilePath();

    m_RunArguments << "-r" << "xml";
    m_RunArguments << "-s";

    QStringList testsAndTags;

    for(int i = 0; i < m_TagModel->rowCount(); i++)
    {
        if(m_TagModel->item(i)->checkState() == Qt::Checked)
        {
            testsAndTags << m_TagModel->item(i)->text();
        }
    }

    for(int i = 0; i < m_TestModel->rowCount(); i++)
    {
        if(m_TestModel->item(i)->checkState() == Qt::Checked)
        {
            QString name = m_TestModel->item(i)->text();

            if(name.contains(QRegExp("\\s+")))
            {
                name = "\"" + name + "\"";
            }
            testsAndTags << name;
        }
    }

    m_RunArguments << testsAndTags.join(",");

    QStringList command = m_RunArguments;
    command.prepend(ui->exePicker->FilePath().absoluteFilePath());

    ui->catchCommandLine->SetText(command.join(" "));
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

void MainWindow::RunTests()
{
    if(ui->exePicker->FilePath().exists())
    {
        if(m_Process)
        {
            delete m_Process;
            m_Process = nullptr;
        }
        m_Process = new QProcess(this);
        connect( m_Process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(OnRunFinished(int,QProcess::ExitStatus)));
        m_Process->start(ui->exePicker->FilePath().absoluteFilePath(), m_RunArguments);
        ui->statusBar->showMessage(tr("Running...."));
    }
}

void MainWindow::OnRunFinished(int, QProcess::ExitStatus)
{
    QString output = QString(m_Process->readAllStandardOutput());

    qDebug() << output;

    QDomDocument document;
    if(!document.setContent(output))
    {
        ui->statusBar->showMessage(tr("Could not parse output of catch exe!"));
    }
    else
    {
       QDomElement element = document.documentElement();
       auto nodeList = element.elementsByTagName("OverallResults");
       auto lastElement = nodeList.at(nodeList.length()-1);
       int successes = lastElement.attributes().namedItem("successes").toAttr().value().toInt();
       int failures = lastElement.attributes().namedItem("failures").toAttr().value().toInt();
       int expectedFailures = lastElement.attributes().namedItem("expectedFailures").toAttr().value().toInt();

       ui->statusBar->showMessage(tr("Result: Successes: %1, Failures: %2, Expected Failures: %3").arg(successes).arg(failures).arg(expectedFailures));
    }

}

void MainWindow::OnFetchFinished(int, QProcess::ExitStatus)
{
    QString output = QString(m_Process->readAllStandardOutput());

    qDebug( output.toStdString().c_str() );

    m_TagModel->clear();
    m_TestModel->clear();

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

    for( auto& string : tags )
    {
        QStandardItem* tag = new QStandardItem("[" + string + "]");
        tag->setCheckable(true);

        m_TagModel->appendRow(tag);
    }


}

void MainWindow::OnItemChanged(QStandardItem *)
{
    BuildCommandLine();
}
