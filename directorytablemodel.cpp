#include "directorytablemodel.h"
#include <QDir>

DirectoryTableModel::DirectoryTableModel(QObject* parent)
    : QAbstractTableModel(parent) { }

int DirectoryTableModel::rowCount(const QModelIndex &parent) const
{
    return dirEntries.count();
}

int DirectoryTableModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant DirectoryTableModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(index.isValid());
    if(role == Qt::DisplayRole) {
        if(index.column() == 0) {
            return dirEntries[index.row()].fileName();
        }
        else if(index.column() == 1) {
            return dirEntries[index.row()].birthTime().toString("yyyy-MM-dd, hh:mm");
        }
        else {
            // TODO: do some logging here
        }
    }
    return QVariant();
}

QVariant DirectoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole) {
        if(section == 0)
            return "File";
        else if(section == 1) {
            return "Time created";
        }
        else {
            // TODO: do some logging here
        }
    }
    return QVariant();
}

void DirectoryTableModel::updateDirEntries(QString const& dirPath)
{
    QDir dir(dirPath);
    beginResetModel();
    dirEntries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    endResetModel();
}
