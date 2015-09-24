#include "CatchTest.h"

CatchTest::CatchTest(const QString &name, const QStringList &tags) :
    m_Name(name),
    m_Tags(tags)
{

}

CatchTest CatchTest::ParseFromCommandLine(const QStringList &cmd)
{
    Q_ASSERT(cmd.size() >= 2);
    Q_ASSERT(cmd[0].startsWith("  "));

    QString name = cmd[0].trimmed();
    QStringList tags;
    if(cmd[1].startsWith("    "))
    {
        tags = cmd[1].trimmed().split(QRegExp("[\\[\\]]"));
        QMutableStringListIterator i(tags);
        while(i.hasNext())
        {
            QString cur = i.next();
            if(cur.isEmpty())
            {
                i.remove();
            }
        }
    }
    return CatchTest(name, tags);
}

const QString& CatchTest::Name() const
{
    return m_Name;
}

const QStringList& CatchTest::Tags() const
{
    return m_Tags;
}

