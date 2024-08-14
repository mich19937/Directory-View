#ifndef DIRECTORYTABLEMODEL_H
#define DIRECTORYTABLEMODEL_H

#include <QFileInfo>
#include <QAbstractTableModel>
#include <QQmlEngine>

class DirectoryTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QFileInfoList dirEntries;
public:
    explicit DirectoryTableModel(QObject* parent = nullptr);
    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    int columnCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public slots:
    void updateDirEntries(QString const& dirPath);
};

#endif // DIRECTORYTABLEMODEL_H
