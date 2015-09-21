#ifndef EXEPICKERWIDGET_H
#define EXEPICKERWIDGET_H

#include <QWidget>

namespace Ui {
class ExePickerWidget;
}

class ExePickerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExePickerWidget(QWidget *parent = 0);
    ~ExePickerWidget();

public slots:
    void BrowseExe();

private:
    Ui::ExePickerWidget *ui;
};

#endif // EXEPICKERWIDGET_H
