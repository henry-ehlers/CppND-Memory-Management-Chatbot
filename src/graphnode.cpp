#include "graphedge.h"
#include "graphnode.h"
#include <iostream>
#include <memory>
GraphNode::GraphNode(int id)
{
 	std::cout << "GRAPH NODE CONSTRUCTOR OF: " << id << "\n";
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
    std::cout << "GRAPH NODE DESTRUCTOR\n";
    for (std::unique_ptr<GraphEdge> &edge : _childEdges) {
      // CALLS DESTRUCTOR ON OBJECT BEING MANAGED + RELEASES POINTER
      std::cout << "graph edge (1): " << edge.get() << "\n";
      edge.reset(); 
      std::cout << "graph edge (2): " << edge.get() << "\n";
    }
  
  	if (_chatBot != nullptr) {
      _chatBot.reset();
    }
    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

// NON-EXCLUSIVE OWNERSHIP
void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

// EXCLUSIVE OWNERSHIP
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
  	// WE NEED TO ACTUALLY REMOVE EDGE FROM THIS SCOPE IF WE WANT TO ADD IT TO THE VECTOR
  	// CANNOT JUST USED A (TEMPORARY) COPY OPERATION, SO WE MUST USE std::move INSTEAD
    _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(std::unique_ptr<ChatBot> chatbot)
{
    _chatBot = std::move(chatbot);
    std::cout << "MOVED CHATBOT (UNIQUE_PTR):" << _chatBot.get() << "\n";
    _chatBot.get()->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(std::move(_chatBot));
    _chatBot = nullptr; // invalidate pointer at source
    if(_chatBot) {std::cout << "CHAT BOT NOT PROPERLY REMOVED\n";};
}
////
//// EOF STUDENT CODE

GraphEdge* GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////
  
	// WE DO NOT RETURN THE SMART POINTER (AND HENCE DO NOT TRANSFER OWNERSHIP)
  	// INSTEAD WE ONLY TRANSFER THE POINTER ADDRESS ITSELF
    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}