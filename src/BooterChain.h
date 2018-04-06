#pragma once

#include "BooterNode.h"
#include <cassert>

namespace Booter
{
    void Boot();
    void Shutdown();
    
    class Chain : public Node
    {
      public:
        Chain()
            : m_firstNode(this)
        { }
        void AddNode(Node* newNode);
    
      protected:
        void BuildAllNodes();
        void KnockAllNodes();
        
        friend void Boot();
        friend void Shutdown();
    
      private:
        void BuildNode() {}
        void KnockNode() {}
        std::atomic<Node*> m_firstNode;
    };
}
