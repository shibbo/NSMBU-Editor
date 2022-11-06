#include "LevelView.h"
#include "rend/renders.h"

#include <QApplication>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QRectF>
#include <QPaintEvent>
#include <QPainterPath>
#include <QClipboard>
#include <QMessageBox>

LevelView::LevelView(QWidget *parent, Level *pLevel) : QWidget(parent) {
    mLevel = pLevel;
    mZoom = 0.9f;
    setMouseTracking(true);
}

void LevelView::screenshot(QRect rect) {
    QPixmap pix(rect.size());
    QPainter painter(&pix);
    painter.translate(-rect.x(), -rect.y());
    paint(painter, rect, 1.0f, false);
    QApplication::clipboard()->setPixmap(pix);
}

void LevelView::paintEvent(QPaintEvent *evt) {
    QPainter painter(this);
    paint(painter, evt->rect().adjusted(0, 0, 64, 64), mZoom, true);
}

void LevelView::paint(QPainter& painter, QRect rect, float zoomLvl, bool selections) {
    painter.scale(zoomLvl, zoomLvl);
    mDrawRect = QRect(rect.x() / zoomLvl, rect.y() / zoomLvl, rect.width() / zoomLvl, rect.height() / zoomLvl);
    painter.fillRect(mDrawRect, mBackgroundColor);

    for (quint32 i = 0; i < 3; i++) {
        QList<BgDatObject *> objs = mLevel->mObjects[i];

        if (objs.count() != 0) {
            for (BgDatObject* obj : objs) {
                QRect location_rect(obj->mXPosition * 64, obj->mYPosition * 64, obj->mWidth * 64, obj->mHeight * 64);
                painter.fillRect(location_rect, QBrush(QColor(245, 142, 39, 50)));
                painter.setPen(QColor(0, 0,0));
                painter.drawRect(location_rect);
            }
        }
    }

    for (Location* loc : mLevel->mLocations) {
        QRect location_rect(loc->getX(), loc->getY(), loc->getW(), loc->getH());
        painter.fillRect(location_rect, QBrush(QColor(85, 80, 185, 50)));
        painter.setPen(QColor(0, 0,0));
        painter.drawRect(location_rect);
    }

    for (Entrance* entr : mLevel->mEntrances) {
        EntranceRenderer rend(entr);
        rend.render(&painter, &rect);
    }

    for (Sprite* spr : mLevel->mSprites) {
        SpriteRenderer rend(spr);
        rend.render(&painter, &rect);
    }

    for (Zone* zone : mLevel->mZones) {
        QRect zone_rect(zone->getX(), zone->getY(), zone->getW(), zone->getH());
        painter.setPen(QColor(255, 255, 255));
        painter.drawRect(zone_rect);
        QString txt = QString("Zone %1").arg(zone->mID);
        painter.setFont(QFont("Arial", 12, QFont::Normal));
        int adjustX = 3;
        int adjustY = 3;
        if (zone_rect.x() < rect.x()) {
            adjustX += rect.x() - zone_rect.x();
        }

        if (zone_rect.y() < rect.y()) {
            adjustY += rect.y() - zone_rect.y();
        }

        painter.drawText(zone_rect.adjusted(adjustX, adjustY, 100, 20), txt);
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    int startx = mDrawRect.x() - mDrawRect.x() % 64;
    int endx = startx + mDrawRect.width() + 64;
    int starty = mDrawRect.y() - mDrawRect.y() % 64;
    int endy = starty + mDrawRect.height() + 64;
    int x = startx - 64;

    while (x <= endx)
    {
        x += 64;
        if (x % 512 == 0)
        {
            painter.setPen(QPen(QColor(255,255,255,75), 2, Qt::DashLine));
            painter.drawLine(x, starty, x, endy);
        }
        else if (x % 256 == 0)
        {
            if (mZoom < 0.3) continue;
            painter.setPen(QPen(QColor(255,255,255,75), 1, Qt::DashLine));
            painter.drawLine(x, starty, x, endy);
        }
        else
        {
            if (mZoom < 0.5) continue;
            painter.setPen(QPen(QColor(255,255,255,75), 1, Qt::DotLine));
            painter.drawLine(x, starty, x, endy);
        }
    }

    int y = starty - 64;
    while (y <= endy)
    {
        y += 64;
        if (y % 512 == 0)
        {
            painter.setPen(QPen(QColor(255,255,255,75), 2, Qt::DashLine));
            painter.drawLine(startx, y, endx, y);
        }
        else if (y % 256 == 0)
        {
            if (mZoom < 0.3) continue;
            painter.setPen(QPen(QColor(255,255,255,75), 1, Qt::DashLine));
            painter.drawLine(startx, y, endx, y);
        }
        else
        {
            if (mZoom < 0.5) continue;
            painter.setPen(QPen(QColor(255,255,255,75), 1, Qt::DotLine));
            painter.drawLine(startx, y, endx, y);
        }
    }

    painter.setRenderHint(QPainter::Antialiasing);
}
