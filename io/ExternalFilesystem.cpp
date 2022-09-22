#include "io/Filesystem.h"

ExternalFilesystem::ExternalFilesystem(QString baseDir) {
    mBasePath = baseDir;
}

ExternalFilesystem::~ExternalFilesystem() {

}

bool ExternalFilesystem::directoryExists(QString path) {
    return QDir(mBasePath + path).exists();
}

void ExternalFilesystem::directoryContents(QString path, QDir::Filter filter, QList<QString>& out) {
    out.clear();

    QStringList res = QDir(mBasePath + path).entryList(filter | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase | QDir::DirsFirst);
    for (int i = 0; i < res.size(); i++) {
        out.append(res[i]);
    }
}

bool ExternalFilesystem::fileExists(QString path) {
    return QFile(mBasePath + path).exists();
}

FileBase* ExternalFilesystem::openFile(QString path) {
    return new ExternalFile(this, mBasePath + path);
}


bool ExternalFilesystem::save(FileBase* pFile) {
    // can't really save the filesystem itself
    return true;
}

bool ExternalFilesystem::deleteFile(QString path) {
    QFile file(mBasePath + path);

    if (!file.exists()) {
        return false;
    }

    return file.remove();
}

bool ExternalFilesystem::renameFile(QString path, QString newName) {
    QFile file(mBasePath + path);

    if (!file.exists()) {
        return false;
    }

    return file.rename(newName);
}

bool ExternalFilesystem::renameDir(QString path, QString newName) {
    QDir dir(mBasePath + path);

    if (!dir.exists()) {
        return false;
    }

    QString newPath = dir.path() + "/" + newName;
    return dir.rename(path, newPath);
}

bool ExternalFilesystem::copyFile(QString path, QString newPath) {
    QFile file(mBasePath + path);

    if (!file.exists()) {
        return false;
    }

    return file.copy(newPath);
}
