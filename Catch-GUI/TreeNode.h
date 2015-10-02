#ifndef TREENODE_H
#define TREENODE_H


#include <QVariant>

class TreeNode
{
public:
    TreeNode();
    TreeNode(TreeNode* parent, int row);
    TreeNode* Parent() const;
    int Row() const;
    void SetRow(int row);

    void AppendChild(TreeNode* child);

    virtual QVariant Data(int row, int role) const = 0;

    const QList<TreeNode*>& SubElements() const;

    QList<TreeNode*> m_SubElements;
    TreeNode* m_Parent;
    int m_Row;
signals:

public slots:
};

#endif // TREENODE_H
