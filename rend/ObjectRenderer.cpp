#include "ObjectRenderer.h"
#include "qpainterpath.h"

RoundedRectRenderer::RoundedRectRenderer(const Object *pObj, QString text, QColor color, QTextOption align) {
    mObj = pObj;
    mText = text;
    mColor = color;
    mAlign = align;
}

void RoundedRectRenderer::render(QPainter *pPainter, QRect *pRect) {
    QRect rect(mObj->getX() + mObj->getOffsX(), mObj->getY() + mObj->getOffsY(), mObj->getW(), mObj->getH());
    pPainter->setPen(QColor(0, 0, 0));
    QPainterPath path;
    path.addRoundedRect(rect, 2.0f, 2.0f);
    pPainter->fillPath(path, mColor);
    pPainter->drawPath(path);
    pPainter->setFont(QFont("Arial", 12, QFont::Normal));
    pPainter->drawText(rect, mText, mAlign);
    pPainter->setPen(Qt::NoPen);
}
