#include "TreeNode.h"

TreeNode::TreeNode() :
    m_Parent(nullptr),
    m_SubElements()
{

}

TreeNode::TreeNode(TreeNode *parent, int row) :
    m_Parent(parent),
    m_Row(row),
    m_SubElements()
{

}

TreeNode *TreeNode::Parent() const
{
    return m_Parent;
}

int TreeNode::Row() const
{
    return m_Row;
}

void TreeNode::SetRow(int row)
{
    m_Row = row;
}

void TreeNode::AppendChild(TreeNode *child)
{
    child->m_Parent = this;
    child->SetRow(m_SubElements.size());
    m_SubElements.append(child);
}

const QList<TreeNode*> &TreeNode::SubElements() const
{
    return m_SubElements;
}

