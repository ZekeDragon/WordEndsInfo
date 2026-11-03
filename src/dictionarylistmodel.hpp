/***********************************************************************************************************************
** The Simple Word Endings Application
** dictionarylistmodel.hpp
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
#pragma once

#include <QAbstractListModel>

#include <memory>

class DictionaryListModelPrivate;

class DictionaryListModel : public QAbstractListModel
{
    Q_OBJECT

    std::unique_ptr<DictionaryListModelPrivate> const d_ptr;

public:
    explicit DictionaryListModel(QObject *parent = nullptr);
    explicit DictionaryListModel(QStringList &&dictionary, QObject *parent = nullptr);
    ~DictionaryListModel() override;

    int rowCount(QModelIndex const &parent = QModelIndex()) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

public slots:
    void filterLeft(QString letter);
    void filterRight(QString letter);
    void unfilterLeft();
    void unfilterRight();

private:
    Q_DECLARE_PRIVATE(DictionaryListModel)
};
