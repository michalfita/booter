#pragma once

#include "BooterProvider.h"
#include "BooterBootable.h"
#include "BooterLevel.h"

namespace Booter
{
    void Boot()
    {
        for (const auto& level : Booter::Level())
        {
            auto& chain = ::Booter::Provider::GetChain(level);
            chain.BuildAllNodes();
        }
    }

    void Shutdown()
    {
        for (const auto& level : Booter::Level())
        {
            auto& chain = ::Booter::Provider::GetChain(level);
            chain.KnockAllNodes();
        }
    }
} // namespace Booter
