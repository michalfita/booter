#include "Booter.h"
#include "gtest/gtest.h"

class BootingVictimOne : public Booter::Bootable<BootingVictimOne>
{
    static BootingVictimOne* BuildInstance()
    {
        return new BootingVictimOne();
    }

    template<class T> friend class Booter::Builder;
};

BOOTER_BUILDER(Booter::Level::Init, BootingVictimOne);


class BootingVictimTwo : public Booter::Bootable<BootingVictimTwo>
{
    static BootingVictimTwo* BuildInstance()
    {
        return new BootingVictimTwo();
    }

    template<class T> friend class Booter::Builder;
};

BOOTER_BUILDER(Booter::Level::Init, BootingVictimTwo);

class BootingVictimThree : public Booter::StaticBootable<BootingVictimThree> 
{
  public:
    BootingVictimThree(BootingVictimOne& dependency) 
       : m_dependency(dependency)
    {}

  private:
    static BootingVictimThree* BuildInstance()
    {
        BootingVictimThree::Build(Booter::Builder<BootingVictimOne>::GetInstance());
        return &BootingVictimThree::GetInstance();
    }

    template<class T> friend class Booter::Builder;

    BootingVictimOne m_dependency;
};

BOOTER_BUILDER(Booter::Level::Init, BootingVictimThree);

namespace Tests
{
    class TestBooterSystem : public ::testing::Test
    {
      public:
        TestBooterSystem() {}
    };

    TEST_F(TestBooterSystem, execution_of_whole_booting_chain)
    {
        Booter::Boot();

        Booter::Builder<BootingVictimOne>::GetInstance();

        Booter::Shutdown();
    }

    TEST_F(TestBooterSystem, assertion_if_getting_instance_of_not_booted)
    {
        // Assertion failed: T::GetModifiableInstancePointer().load() != nullptr, file c:\projects\booter\src\BooterBootable.h, line 38
        EXPECT_DEATH(Booter::Builder<BootingVictimOne>::GetInstance(), "Assertion failed.*load\\(\\) != nullptr.*");
    }
} // namespace Tests
