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
void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{
    _chatBot = chatbot;
    std::cout << "MOVED CHATBOT (PTR):" << _chatBot << "\n";
    _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(_chatBot);
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