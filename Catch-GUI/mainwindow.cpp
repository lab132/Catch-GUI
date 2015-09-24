#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QMessageBox>
#include "CatchTest.h"
#include <QDebug>

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
    QStringList arguments;

    arguments << ui->exePicker->FilePath().absoluteFilePath();

    arguments << "-r" << "xml";

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

    arguments << testsAndTags.join(",");

    ui->catchCommandLine->SetText(arguments.join(" "));
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
