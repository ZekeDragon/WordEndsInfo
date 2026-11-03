/***********************************************************************************************************************
** The Simple Word Endings Application
** mainwindow.cpp
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
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QAbstractListModel>
#include <QFile>
#include <QTextStream>
#include <QDir>

#include "alphabetselector.hpp"
#include "dictionarylistmodel.hpp"

class MainWindowPrivate
{
    MainWindow *q_ptr;

    Ui::MainWindow ui;
    DictionaryListModel listModel;

public:
    MainWindowPrivate(MainWindow *self) : q_ptr{ self }
    {
        ui.setupUi(self);

        QObject::connect(ui.leftSelector,
                         &AlphabetSelector::letterSelected,
                         &listModel,
                         &DictionaryListModel::filterLeft);
        QObject::connect(ui.leftSelector,
                         &AlphabetSelector::letterDeselected,
                         &listModel,
                         &DictionaryListModel::unfilterLeft);
        QObject::connect(ui.rightSelector,
                         &AlphabetSelector::letterSelected,
                         &listModel,
                         &DictionaryListModel::filterRight);
        QObject::connect(ui.rightSelector,
                         &AlphabetSelector::letterDeselected,
                         &listModel,
                         &DictionaryListModel::unfilterRight);

        ui.listView->setModel(&listModel);
    }

private:
    Q_DECLARE_PUBLIC(MainWindow)
};

MainWindow::MainWindow(QWidget *parent) : QMainWindow{ parent }, d_ptr{ std::make_unique<MainWindowPrivate>(this) }
{
    // No further implementation.
}

MainWindow::~MainWindow() = default;
