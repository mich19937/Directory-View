#include "appcontroller.h"

#include <QFileInfo>

AppController::AppController(QObject *parent)
    : QObject{parent}
{
    connect(this, &AppController::dirPathChanged, this, &AppController::onDirPathChanged);
}

bool AppController::getIsDirPathValid() const {
    QFileInfo dir(dirPath);
    bool dirValid = dir.exists() && dir.isDir();
    return dirValid;
}

DirectoryTableModel* AppController::getDirTableModel() const
{
    return dirTableModel.get();
}

void AppController::setDirPath(const QString &arg)
{
    if(dirPath == arg) return;
    dirPath = arg;
    emit dirPathChanged();
}

void AppController::onDirPathChanged() {
    emit isDirPathValidChanged();
    if(getIsDirPathValid() == true)
        dirTableModel->updateDirEntries(dirPath);
}
