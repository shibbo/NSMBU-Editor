#ifndef ENTRANCERENDERER_H
#define ENTRANCERENDERER_H

#include "ObjectRenderer.h"

class EntranceRenderer : public ObjectRenderer {
public:
    EntranceRenderer(const Entrance *entrance);

    void render(QPainter *pPainter, QRect *pDrawRect);

    RoundedRectRenderer* mRect;
    const Entrance* mEntrance;
};

#endif // ENTRANCERENDERER_H
