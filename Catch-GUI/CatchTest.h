#ifndef CATCHTEST_H
#define CATCHTEST_H

#include <QString>
#include <QStringList>

class CatchTest
{
public:
    CatchTest(const QString& name, const QStringList& tags);

    static CatchTest ParseFromCommandLine(const QStringList& cmd);

    const QString &Name() const;

    const QStringList &Tags() const;

private:
    QString m_Name;
    QStringList m_Tags;

};

#endif // CATCHTEST_H
