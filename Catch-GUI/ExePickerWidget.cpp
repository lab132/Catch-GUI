#include "ExePickerWidget.h"
#include "ui_ExePickerWidget.h"

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
