#include "PathFinding.h"

PathFinding::PathFinding(Vector2 pStartPos, Vector2 pTargetPos, GridMap* pGrid)
{
	grid = pGrid;
	startPos = pStartPos;
	targetPos = pTargetPos;
}

void PathFinding::OnUpdate()
{
	FindPath(startPos, targetPos);
}

void PathFinding::FindPath(Vector2 pStartPos, Vector2 pTargetPos)
{
	Node* startNode = &grid->NodeFromWorldPosition(pStartPos);
	Node* targetNode = &grid->NodeFromWorldPosition(pTargetPos);

	std::vector<Node*> openList; //list of nodes being checked
	std::vector<Node*> closedList; //list of nodes that were checked

	openList.push_back(startNode);

	while (!openList.empty()) {
		Node* currentNode = openList[0];//Create a node and set it to the first item in the open list
		for (int i = 1; i < openList.size(); i++) {//Loop through the open list starting from the second object

			if (openList[i]->FCost() < currentNode->FCost() || openList[i]->FCost() == currentNode->FCost() && openList[i]->hCost < currentNode->hCost) {//If the f cost of that object is less than or equal to the f cost of the current node
				currentNode = openList[i];//Set the current node to that object
			}
		}
		openList.erase(openList.begin());	//Remove that from the open list
		closedList.push_back(currentNode);	//And add it to the closed list

		if (currentNode == targetNode) {	//If the current node is the same as the target node
			GetFinalPath(startNode, targetNode);	//Calculate the final path
		}


		for (Node node : grid->GetNeighboringNodes(currentNode)) {	//Loop through each neighbor of the current node
			//bool exists = (std::find(closedList.begin(), closedList.end(), node) == closedList.end());
			if (ContainsNode(node, closedList)) {	//If the neighbor is a wall or has already been checked
				continue;
			}
			int moveCost = currentNode->gCost + GetManhattenDistance(currentNode, &node);	//Get the F cost of that neighbor
		
			if (moveCost < node.gCost || ContainsNode(node, closedList)) {//If the f cost is greater than the g cost or it is not in the open list
				node.gCost = moveCost;//Set the g cost to the f cost
				node.gCost = GetManhattenDistance(&node, targetNode);//Set the h cost
				node.parent = currentNode;//Set the parent of the node for retracing steps
		
				if (ContainsNode(node, closedList)) {//If the neighbor is not in the openlist
					openList.insert(openList.begin(), &node);//Add it to the list
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
 