#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <QList>

template < typename T >
class TreeModel : public QAbstractItemModel
{
public:
    TreeModel();

signals:

public slots:

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QList<T*> m_RootNodes;
};

#include "TreeModel.inl"

#endif // TREEMODEL_H
