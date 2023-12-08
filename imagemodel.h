#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QAbstractTableModel>
#include <QImage>


class ImageModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ImageModel(QObject *parent = 0);

    void setImage(const QImage &image);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole | Qt::EditRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole | Qt::EditRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QImage getModelImage();

private:
    QImage modelImage;
};


#endif
