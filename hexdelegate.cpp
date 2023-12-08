#include "hexdelegate.h"

#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QComboBox>

std::string b2sHex(uint8_t byte) {
    std::string s(3,0);
    sprintf(const_cast<char*>(s.c_str()), "0x%0.2X", byte);
    return s;
}

HexDelegate::HexDelegate(QObject *parent) {}
HexDelegate::~HexDelegate() {}

void HexDelegate::paint(QPainter *painter,          // отвечает за ОТРИСОВКУ в тейбле
                  const QStyleOptionViewItem &option,
                  const QModelIndex &index) const
{
    painter->save(); //сохр что было перед нами

    QVariant val = index.data(Qt::DisplayRole);
    if (val.canConvert<int>()) {
        QString bytesStr = QString(b2sHex(val.toInt()).c_str());
        painter->drawText(option.rect, bytesStr,QTextOption());
    } else {
    }
// если не проверять на canConvert, то просто напишет нули в случае плохих данных

    painter->restore(); // возвращаем как закончили
}

QSize HexDelegate::sizeHint(const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{
    return {20, 15};
}

QWidget *HexDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox* cBox = new QComboBox(parent);
// если не указывать родителя, то цепляться комбо будет к разметке уровнем выше - к углу IDE, а не виджета
    for (int ch = 0; ch < 0x100; ch++) {
        cBox->addItem(QString("x%1 [%2] %3").arg(b2sHex(ch).c_str()).arg(ch).arg(char(ch)), ch);
    }
    return cBox;
}

void HexDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const {}

void HexDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(!index.isValid())
        return;
    QComboBox* cBox = qobject_cast<QComboBox*>(editor);
    if(!cBox)
        return; // не получилось скастить

    QVariant val = index.data(Qt::DisplayRole); //берем данные
    int cBoxIndex = cBox->findData(val);  // находим по данным индекс, где эти данные
    cBox->setCurrentIndex(cBoxIndex);       // индекс комбы должен быть таким же
// если этот код не прогонять, то комбобокс будет при клике показывать нудлевую строку, а не ту, где выбранные данные
}

void HexDelegate::setModelData(QWidget *editor,
                               QAbstractItemModel *model,
                               const QModelIndex &index) const
{
    if(!index.isValid())
        return;
    QComboBox* cBox = qobject_cast<QComboBox*>(editor);
    if(!cBox)
        return; // не получилось скастить

    QVariant val = cBox->currentData();
    model->setData(index, val);
}

void HexDelegate::updateEditorGeometry(QWidget *editor,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{ editor->setGeometry(option.rect); }
