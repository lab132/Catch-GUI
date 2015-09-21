#include "ExePickerWidget.h"
#include "ui_ExePickerWidget.h"
#include <QFileDialog>

ExePickerWidget::ExePickerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExePickerWidget)
{
    ui->setupUi(this);
}

ExePickerWidget::~ExePickerWidget()
{
    delete ui;
}

const QFileInfo &ExePickerWidget::FilePath() const
{
    return m_Info;
}

void ExePickerWidget::BrowseExe()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Select Catch Exe"), QString(), tr("Catch Exe (*.exe)"));

    m_Info = QFileInfo(fileName);

    ui->lineEdit->setText(fileName);
}
