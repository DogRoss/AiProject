#include "PathFinding.h"

//Use this function to sort nodes using their gScore value
bool NodeSort(const Node* i, const Node* j)
{
	return (i->gCost< j->gCost);
}

PathFinding::PathFinding(Vector2 pStartPos, Vector2 pTargetPos, GridMap* pGrid)
{
	grid = pGrid;
	startPos = pStartPos;
	targetPos = pTargetPos;
}

void PathFinding::OnUpdate()
{
	Node* startNode;
	Node* endNode;
	startNode = &grid->NodeFromWorldPosition(startPos);
	endNode = &grid->NodeFromWorldPosition(targetPos);
	FindPath(startNode, endNode);
}

void PathFinding::FindPath(Node* startNode, Node* endNode)
{
	//Validate the input
	if (startNode == nullptr || endNode == nullptr)
	{
		return;
	}

	if (startNode == endNode)
	{
		return GetFinalPath(startNode, endNode);
	}


	//Initialize the starting node
	startNode->gCost = 0;
	startNode->parent = nullptr;

	//Create our temporary lists for storing nodes
	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	//Add the starting node to openList
	openList.push_back(startNode);

	while (!openList.empty())
	{
		//Sort openList based on gScore using the function created above
		std::sort(openList.begin(), openList.end(), NodeSort);

		//Set the current node to the first node in the openList
		Node* currentNode = new Node();
		currentNode = openList.front();
		//Remove currentNode from openList
		openList.erase(openList.begin());
		//Add currentNode to closedList
		closedList.push_back(currentNode);

		//If the destination node was added to the closed list,
		//the shortest path has been found
		if (currentNode == endNode)
		{
			break;
		}

		//For each Edge e in currentNode's connections
		for (Node e : grid->GetNeighboringNodes(currentNode))
		{
			//If the target node is in the closedList, ignore it
			if (std::find(closedList.begin(), closedList.end(), e) != closedList.end()) {
				continue;
			}
			//If the target node is not in the openList, update it
			if (std::find(openList.begin(), openList.end(), e) == openList.end()) {
				//Calculate the target node's G Score
				e.gCost = currentNode->gCost + e.gCost;
				//Set the target node's previous to currentNode
				e.parent = currentNode;
				//Find the earliest point we should insert the node
				//to the list to keep it sorted
				auto insertionPos = openList.end();
				for (auto i = openList.begin(); i != openList.end(); i++) {
					if (e.gCost < (*i)->gCost) {
						insertionPos = i;
						break;
					}
				}
				//Insert the node at the appropriate position
				openList.insert(insertionPos, &e);
			}
			//Otherwise the target node IS in the open list
			else {
				//Compare the new G Score to the old one before updating
				if (currentNode->gCost + e.gCost < e.gCost) {
					//Calculate the target node's G Score
					e.gCost = currentNode->gCost + e.gCost;
					//Set the target node's previous to currentNode
					e.parent = currentNode;
				}
			}
		}
	}
}

void PathFinding::GetFinalPath(Node* pStartNode, Node* pEndNode)
{
	//std::list<Node> finalPath;//List to hold the path sequentially 
	Node* currentNode = pEndNode;//Node to store the current node being checked

	while (currentNode != pStartNode) {//While loop to work through each node going through the parents to the beginning of the path
		//finalPath.push_back(currentNode);//Add that node to the final path
		grid->finalPath.push_back(currentNode);//Add that node to the final path
		currentNode->finalPath = true;
		if (currentNode->HasParent()) {
			currentNode = currentNode->parent;//Move onto its parent node
		}
	}

	//finalPath.reverse();//Reverse the path to get the correct order
	grid->finalPath.reverse();//Reverse the path to get the correct order

	//grid->finalPath = finalPath;//Set the final path
}

int PathFinding::GetManhattenDistance(Node* pNodeA, Node* pNodeB)
{
	int x = abs(pNodeA->gridX = pNodeB->gridX);
	int y = abs(pNodeA->gridY = pNodeB->gridY);

	return x + y;
}

bool PathFinding::ContainsNode(Node pNode, std::vector<Node*> nodeList)
{
	bool result = false;
	for (Node* node : nodeList) {
		if (node->FCost() == pNode.FCost() && node->gridX == pNode.gridX && node->gridY == pNode.gridY) {
			result = true;
		}
	}
	return result;
}

//bool PathFinding::NodeSort(Node* first, Node* second)
//{
//	return (first->gCost < second->gCost);
//
//	
//}

 