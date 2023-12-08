#ifndef PROGRESSBARDELEGATE_H
#define PROGRESSBARDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class ProgressBarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ProgressBarDelegate(QObject* parent = 0);
    virtual ~ProgressBarDelegate();

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // PROGRESSBARDELEGATE_H
