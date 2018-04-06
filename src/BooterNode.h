#pragma once

#include <atomic>

namespace Booter
{
    class Chain;
    
    class Node
    {
      public:
        virtual ~Node();
      protected:
        Node();
        virtual void BuildNode() = 0;
        virtual void KnockNode() = 0;
        std::atomic<Node*> m_nextNode;
        
        friend class Booter::Chain;
    };

} // namespace Booter
