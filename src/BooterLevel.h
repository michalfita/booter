#pragma once

#include <type_traits>

namespace Booter
{
    enum class Level
    {
        Init,
        Drivers,
        // Below this level in the context without the Scheduler running.
        Scheduler,
        // Above this level in the context of the task after Scheduler has been started.
        BasicServices,        // Can we start CLI here?
        FileSystem,
        EventManager,
        MessageStore,
        DomainModels,
        Networks,             // Do we need to worry about sequence of WiFi and ZigBee?
        TcpIp,
        Cloud,
        Last,                 // Don't use this one! Dummy, for easier manipulation.
        NumberOfLevels = Last // Don't you dare to change that or move
    };
    
    inline Level operator++(Level& level) { return level = static_cast<Level>(std::underlying_type<Level>::type(level) + 1); }
    inline Level operator*(Level level) { return level; }
    inline Level begin(const Level& /*level*/) { return Level::Init; }
    inline Level end(const Level& /*level*/) { return static_cast<Level>(std::underlying_type<Level>::type(Level::Last)); }
}
