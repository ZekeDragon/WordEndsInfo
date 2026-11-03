/***********************************************************************************************************************
** The Simple Word Endings Application
** main.cpp
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

#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        Application a(argc, argv);
        return a.run();
    }
    catch ([[maybe_unused]] std::bad_alloc const &ba)
    {
        std::cerr << "WordEndsInfo ran out of memory, and has no choice but to close.\n";
        return EXIT_FAILURE;
    }
    catch (std::exception const &ex)
    {
        std::cerr << "WordEndsInfo must close due to an exception being thrown: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "WordEndsInfo threw an unknown exception and must close.\n";
        return EXIT_FAILURE;
    }
}
