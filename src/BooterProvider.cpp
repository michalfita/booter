#include "BooterProvider.h"
#include "BooterChain.h"

Booter::Chain& Booter::Provider::GetChain(Booter::Level initLevel)
{
    static ChainsArray booterChains;
    return booterChains.at(static_cast<size_t>(initLevel));
}
