#ifndef HEXDELEGATE_H
#define HEXDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class HexDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit HexDelegate(QObject *parent = nullptr);
    virtual ~HexDelegate();

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void destroyEditor(QWidget *editor, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // HEXDELEGATE_H
