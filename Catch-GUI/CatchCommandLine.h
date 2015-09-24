#ifndef CATCHCOMMANDLINE_H
#define CATCHCOMMANDLINE_H

#include <QWidget>

namespace Ui {
class CatchCommandLine;
}

class CatchCommandLine : public QWidget
{
    Q_OBJECT

public:
    explicit CatchCommandLine(QWidget *parent = 0);
    ~CatchCommandLine();
    void SetText(const QString& cmd);

private:
    Ui::CatchCommandLine *ui;
};

#endif // CATCHCOMMANDLINE_H
