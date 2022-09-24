#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game/Level.h"
#include "ui/LevelView.h"
#include "ui/WindowBase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public WindowBase
{
    Q_OBJECT

public:
    MainWindow(WindowBase *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Level* mLevel;
    LevelView* mLevelView;
};
#endif // MAINWINDOW_H
