#include "PathFinding.h"

PathFinding::PathFinding(Vector2 pStartPos, Vector2 pTargetPos, GridMap pGrid)
{
	grid = &pGrid;
	startPos = pStartPos;
	targetPos = pTargetPos;
}

void PathFinding::OnUpdate()
{
	FindPath(startPos, targetPos);
}

void PathFinding::FindPath(Vector2 pStartPos, Vector2 pTargetPos)
{
	Node startNode = grid->NodeFromWorldPosition(pStartPos);
	Node targetNode = grid->NodeFromWorldPosition(pTargetPos);

	std::list<Node> openList; //list of nodes being checked
	std::list <Node> closedList; //list of nodes that were checked

	openList.push_back(startNode);

	while (!openList.empty()) {
		Node currentNode = openList.front();//Create a node and set it to the first item in the open list
		std::list<Node>::iterator nIterator = openList.begin();
		for (int i = 1; i < openList.size(); i++) {//Loop through the open list starting from the second object
			nIterator = openList.begin();
			advance(nIterator, i);
			if ((*nIterator).FCost() < currentNode.FCost() || (*nIterator).FCost() == currentNode.FCost() && (*nIterator).hCost < currentNode.hCost) {
				currentNode = (*nIterator);//Set the current node to that object
			}
		}
		openList.erase(nIterator);	//Remove that from the open list
		closedList.push_back(currentNode);	//And add it to the closed list

		if (currentNode == targetNode) {	//If the current node is the same as the target node
			GetFinalPath(startNode, targetNode);	//Calculate the final path
		}

		for (int i = 0; i < grid->GetNeighboringNodes(currentNode).size(); i++) {	//Loop through each neighbor of the current node
			std::list<Node>::iterator gIterator = grid->GetNeighboringNodes(currentNode).begin();
			advance(gIterator, i);
			bool exists = (std::find(closedList.begin(), closedList.end(), (*gIterator)) == closedList.end());
			if (exists) {	//If the neighbor is a wall or has already been checked
				continue;
			}
			int moveCost = currentNode.gCost + GetManhattenDistance(currentNode, (*gIterator));	//Get the F cost of that neighbor
		
			if (moveCost < (*gIterator).gCost || !exists) {//If the f cost is greater than the g cost or it is not in the open list
				(*gIterator).gCost = moveCost;//Set the g cost to the f cost
				(*gIterator).gCost = GetManhattenDistance((*gIterator), targetNode);//Set the h cost
				(*gIterator).parent = &currentNode;//Set the parent of the node for retracing steps
		
				if (!exists) {//If the neighbor is not in the openlist
					openList.push_back((*gIterator));//Add it to the list
				}
			}
		}
	}
}

void PathFinding::GetFinalPath(Node pStartNode, Node pEndNode)
{
	std::list<Node> finalPath;//List to hold the path sequentially 
	Node currentNode = pEndNode;//Node to store the current node being checked

	while (currentNode != pStartNode) {//While loop to work through each node going through the parents to the beginning of the path
		finalPath.push_back(currentNode);//Add that node to the final path
		currentNode.finalPath = true;
		if (currentNode.HasParent()) {
			currentNode = *currentNode.parent;//Move onto its parent node
		}
	}

	finalPath.reverse();//Reverse the path to get the correct order

	grid->finalPath = finalPath;//Set the final path
}

int PathFinding::GetManhattenDistance(Node pNodeA, Node pNodeB)
{
	int x = abs(pNodeA.gridX = pNodeB.gridX);
	int y = abs(pNodeA.gridY = pNodeB.gridY);

	return x + y;
}
 