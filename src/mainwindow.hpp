/***********************************************************************************************************************
** The Simple Word Endings Application
** mainwindow.hpp
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

#include <QMainWindow>

#include <memory>

class MainWindowPrivate;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::unique_ptr<MainWindowPrivate> const d_ptr;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    /*
public slots:
    void leftLetterToggled(bool newState);
    void rightLetterToggled(bool newState);
    */

private:
    Q_DECLARE_PRIVATE(MainWindow)
};
