#ifndef LABELFILTERWIDGET_H
#define LABELFILTERWIDGET_H

#include <QWidget>

namespace Ui {
class TagFilterWidget;
}

class TagFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagFilterWidget(QWidget *parent = 0);
    ~TagFilterWidget();

private:
    Ui::TagFilterWidget *ui;
};

#endif // LABELFILTERWIDGET_H
