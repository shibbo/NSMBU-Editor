#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#include <QWidget>
#include <QLayout>
#include <QList>

#include "game/Level.h"

class LevelView : public QWidget
{
    Q_OBJECT
public:
    explicit LevelView(QWidget *parent, Level *pLevel);

    void screenshot(QRect rect);

signals:


protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    void paint(QPainter& painter, QRect rect, float zoomLvl, bool selections);


    Level* mLevel;
    QRect mDrawRect;
    float mZoom;
    QColor mBackgroundColor;

};

#endif // LEVELVIEW_H
