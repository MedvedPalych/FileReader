#include <QApplication>
#include "progressbardelegate.h"

ProgressBarDelegate::ProgressBarDelegate(QObject* parent)
    :QStyledItemDelegate(parent) {

}

ProgressBarDelegate::~ProgressBarDelegate() {}

void ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
// копипаст с документации прогрессбара
            int progress = index.data().toInt();
            QStyleOptionProgressBar progressBarOption;
            progressBarOption.rect = option.rect;
            progressBarOption.minimum = 0;
            progressBarOption.maximum = 100;
            progressBarOption.progress = progress;
            progressBarOption.text = QString::number(progress) + "%";
            progressBarOption.textVisible = true;
            QApplication::style()->drawControl(QStyle::CE_ProgressBar,
                                               &progressBarOption, painter);
// конец копипаста
}

QSize ProgressBarDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}
