/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "testtessellator.h"
#include <private/qtessellator_p.h>

#include "math.h"
#include <QtCore/QDebug>

class TestTessellator : public QTessellator
{
public:
    QVector<XTrapezoid> *traps;
    void addTrap(const Trapezoid &trap);
};

void TestTessellator::addTrap(const Trapezoid &trap)
{
    XTrapezoid xtrap;
    xtrap.top = Q27Dot5ToXFixed(trap.top);
    xtrap.bottom = Q27Dot5ToXFixed(trap.bottom);
    xtrap.left.p1.x = Q27Dot5ToXFixed(trap.topLeft->x);
    xtrap.left.p1.y = Q27Dot5ToXFixed(trap.topLeft->y);
    xtrap.left.p2.x = Q27Dot5ToXFixed(trap.bottomLeft->x);
    xtrap.left.p2.y = Q27Dot5ToXFixed(trap.bottomLeft->y);
    xtrap.right.p1.x = Q27Dot5ToXFixed(trap.topRight->x);
    xtrap.right.p1.y = Q27Dot5ToXFixed(trap.topRight->y);
    xtrap.right.p2.x = Q27Dot5ToXFixed(trap.bottomRight->x);
    xtrap.right.p2.y = Q27Dot5ToXFixed(trap.bottomRight->y);
    traps->append(xtrap);
}


void test_tesselate_polygon(QVector<XTrapezoid> *traps, const QPointF *points, int nPoints,
                         bool winding)
{
    TestTessellator t;
    t.traps = traps;
    t.setWinding(winding);
    t.tessellate(points, nPoints);
}


void test_tessellate_polygon_convex(QVector<XTrapezoid> *traps, const QPointF *points, int nPoints,
                                   bool winding)
{
    TestTessellator t;
    t.traps = traps;
    t.setWinding(winding);
    t.tessellateConvex(points, nPoints);
}


void test_tessellate_polygon_rect(QVector<XTrapezoid> *traps, const QPointF *points, int nPoints,
                                  bool winding)
{
    // 5 points per rect
    if (nPoints % 5 != 0)
        qWarning() << Q_FUNC_INFO << "multiples of 5 points expected";

    TestTessellator t;
    t.traps = traps;
    t.setWinding(winding);
    for (int i = 0; i < nPoints / 5; ++i) {
        QPointF rectA = points[5*i];
        QPointF rectB = points[5*i+1];
        QPointF rectC = points[5*i+2];
        QPointF rectD = points[5*i+3];

        QPointF a = (rectA + rectD) * 0.5;
        QPointF b = (rectB + rectC) * 0.5;

        QPointF delta = rectA - rectD;

        qreal width = sqrt(delta.x() * delta.x() + delta.y() * delta.y());

        t.tessellateRect(a, b, width);
    }
}
