#include "TreeModel.h"
#ifndef TREEMODEL_INL
#define TREEMODEL_INL

template <typename T>
inline
TreeModel<T>::TreeModel()
{

}

template <typename T>
inline
QModelIndex TreeModel<T>::index(int row, int column, const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return createIndex(row, column, (m_RootNodes[row]));
    }
    T* parentNode = static_cast<T*>(parent.internalPointer());
    return createIndex(row, column, (parentNode->SubElements()[row]));
}

template <typename T>
inline
QModelIndex TreeModel<T>::parent(const QModelIndex &child) const
{
    if(!child.isValid())
    {
        return QModelIndex();
    }
    T* node = static_cast<T*>(child.internalPointer());
    if(node->Parent() == nullptr)
    {
        return QModelIndex();
    }
    else
    {
        return createIndex(node->Parent()->Row(), 0, (node->Parent()));
    }
}

template <typename T>
inline
int TreeModel<T>::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return m_RootNodes.size();
    }
    else
    {
        T* node = static_cast<T*>(parent.internalPointer());
        return node->SubElements().size();
    }
}

template <typename T>
inline
int TreeModel<T>::columnCount(const QModelIndex &parent) const
{
    return 1;
}

template <typename T>
inline
QVariant TreeModel<T>::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }
    T* node = static_cast<T*>(index.internalPointer());

    return node->Data(role, index.column());
}

#endif

