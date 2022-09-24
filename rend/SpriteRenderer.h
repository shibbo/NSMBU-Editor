#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "ObjectRenderer.h"

class SpriteRenderer : public ObjectRenderer {
public:
    SpriteRenderer(const Sprite *pSprite);

    void render(QPainter *pPainter, QRect *pDrawRect);

    RoundedRectRenderer* mRect;
    const Sprite* mSprite;
};

#endif // SPRITERENDERER_H
