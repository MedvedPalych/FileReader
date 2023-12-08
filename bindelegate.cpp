#include "bindelegate.h"
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QEvent>
#include <QMouseEvent>
#include <QLineEdit>
#include <QRegularExpression>

unsigned char binToByte(const QString s) { // подразумевается, что на вход
  uint8_t result = 0;                      // строка строго из 0 и 1
  uint8_t len = s.length()-1;
  for (int i = 0; i <= len; i++ ) {
      if (s[len-i] == '1')
        result += 1 << i;
      else
      if (s[len-i] == '0')
        continue;
  }
  return result;
}

BinDelegate::BinDelegate(QObject* parent) {}

BinDelegate::~BinDelegate() {}

void BinDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QVariant val = index.data(Qt::DisplayRole);
    if (val.canConvert<uint8_t>()) {
        QString binStr = QString::number(val.toInt(), 2);
        painter->drawText(option.rect, binStr, QTextOption(Qt::AlignHCenter));
    }

    painter->restore();
}

QSize BinDelegate::sizeHint(const QStyleOptionViewItem &option,
                            const QModelIndex &index) const {
  return {30, 15};
}

QWidget *BinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
// в create Editor надо задать, какого типа эдитор будет
  QLineEdit* line = new QLineEdit(parent);
  line->setMaxLength(8);
  QRegularExpression regex("[01]{0,8}"); // берем только 1 и 0 и не больше 8 штук
  line->setValidator(new QRegularExpressionValidator(regex, parent));
  connect(line, &QLineEdit::textChanged,
          [=](const QString &text) {
              if  (text != regex.match(text).captured()) {
                  line->setText("");  }
              }); // йеее, лямбды рулят!
  return line;
}

void BinDelegate::destroyEditor(QWidget *editor,
                          const QModelIndex &index) const {}


void BinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if(!index.isValid())
    return;
  QLineEdit* line = qobject_cast<QLineEdit*>(editor);
  if(!line)
    return; // не получилось скастить
  QVariant val = index.data(Qt::DisplayRole); //берем данные ИЗ МОДЕЛИ
  line->setText(QString::number(val.toInt(), 2)); // взятые данные модели -> бин строка
} // отвечает за показ данных в эдиторе при активации


void BinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if(!index.isValid())
      return;
  QLineEdit* line = qobject_cast<QLineEdit*>(editor);
  if(!line)
      return; // не получилось скастить

  QString val = line->text();
  // надо преобразовать строку обратно в байт
  model->setData(index, binToByte(val));

} // отвечает за передачу введенных данных в модель


void BinDelegate::updateEditorGeometry(QWidget *editor,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}

