#ifndef EXEPICKERWIDGET_H
#define EXEPICKERWIDGET_H

#include <QWidget>
#include <QFileInfo>

namespace Ui {
class ExePickerWidget;
}

class ExePickerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExePickerWidget(QWidget *parent = 0);
    ~ExePickerWidget();

    const QFileInfo& FilePath() const;

public slots:
    void BrowseExe();

private:
    Ui::ExePickerWidget *ui;
    QFileInfo m_Info;
};

#endif // EXEPICKERWIDGET_H
