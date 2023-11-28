#include "imagemodel.h"

ImageModel::ImageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}


void ImageModel::setImage(const QImage &image)
{
    beginResetModel();
    modelImage = image;
    endResetModel();
}

int ImageModel::rowCount(const QModelIndex & /* parent */) const
{
    return modelImage.height();
}

int ImageModel::columnCount(const QModelIndex & /* parent */) const

{
    return modelImage.width();
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return modelImage.pixelColor(index.column(), index.row());
}


QVariant ImageModel::headerData(int /* section */,
                                Qt::Orientation /* orientation */,
                                int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(1, 1);
    return QVariant();
}

