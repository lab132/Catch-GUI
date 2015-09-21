#include "TagFilterWidget.h"
#include "ui_TagFilterWidget.h"

TagFilterWidget::TagFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagFilterWidget)
{
    ui->setupUi(this);
}

TagFilterWidget::~TagFilterWidget()
{
    delete ui;
}
