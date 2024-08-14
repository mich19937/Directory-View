#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

#include "directorytablemodel.h"

class AppController : public QObject
{
    Q_OBJECT
    QString dirPath;
    std::unique_ptr<DirectoryTableModel> dirTableModel = std::make_unique<DirectoryTableModel>();
public:
    Q_PROPERTY(bool isDirPathValid READ getIsDirPathValid NOTIFY isDirPathValidChanged)
    Q_PROPERTY(QString dirPath MEMBER dirPath WRITE setDirPath NOTIFY dirPathChanged)
    Q_PROPERTY(DirectoryTableModel* dirTableModel READ getDirTableModel CONSTANT)
    
    explicit AppController(QObject *parent = nullptr);

    bool getIsDirPathValid() const;
    DirectoryTableModel* getDirTableModel() const;
public slots:
    void setDirPath(QString const& arg);
    
signals:
    void isDirPathValidChanged();
    void dirPathChanged();

private:
    void onDirPathChanged();
};

#endif // APPCONTROLLER_H
