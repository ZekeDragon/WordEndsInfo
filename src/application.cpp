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
#include "application.hpp"

#include <QApplication>
#include <QTranslator>

#include "base.hpp"
#include "mainwindow.hpp"

class ApplicationPrivate
{
    Application *q_ptr;

    QApplication app;
    QTranslator translator;
    MainWindow win;

public:
    ApplicationPrivate(int &argc, char **argv, Application *self) : q_ptr{ self }, app{ argc, argv }
    {
        QStringList const uiLanguages = QLocale::system().uiLanguages();
        for (QString const &locale : uiLanguages)
        {
            QString const baseName = "WordEndsInfo_" + QLocale(locale).name();
            if (translator.load(":/i18n/" + baseName))
            {
                app.installTranslator(&translator);
                break;
            }
        }
    }

    int run()
    {
        win.show();
        return QApplication::exec();
    }

private:
    Q_DECLARE_PUBLIC(Application)
};

Application::Application(int &argc, char **argv, QObject *parent) :
    QObject{ parent },
    d_ptr{ std::make_unique<ApplicationPrivate>(argc, argv, this) }
{
    // No further implementation.
}

Application::~Application() = default;

int Application::run()
{
    W_D();

    return d.run();
}

void Application::erroneousTerminate(int code)
{
    if (code == 0)
    {
        quit();
    }
    else
    {
        exit(code);
    }
}

void Application::exit(int code)
{
    W_D();

    d.app.exit(code);
}

void Application::quit()
{
    W_D();

    d.app.quit();
}
