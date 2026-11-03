/***********************************************************************************************************************
** The Simple Word Endings Application
** alphabetselector.hpp
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

#include <QWidget>

#include <memory>

class AlphabetSelectorPrivate;

QStringList const &englishAlphabet();

class AlphabetSelector : public QWidget
{
    Q_OBJECT

    std::unique_ptr<AlphabetSelectorPrivate> const d_ptr;

public:
    explicit AlphabetSelector(QWidget *parent = nullptr);
    explicit AlphabetSelector(QStringList const &alphabet, QWidget *parent = nullptr);
    ~AlphabetSelector() override;

    void setAlphabet(QStringList const &alphabet);

signals:
    void letterSelected(QString letter);
    void letterDeselected(QString letter);

private:
    Q_DECLARE_PRIVATE(AlphabetSelector)
};
