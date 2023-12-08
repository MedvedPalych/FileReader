#include "imagemodel.h"

ImageModel::ImageModel(QObject *parent)
    : QAbstractTableModel(parent) {}


void ImageModel::setImage(const QImage &image) {
    beginResetModel();
    modelImage = image;
    endResetModel();
}

int ImageModel::rowCount(const QModelIndex & /* parent */) const {
  return modelImage.height();
}

int ImageModel::columnCount(const QModelIndex & /* parent */) const {
  return modelImage.width();
}


QVariant ImageModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    return modelImage.pixelColor(index.column(), index.row());

}


QVariant ImageModel::headerData(int /* section */,
                                Qt::Orientation /* orientation */,
                                int role) const {
    if (role == Qt::SizeHintRole)
        return QSize(1, 1);
    return QVariant();
}

bool ImageModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    bool result = false; // а зачем
    switch(role) {
      case Qt::EditRole:   {
        modelImage.setPixelColor(index.column(), index.row(), value.value<QColor>());
        emit dataChanged(index,index);
      }
        break;
      default:
        break;
    }
    emit dataChanged(index, index);
    return result;

}

Qt::ItemFlags ImageModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

QImage ImageModel::getModelImage() {
    return this->modelImage;
}

