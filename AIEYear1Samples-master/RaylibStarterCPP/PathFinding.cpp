#include "PathFinding.h"

void PathFinding::OnUpdate()
{
	//FindPath(startPos, targetPos);
}

void PathFinding::FindPath(Vector2 pStartPos, Vector2 pTargetPos)
{
	Node startNode = grid.NodeFromWorldPosition(pStartPos);
	Node targetNode = grid.NodeFromWorldPosition(pTargetPos);

	std::list<Node> openList; //list of nodes being checked
	std::list <Node> closedList; //list of nodes that were checked

	openList.push_back(startNode);

	while (!openList.empty()) {
		Node currentNode = openList.front();
		std::list<Node>::iterator nIterator = openList.begin();
		for (int i = 1; i < openList.size(); i++) {
			nIterator = openList.begin();
			advance(nIterator, i);
			if ((*nIterator).FCost() < currentNode.FCost() || (*nIterator).FCost() == currentNode.FCost() && (*nIterator).hCost < currentNode.hCost) {
				currentNode = (*nIterator);
			}
		}
		//openList.remove(currentNode); //TODO: ERROR
		openList.erase(nIterator);
		closedList.push_back(currentNode);

		if (currentNode == targetNode) {
			GetFinalPath(startNode, targetNode);
		}

		for (int i = 0; i < grid.GetNeighboringNodes(currentNode).size(); i++) {
			std::list<Node>::iterator gIterator = grid.GetNeighboringNodes(currentNode).begin();
			advance(gIterator, i);
			bool exists = (std::find(closedList.begin(), closedList.end(), (*gIterator)) == closedList.end());
			if (exists) {
				continue;
			}
			int moveCost = currentNode.gCost + GetManhattenDistance(currentNode, (*gIterator));
		
			if (moveCost < (*gIterator).gCost || !exists) {
				(*gIterator).gCost = moveCost;
				(*gIterator).gCost = GetManhattenDistance((*gIterator), targetNode);
				(*gIterator).parent = &currentNode;
		
				if (!exists) {
					openList.push_back((*gIterator));
				}
			}
		}
	}
}

void PathFinding::GetFinalPath(Node pStartNode, Node pEndNode)
{
	std::list<Node> finalPath;
	Node currentNode = pEndNode;

	while (currentNode != pStartNode) {
		finalPath.push_back(currentNode);
		currentNode = *currentNode.parent;
	}

	finalPath.reverse();

	grid.finalPath = finalPath;
}

int PathFinding::GetManhattenDistance(Node pNodeA, Node pNodeB)
{
	int x = abs(pNodeA.gridX = pNodeB.gridX);
	int y = abs(pNodeA.gridY = pNodeB.gridY);

	return x + y;
}
 