#include "CatchCommandLine.h"
#include "ui_CatchCommandLine.h"

CatchCommandLine::CatchCommandLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatchCommandLine)
{
    ui->setupUi(this);
}

CatchCommandLine::~CatchCommandLine()
{
    delete ui;
}

void CatchCommandLine::SetText(const QString &cmd)
{
    ui->commandLine->setText(cmd);
}
