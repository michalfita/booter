#pragma once

#include "BooterLevel.h"
#include "BooterChain.h"
#include <atomic>
#include <array>
#include <cassert>

namespace Booter
{
    void Boot();
    void Shutdown();
    
    class Provider
    {
        Provider() = delete;
        
        using ChainsArray = std::array<Chain, static_cast<size_t>(Booter::Level::NumberOfLevels)>;
        
        static Chain& GetChain(Booter::Level initLevel);
        
        template <class T> friend class Builder;
        friend void Booter::Boot();
        friend void Booter::Shutdown();
    };
} // namespace Booter
