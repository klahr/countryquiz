/*
 * Copyright (c) 2023-2024 Tomi Leppänen
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <QCoreApplication>
#include <QMutex>
#include <QObject>
#include <QRectF>
#include <QSvgRenderer>
#include <QThread>
#include <QVector>

class MapRenderer : public QObject
{
    Q_OBJECT

public:
    static MapRenderer *get(const QString &filePath);
    static void setup(QCoreApplication *app);

public slots:
    void renderMap(const QSize &maxSize, const QString &code);

signals:
    void tileCountReady(const QSize &size, const QSize &tiles, const QString &code);
    void tileReady(const QImage &image, const QRectF &tile, const QString &code);
    void overlayReady(const QImage &image, const QRectF &tile, const QString &code);

private:
    explicit MapRenderer(const QString &filePath, QObject *parent = nullptr);

    static QMutex s_rendererMutex;
    static QVector<MapRenderer *> s_renderers;
    static QThread *s_rendererThread;

    QString m_mapFilePath;
    QSvgRenderer m_renderer;
    QString m_tilePathTemplate;
    QSize m_tileSize;
    QSize m_dimensions;
};

#endif // MAPRENDERER_H
