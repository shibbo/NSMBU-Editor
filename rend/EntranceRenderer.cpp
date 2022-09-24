#include "EntranceRenderer.h"

EntranceRenderer::EntranceRenderer(const Entrance *pEntrance){
    mEntrance = pEntrance;
    mRect = new RoundedRectRenderer(mEntrance, "", QColor(255, 0, 0, 150));
}

void EntranceRenderer::render(QPainter *pPainter, QRect *pDrawRect) {
    mRect->render(pPainter, pDrawRect);
    QRect textRect(mEntrance->getX() + mEntrance->getOffsX() + 2, mEntrance->getY() + mEntrance->getOffsY() + 1, mEntrance->getW() - 4, mEntrance->getH());
    pPainter->setPen(QColor(0,0,0));
    pPainter->setFont(QFont("Arial", 12, QFont::Normal));
    pPainter->drawText(textRect, QString("%1").arg(mEntrance->getID()), Qt::AlignLeft | Qt::AlignTop);
    pPainter->setPen(Qt::NoPen);
}
