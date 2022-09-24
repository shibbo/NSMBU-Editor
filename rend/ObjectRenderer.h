#ifndef OBJECTRENDERER_H
#define OBJECTRENDERER_H

#include <QPainter>
#include "game/obj/Objects.h"

/* implementations for the basic renderers
 * more complex renderers will go in their own file
 */
class ObjectRenderer {
public:
    ObjectRenderer() {

    }

    ObjectRenderer(Object *pObj) {

    }

    virtual ~ObjectRenderer() {

    }

    virtual void render(QPainter *, QRect *) {

    }
};

class RoundedRectRenderer : public ObjectRenderer {
public:
    RoundedRectRenderer();
    RoundedRectRenderer(const Object *pObj, QString text, QColor color, QTextOption align = Qt::AlignHCenter | Qt::AlignVCenter);

    void render(QPainter *pPainter, QRect *pDrawRect);

protected:
    const Object* mObj;
    QString mText;
    QColor mColor;
    QTextOption mAlign;
};

#endif // OBJECTRENDERER_H
