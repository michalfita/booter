#pragma once

#include <array>
#include <atomic>
#include <cstdint>
#include "BooterBootable.h"

namespace Booter
{
    template <typename P>
    class StaticBootableStorage;

    template <typename P>
    class StaticBootable : public Bootable<P>
    {
    public:
        using InstancePtr = std::atomic<P*>;

        // sizeof(P) cannot be calculated from here due to P inheriting from me: static std::array<uint8_t, sizeof(P)> m_underlyingMemory;
        
    public:
        template<typename ... ArgsT>
        static void Build(ArgsT ... arguments)
        {
            P::GetModifiableInstancePointer() = new (StaticBootableStorage<P>::m_underlyingMemory.data()) P(arguments ...);
        }

        static void Knock()
        {
            assert(P::GetModifiableInstancePointer().load() != nullptr);
            P::GetModifiableInstancePointer().exchange(nullptr).~P(); // Underlying memory is static
        }
        
        static P& GetInstance()
        {
            assert(P::GetModifiableInstancePointer().load() != nullptr);
            return *(P::GetModifiableInstancePointer().load());
        }

    private:
        template <class T> friend class Builder;
    };

    template <typename P>
    class StaticBootableStorage {
        static std::array<uint8_t, sizeof(P)> m_underlyingMemory;
        template <typename Q> friend class StaticBootable;
    };

    template <typename P>
    std::array<uint8_t, sizeof(P)> StaticBootableStorage<P>::m_underlyingMemory;
}