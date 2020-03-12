#pragma once

#include "BooterChain.h"
#include "BooterLevel.h"
#include "BooterProvider.h"

#include <cassert>

namespace Booter
{
    template <class T>
    class Bootable
    {
      public:
        using InstancePtr = std::atomic<T*>;
      
      protected:
        static InstancePtr& GetModifiableInstancePointer()
        {
            static InstancePtr instanceAtomicPointer;
            return instanceAtomicPointer;
        }
      
      private:
        template <class R> friend class Builder;
    };
    
    
    template <class T>
    class Builder : protected Node
    {
      public:
        Builder<T>(Level level)
        {
            ::Booter::Provider::GetChain(level).AddNode(this);
        }
        
        static T& GetInstance() { 
            assert(T::GetModifiableInstancePointer().load() != nullptr);
            return *T::GetModifiableInstancePointer().load();
        };
    
      protected:
        void BuildNode() override
        {
            assert(T::GetModifiableInstancePointer().load() == nullptr);
            T::GetModifiableInstancePointer().store(T::BuildInstance());
        }
        
        void KnockNode() override
        {
            assert(T::GetModifiableInstancePointer().load() != nullptr);
            delete T::GetModifiableInstancePointer().exchange(nullptr);
        }
    };
} // namespace Booter

#define BOOTER_CONSTRUCT_VARIABLE_NAME(CLASS) booterBuilderOf ## CLASS
#define BOOTER_BUILDER(LEVEL, CLASS) \
    static Booter::Builder<CLASS> BOOTER_CONSTRUCT_VARIABLE_NAME(CLASS)(LEVEL);
