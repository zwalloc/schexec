#pragma once

#include <ulib/string.h>

namespace schexec
{
    void launch(ulib::string_view commandLine);
    void launch(ulib::list<ulib::string> args);
}