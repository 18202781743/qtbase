// Copyright (C) 2024 UnionTech Software Technology Co., Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qdeepintheme_p.h"

#include <QPalette>
#include <QGuiApplication>

#include <private/qguiapplication_p.h>
#include <qpa/qplatformintegration.h>

#if QT_CONFIG(xcb)
#include <QtGui/private/qtx11extras_p.h>
#include <xcb/xcb.h>
#endif

QT_BEGIN_NAMESPACE

const char *QDeepinTheme::name = "deepin";

// Default active color for Deepin desktop environment (blue)
static const QColor defaultActiveColor(0, 129, 255); // #0081FF

QDeepinThemePrivate::QDeepinThemePrivate()
    : QGenericUnixThemePrivate()
    , q_ptr(nullptr)
{
}

QDeepinThemePrivate::~QDeepinThemePrivate()
{
}

QColor QDeepinThemePrivate::activeColor() const
{
    return m_activeColor;
}

void QDeepinThemePrivate::setActiveColor(const QColor &color)
{
    m_activeColor = color;
}

QDeepinTheme::QDeepinTheme()
    : QGenericUnixTheme(new QDeepinThemePrivate())
{
    d_ptr = static_cast<QDeepinThemePrivate*>(QGenericUnixTheme::d_ptr.data());
    d_ptr->q_ptr = this;

    // Try to read active color from XSettings
#if QT_CONFIG(xcb)
    if (QX11Info::isPlatformX11()) {
        // TODO: Read Qt/ActiveColor from XSettings
        // For now, use default color
        d_ptr->setActiveColor(defaultActiveColor);
    } else
#endif
    {
        d_ptr->setActiveColor(defaultActiveColor);
    }
}

QDeepinTheme::~QDeepinTheme()
{
}

bool QDeepinTheme::isDeepinEnvironment()
{
    if (!qGuiApp)
        return false;

    QByteArray desktopEnv = qGuiApp->property("desktopEnvironment").toByteArray();
    return desktopEnv.contains("deepin") || desktopEnv.contains("DDE");
}

QPlatformTheme *QDeepinTheme::createDeepinTheme()
{
    return new QDeepinTheme;
}

const QPalette *QDeepinTheme::palette(Palette type) const
{
    if (type != SystemPalette)
        return QGenericUnixTheme::palette(type);

    QColor activeColor = d_ptr->activeColor();

    // Use default active color if not set
    if (!activeColor.isValid()) {
        activeColor = defaultActiveColor;
    }

    if (!m_paletteInitialized) {
        m_palette = *QGenericUnixTheme::palette(type);
        m_paletteInitialized = true;
    }

    m_palette.setColor(QPalette::Normal, QPalette::Highlight, activeColor);

    int h, s, v;
    activeColor.getHsv(&h, &s, &v);
    QColor highlightedText = (v > 128) ? Qt::black : Qt::white;
    m_palette.setColor(QPalette::Normal, QPalette::HighlightedText, highlightedText);

    return &m_palette;
}

QT_END_NAMESPACE
