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
#include "alphabetselector.hpp"

#include <QPushButton>
#include <QButtonGroup>

#include "base.hpp"

#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>

class AlphabetSelectorPrivate
{
    AlphabetSelector *const q_ptr;

    QList<QPushButton *> letterButtons;
    QButtonGroup lettersGroup;
    QGridLayout *const gridLayout;

public:
    AlphabetSelectorPrivate(AlphabetSelector *self) : q_ptr{ self }, gridLayout{ new QGridLayout(self) }
    {
        lettersGroup.setExclusive(false);
        auto buttonChanged = [&](QAbstractButton *button, bool checked) {
            if (button)
            {
                W_Q();

                QString emittedText = button->text().remove(QChar{ '&' });

                if (checked)
                {
                    R::for_each(letterButtons, [&](QAbstractButton *letterButton) {
                        if (letterButton->isChecked() and button != letterButton)
                        {
                            letterButton->setChecked(false);
                        }
                    });

                    emit q.letterSelected(emittedText);
                }
                else
                {
                    emit q.letterDeselected(emittedText);
                }
            }
            else
            {
                // Throw exception.
            }
        };

        QObject::connect(&lettersGroup, &QButtonGroup::buttonToggled, self, buttonChanged);
    }

    void setAlphabet(QStringList const &alphabet)
    {
        R::for_each(letterButtons, [&](QPushButton *button) {
            lettersGroup.removeButton(button);
            gridLayout->removeWidget(button);
            button->hide();
            button->deleteLater();
        });

        letterButtons.clear();
        letterButtons.reserve(alphabet.size());
        auto halfPoint = alphabet.size() - (alphabet.size() / 2);

        R::transform(V::iota(0z, alphabet.size()), std::back_inserter(letterButtons), [&](qsizetype i) {
            QPushButton *newButton = new QPushButton(alphabet[i]);
            newButton->setCheckable(true);
            lettersGroup.addButton(newButton);
            gridLayout->addWidget(newButton, i % halfPoint, i < halfPoint ? 0 : 1);
            return newButton;
        });
    }

private:
    Q_DECLARE_PUBLIC(AlphabetSelector)
};

QStringList const &englishAlphabet()
{
    static QStringList english{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                                "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

    return english;
}

AlphabetSelector::AlphabetSelector(QWidget *parent) : AlphabetSelector{ englishAlphabet(), parent }
{
    // No further implementation.
}

AlphabetSelector::AlphabetSelector(QStringList const &alphabet, QWidget *parent) :
    QWidget{ parent },
    d_ptr{ std::make_unique<AlphabetSelectorPrivate>(this) }
{
    W_D();

    d.setAlphabet(alphabet);
}

void AlphabetSelector::setAlphabet(QStringList const &alphabet)
{
    W_D();

    d.setAlphabet(alphabet);
}

AlphabetSelector::~AlphabetSelector() = default;
