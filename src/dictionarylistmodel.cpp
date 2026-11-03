/***********************************************************************************************************************
** The Simple Word Endings Application
** application.cpp
** Copyright © Quinn David Kirwan
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
** the License. You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
** an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
** specific language governing permissions and limitations under the License.
***********************************************************************************************************************/
#include "dictionarylistmodel.hpp"

#include <QFile>
#include <QTextStream>

#include "base.hpp"

using WordEndIndexList = QList<qsizetype>;

QStringList englishDictionary()
{
    QStringList words;
    QFile dictFile{ ":/com/kirhut/wordendsinfo/english.txt" };
    if (not dictFile.open(QFile::ReadOnly))
    {
        throw std::runtime_error(dictFile.errorString().toStdString());
    }

    QTextStream dict{ &dictFile };
    for (QString word = dict.readLine(); not word.isEmpty(); word = dict.readLine())
    {
        words << word;
    }

    return words;
}

class DictionaryListModelPrivate
{
    DictionaryListModel *const q_ptr;

    QStringList dict;
    QList<WordEndIndexList> endLists{ 26 };
    qsizetype beginFilterStart{ 0 }, beginFilterEnd{ dict.size() };
    WordEndIndexList *endFilter{ nullptr };

    QString beginFilterString, endFilterString;

    qsizetype rows;

public:
    DictionaryListModelPrivate(DictionaryListModel *self, QStringList &&dictionary) :
        q_ptr{ self },
        dict{ std::move(dictionary) },
        rows{ dict.size() }
    {
        R::for_each(V::iota(0z, dict.size()), [&](qsizetype i) { endLists[dict[i].back().toLatin1() - 'a'] << i; });
    }

    int rowCount(QModelIndex const &parent = {}) const
    {
        if (parent.isValid())
        {
            return 0;
        }

        return rows;
    }

    QVariant data(QModelIndex const &index, int role) const
    {
        if (index.isValid() and index.row() < rows and index.row() >= 0 and role == Qt::DisplayRole)
        {
            if (endFilter)
            {
                return dict[*(R::lower_bound(*endFilter, beginFilterStart) + index.row())];
            }
            else
            {
                return dict[beginFilterStart + index.row()];
            }
        }

        return {};
    }

    void filterLeft(QString letter)
    {
        W_Q();

        letter = letter.toLower();
        if (letter == beginFilterString)
        {
            return;
        }

        q.beginResetModel();
        beginFilterString = letter;

        if (letter == "a")
        {
            beginFilterStart = 0;
        }
        else
        {
            beginFilterStart = R::distance(R::begin(dict), R::lower_bound(dict, letter));
        }

        if (letter == "z")
        {
            beginFilterEnd = dict.size();
        }
        else
        {
            beginFilterEnd = R::distance(R::begin(dict), R::lower_bound(dict, nextLetter(letter)));
        }

        calculateSize();
        q.endResetModel();
    }

    void filterRight(QString letter)
    {
        W_Q();

        letter = letter.toLower();
        if (letter == endFilterString)
        {
            return;
        }

        q.beginResetModel();
        endFilterString = letter;
        endFilter       = &endLists[letter.front().toLatin1() - 'a'];
        calculateSize();
        q.endResetModel();
    }

    void unfilterLeft()
    {
        W_Q();

        if (beginFilterString.isEmpty())
        {
            return;
        }

        q.beginResetModel();
        beginFilterString.clear();
        beginFilterStart = 0;
        beginFilterEnd   = dict.size();
        calculateSize();
        q.endResetModel();
    }

    void unfilterRight()
    {
        W_Q();

        if (endFilterString.isEmpty())
        {
            return;
        }

        q.beginResetModel();
        endFilterString.clear();
        endFilter = nullptr;
        calculateSize();
        q.endResetModel();
    }

private:
    QString nextLetter(QString const &letter) const
    {
        return { QChar::fromLatin1(letter.front().toLatin1() + 1) };
    }

    void calculateSize()
    {
        if (endFilter)
        {
            rows = R::lower_bound(*endFilter, beginFilterEnd) - R::lower_bound(*endFilter, beginFilterStart);
        }
        else
        {
            rows = beginFilterEnd - beginFilterStart;
        }
    }

    Q_DECLARE_PUBLIC(DictionaryListModel)
};

DictionaryListModel::DictionaryListModel(QObject *parent) : DictionaryListModel{ englishDictionary(), parent }
{
    // No further implementation.
}

DictionaryListModel::DictionaryListModel(QStringList &&dictionary, QObject *parent) :
    QAbstractListModel{ parent },
    d_ptr{ std::make_unique<DictionaryListModelPrivate>(this, std::move(dictionary)) }
{
    // No further implementation.
}

DictionaryListModel::~DictionaryListModel() = default;

int DictionaryListModel::rowCount(QModelIndex const &parent) const
{
    W_D();

    return d.rowCount(parent);
}

QVariant DictionaryListModel::data(QModelIndex const &index, int role) const
{
    W_D();

    return d.data(index, role);
}

void DictionaryListModel::filterLeft(QString letter)
{
    W_D();

    d.filterLeft(std::move(letter));
}

void DictionaryListModel::filterRight(QString letter)
{
    W_D();

    d.filterRight(std::move(letter));
}

void DictionaryListModel::unfilterLeft()
{
    W_D();

    d.unfilterLeft();
}

void DictionaryListModel::unfilterRight()
{
    W_D();

    d.unfilterRight();
}
