#ifndef BYTEARRAYMODEL_H
#define BYTEARRAYMODEL_H
#include <QAbstractItemModel>
#include <QObject>


class ByteArrayModelPrivate;

class ByteArrayModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ByteArrayModel(QObject* parent = nullptr);
    virtual ~ByteArrayModel();
    void setArray(const QByteArray& data);
    QByteArray getArray() const;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    ByteArrayModelPrivate* m_dptr; // хитрость, чтобы спрятать данные

    // QAbstractItemModel interface
};

#endif // BYTEARRAYMODEL_H
