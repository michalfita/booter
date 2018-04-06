#include "BooterChain.h"

#include <cassert>

void Booter::Chain::AddNode(Node * newNode)
{
    assert(m_firstNode.load() != nullptr);
    
    Node* currentNode = m_firstNode.exchange(newNode);
    
    assert(currentNode->m_nextNode.load() == nullptr);
    
    currentNode->m_nextNode = newNode;
}

void Booter::Chain::BuildAllNodes()
{
    assert(m_firstNode.load() != nullptr);
    
    for (Node* currentNode = m_nextNode.load(); currentNode != nullptr; currentNode = currentNode->m_nextNode.load())
    {
       currentNode->BuildNode();
    }
}

void Booter::Chain::KnockAllNodes()
{
	// This currently clean all nodes up... consider if these should be separate steps.
	assert(m_firstNode.load() != nullptr);
	for (Node* currentNode = m_nextNode.exchange(nullptr); currentNode != nullptr; currentNode = currentNode->m_nextNode.exchange(nullptr))
	{
		currentNode->KnockNode();
	}
}
