/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Assistant of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QHELPSEARCHENGINE_H
#define QHELPSEARCHENGINE_H

#include <QtHelp/qhelp_global.h>

#include <QtCore/QMap>
#include <QtCore/QUrl>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Help)

class QHelpEngineCore;
class QHelpSearchQueryWidget;
class QHelpSearchResultWidget;
class QHelpSearchEnginePrivate;

class QHELP_EXPORT QHelpSearchQuery
{
public:
    enum FieldName { DEFAULT = 0, FUZZY, WITHOUT, PHRASE, ALL, ATLEAST };

    QHelpSearchQuery()
        : fieldName(DEFAULT) { wordList.clear(); }
    QHelpSearchQuery(FieldName field, const QStringList &wordList)
        : fieldName(field), wordList(wordList) {}

    FieldName fieldName;
    QStringList wordList;
};

class QHELP_EXPORT QHelpSearchEngine : public QObject
{
    Q_OBJECT

public:
    explicit QHelpSearchEngine(QHelpEngineCore *helpEngine,
        QObject *parent = 0);
    ~QHelpSearchEngine();

    QHelpSearchQueryWidget* queryWidget();
    QHelpSearchResultWidget* resultWidget();

#ifdef QT_DEPRECATED
    QT_DEPRECATED int hitsCount() const;
#endif
    int hitCount() const;

    typedef QPair<QString, QString> SearchHit;
    QList<SearchHit> hits(int start, int end) const;

    QList<QHelpSearchQuery> query() const;

public Q_SLOTS:
    void reindexDocumentation();
    void cancelIndexing();

    void search(const QList<QHelpSearchQuery> &queryList);
    void cancelSearching();

Q_SIGNALS:
    void indexingStarted();
    void indexingFinished();

    void searchingStarted();
    void searchingFinished(int hits);

private Q_SLOTS:
    void indexDocumentation();

private:
    QHelpSearchEnginePrivate *d;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif  // QHELPSEARCHENGINE_H
