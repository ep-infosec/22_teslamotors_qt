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


#include <QtTest/QtTest>

class tst_MyTestCase: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase_data() const;
    void initTestCase() const;

    void a_data() const;
    void a() const;

    void b() const;

    void c_data() const;
    void c() const;
};

void tst_MyTestCase::initTestCase_data() const
{
    QTest::addColumn<int>("f");
    QTest::addColumn<int>("g");

    QTest::newRow("global data tag 1 ") << 1 << 2;
    QTest::newRow("global data tag 2") << 1 << 2;
}

void tst_MyTestCase::initTestCase() const
{
}

void tst_MyTestCase::a_data() const
{
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");

    QTest::newRow("data tag a1 ") << 1 << 2;
    QTest::newRow("data tag a2") << 1 << 2;
}

void tst_MyTestCase::a() const
{
}

void tst_MyTestCase::b() const
{
}

void tst_MyTestCase::c_data() const
{
    QTest::addColumn<int>("x");

    QTest::newRow("data tag c1") << 1;
    QTest::newRow("data tag c2") << 1;
    QTest::newRow("data tag c3") << 1;
}

void tst_MyTestCase::c() const
{
}

QTEST_MAIN(tst_MyTestCase)

#include "tst_printdatatagswithglobaltags.moc"
