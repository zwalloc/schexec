#include <iostream>

#include <schexec/launch.h>
#include <ulib/format.h>

#include <windows.h>

int main(int argc, const char *argv[])
{
    try
    {
        if (argc > 1)
        {
            ulib::string command;

            for (size_t i = 1; i < size_t(argc); i++)
            {
                command += "\"";
                command += argv[i];
                command += "\"";
                command += " ";
            }

            schexec::launch(command);
        }
        else
        {
            fmt::print("No args\n");
        }
    }
    catch (const std::exception &ex)
    {
        fmt::print("Exception occurred: {}\n", ex.what());
    }

    return 0;
}
