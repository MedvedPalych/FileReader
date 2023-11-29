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

    // + QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void switchFormat();
private:
    ByteArrayModelPrivate* m_dptr; // хитрость, чтобы спрятать данные
    bool binView = false;
    // - QAbstractItemModel interface
};

#endif // BYTEARRAYMODEL_H
