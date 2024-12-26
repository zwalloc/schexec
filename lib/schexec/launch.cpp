#include "launch.h"

// #include <ulib/string.h>
#include <ulib/process.h>
#include <ulib/format.h>

namespace schexec
{
    void launch(ulib::string_view commandLine)
    {
        ulib::u8string taskName = ulib::format(u8"SCHEXEC_TASK_{}_{}", uint(rand()), uint(rand()));

        auto createTaskCommand =
            ulib::format(u8"schtasks /create /tn {} /TR \"{}\" /sc MONTHLY", taskName, commandLine);
        auto deleteTaskCommand = ulib::format(u8"schtasks /delete /tn \"{}\" /f", taskName);

        auto exitCode = ulib::process{createTaskCommand}.wait();
        if (exitCode != 0)
            throw ulib::RuntimeError{ulib::format("Command: {} Failed with code: {}", createTaskCommand, exitCode)};

        auto delete_task = [&]() {
            ulib::process{deleteTaskCommand}.wait();
        };

        try
        {
            auto runTaskCommand = ulib::format(u8"schtasks /run /tn \"{}\"", taskName);
            exitCode = ulib::process{runTaskCommand}.wait();

            if (exitCode != 0)
                throw ulib::RuntimeError{ulib::format("Command: {} Failed with code: {}", runTaskCommand, exitCode)};
        }
        catch (const std::exception &ex)
        {
            delete_task();
            throw;
        }

        delete_task();
    }
} // namespace schexec