#ifndef BINDELEGATE_H
#define BINDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class BinDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  BinDelegate(QObject* parent = nullptr);
  virtual ~BinDelegate();

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

#endif // BINDELEGATE_H
