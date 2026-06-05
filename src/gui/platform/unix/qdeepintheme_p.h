// Copyright (C) 2024 UnionTech Software Technology Co., Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QDEEPINTHEME_P_H
#define QDEEPINTHEME_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <private/qgenericunixtheme_p.h>

#include <QColor>
#include <QPalette>

QT_BEGIN_NAMESPACE

class QDeepinTheme;

class QDeepinThemePrivate : public QGenericUnixThemePrivate
{
public:
    QDeepinThemePrivate();
    ~QDeepinThemePrivate() override;

    QColor activeColor() const;
    void setActiveColor(const QColor &color);

    QDeepinTheme *q_ptr;

private:
    QColor m_activeColor;
};

class QDeepinTheme : public QGenericUnixTheme
{
public:
    QDeepinTheme();
    ~QDeepinTheme() override;

    static const char *name;

    const QPalette *palette(Palette type = SystemPalette) const override;

    static bool isDeepinEnvironment();
    static QPlatformTheme *createDeepinTheme();

private:
    QDeepinThemePrivate *d_ptr;
    mutable QPalette m_palette;
    mutable bool m_paletteInitialized = false;
};

QT_END_NAMESPACE

#endif // QDEEPINTHEME_P_H
