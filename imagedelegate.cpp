#include "imagedelegate.h"

#include <iostream>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QLineEdit>
#include <QSpinBox>
#include <QSize>


imagedelegate::imagedelegate(QObject* parent) {

}

imagedelegate::~imagedelegate() { }


void imagedelegate::paint(QPainter *painter,
                    const QStyleOptionViewItem &option,
                    const QModelIndex &index) const {

  painter->save(); //сохр что было перед нами
  QColor bgCol = index.data(Qt::DisplayRole).value<QColor>();
  QString colCode = bgCol.name();
  // Вот это охренеть, можно вот ТАК нагло привести QVariant index.data к колору?
  // не понимаю, почему нельзя просто QColor привести к строке как мы привели
  // QVariant к колору для bgCol
  painter->fillRect(option.rect, bgCol);
  painter->drawText(option.rect, colCode);

  painter->restore(); // возвращаем как закончили

}


QSize imagedelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex &index) const {
  QRect headerRect = option.rect;
  headerRect.setWidth(100);
  // ПОЧЕМУ игнорируется и sizeHint, и выполнение этих указаний в paint???????
}


QString imagedelegate::displayText(const QVariant &value,
                                   const QLocale &locale) const {
  return QStyledItemDelegate::displayText(value, locale);
}


QWidget *imagedelegate::createEditor(QWidget *parent,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
  QLineEdit* line = new QLineEdit(parent);
  line->setInputMask("hh.hh.hh;_");
  return line;

}


void imagedelegate::destroyEditor(QWidget *editor,
                            const QModelIndex &index) const {}


void imagedelegate::setEditorData(QWidget *editor,
                            const QModelIndex &index) const {

  if(!index.isValid())
    return;
  QLineEdit* line = qobject_cast<QLineEdit*>(editor);
  if(!line)
    return; // не получилось скастить
  QColor bgCol = index.data(Qt::DisplayRole).value<QColor>();
  line->setText(QString("%1").arg(bgCol.name()));

}


void imagedelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                           const QModelIndex &index) const {
  if(!index.isValid())
      return;
  QLineEdit* line = qobject_cast<QLineEdit*>(editor);
  if(!line)
      return; // не получилось скастить

  int R{}, G{}, B{};
  std::string str = line->text().toStdString();
  std::sscanf(str.c_str(), "%x.%x.%x", &R, &G, &B);
  model->setData(index, QColor(R, G, B));

}


void imagedelegate::updateEditorGeometry(QWidget *editor,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
  editor->setFixedWidth(100);
  // setBaseSize не работает как ожидается: размер берется из
  // option.rect; а если вот так, тогда ширина учитывается
  editor->setGeometry(option.rect);
}

