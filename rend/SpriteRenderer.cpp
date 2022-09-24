#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const Sprite *pSprite){
    mSprite = pSprite;
    mRect = new RoundedRectRenderer(mSprite, "", QColor(0, 90, 150, 150));
}

void SpriteRenderer::render(QPainter *pPainter, QRect *pDrawRect) {
    mRect->render(pPainter, pDrawRect);
    QRect textRect(mSprite->getX() + mSprite->getOffsX() + 2, mSprite->getY() + mSprite->getOffsY() + 1, mSprite->getW() - 4, mSprite->getH());
    pPainter->setPen(QColor(0,0,0));
    pPainter->setFont(QFont("Arial", 12, QFont::Normal));
    pPainter->drawText(textRect, QString("%1").arg(mSprite->getID()), Qt::AlignLeft | Qt::AlignTop);
    pPainter->setPen(Qt::NoPen);
}
