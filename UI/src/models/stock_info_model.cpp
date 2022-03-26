#include <models/stock_info_model.hpp>

StockInfoModel::StockInfoModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int StockInfoModel::rowCount(const QModelIndex & /*parent*/) const
{
   return 0;
}

int StockInfoModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

QVariant StockInfoModel::data(const QModelIndex &index, int role) const
{
    // if (role == Qt::DisplayRole)
    //    return QString("Row%1, Column%2")
    //                .arg(index.row() + 1)
    //                .arg(index.column() +1);

    return QVariant();
}

QVariant StockInfoModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Item ID");
        case 1:
            return QString("Item Name");
        case 2:
            return QString("Current Stock");
        case 3:
            return QString("Profit");
        }
    }
    return QVariant();
}