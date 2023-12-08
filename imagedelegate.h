#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class imagedelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  imagedelegate(QObject* parent = nullptr);
  virtual ~imagedelegate();

  // QAbstractItemDelegate interface
public:
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  void destroyEditor(QWidget *editor, const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


  QString displayText(const QVariant &value, const QLocale &locale) const override;
};

#endif // IMAGEDELEGATE_H
