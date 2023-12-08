#ifndef CHARDELEGATE_H
#define CHARDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class CharDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CharDelegate(QObject* parent = nullptr);
    virtual ~CharDelegate();

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // CHARDELEGATE_H
