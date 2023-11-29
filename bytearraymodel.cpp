#include "bytearraymodel.h"
#include <QtDebug>

//========================= // PostIMPLementation метод (не прыщ)
class ByteArrayModelPrivate {
public:
    QByteArray data;
    const int rowLenght = 8;

};
//-------------------------

ByteArrayModel::ByteArrayModel(QObject *parent)
    : QAbstractItemModel{parent}
    , m_dptr{new ByteArrayModelPrivate()} {}

ByteArrayModel::~ByteArrayModel() {
    delete m_dptr;
}

void ByteArrayModel::setArray(const QByteArray &data)
{
    beginResetModel(); // оповещение ВСЕХ, что пошло изменение
    m_dptr->data = data;
    endResetModel();
}

QByteArray ByteArrayModel::getArray() const
{
    return m_dptr->data;
}

QModelIndex ByteArrayModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex ByteArrayModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ByteArrayModel::rowCount(const QModelIndex &parent) const
{
    return m_dptr->data.size()/m_dptr->rowLenght
                               + !!(m_dptr->data.size()%m_dptr->rowLenght);
}

int ByteArrayModel::columnCount(const QModelIndex &parent) const
{
    return m_dptr->rowLenght;
}

QVariant ByteArrayModel::data(const QModelIndex &index, int role) const
{

    QString binStr = "";
    uint8_t temp = 0;
    QVariant result;
    switch(role) {
      case Qt::DisplayRole:
      case Qt::EditRole:   {  // EditRole нужен, чтобы когда будем даблклик на ячейку, там не было пусто
        int row = index.row();
        int col = index.column();
        int originalIndex = row*m_dptr->rowLenght+col;
        if (originalIndex < m_dptr->data.size() ) {
            if (binView == true) {
                temp = static_cast<uint8_t>(m_dptr->data[originalIndex]);
                binStr += QString::number(temp, 2); // выводит число по основанию 2
                result = QVariant(binStr);
            } else
                result = QVariant(uint8_t(m_dptr->data[originalIndex]));
        }
      }
        break;
      default:
        break;
    }
    return result;



}

Qt::ItemFlags ByteArrayModel::flags(const QModelIndex &index) const
{
    if (binView == false)
      return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    else
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool ByteArrayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    switch(role) {
      case Qt::EditRole:   {
        int row = index.row();
        int col = index.column();
        int originalIndex = row*m_dptr->rowLenght+col;
        if (originalIndex < m_dptr->data.size() ) {
            m_dptr->data[originalIndex] = (char)value.toInt();
        }
      }
        break;
      default:
        break;
    }
    emit dataChanged(index, index); // почему-то не меняет значение первого "столбца"
    return result;
}

void ByteArrayModel::switchFormat() {
    binView = !binView;
}

