#include "chardelegate.h"

#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QEvent>
#include <QMouseEvent>

CharDelegate::CharDelegate(QObject* parent) { }
CharDelegate::~CharDelegate() { }

void CharDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();

    QVariant val = index.data(Qt::DisplayRole);
    if (val.canConvert<int>()) {
        unsigned char c = val.toInt();
        if (c < 32) {
            painter->drawText(option.rect, QString("SERV"),QTextOption());
        } else if (c > 127) {
            painter->drawText(option.rect, QString("OVER"),QTextOption());
        } else {
            QTextOption to;
            to.setAlignment(Qt::AlignHCenter);
            painter->drawText(option.rect, QString(1,c),QTextOption());
        }
    } else {

    }

    painter->restore();
}

QSize CharDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    return {20, 15};
}

bool CharDelegate::editorEvent(QEvent *event,
                               QAbstractItemModel *model,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        int val = index.data(Qt::DisplayRole).toInt();

        if (mouseEvent->button() == Qt::LeftButton)
            val++;
        else if (mouseEvent->button() == Qt::RightButton)
            val--;
        model->setData(index, val);
        return true;
    }
    if (event->type() == QEvent::MouseButtonDblClick)
        return true;
    return false;
}
