#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void BuildCommandLine();

public slots:
    void FetchTestsAndTags();
    void RunTests();
    void OnRunFinished(int, QProcess::ExitStatus);
    void OnFetchFinished(int, QProcess::ExitStatus);
    void OnItemChanged(QStandardItem*);

private:
    Ui::MainWindow *ui;

    QProcess* m_Process;
    QStringList m_FetchArguments;
    QStandardItemModel* m_TagModel;
    QStandardItemModel* m_TestModel;

    QStringList m_RunArguments;
};

#endif // MAINWINDOW_H
