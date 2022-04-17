#include "PathFinding.h"

void PathFinding::OnUpdate()
{
	FindPath(startPos, targetPos);
}

void PathFinding::FindPath(Vector2 pStartPos, Vector2 pTargetPos)
{
	Node startNode = grid.NodeFromWorldPosition(pStartPos);
	Node targetNode = grid.NodeFromWorldPosition(pTargetPos);

	std::list<Node> openList; //list of nodes being checked
	std::unordered_set<Node> closedList; //list of nodes that were checked

	openList.push_back(startNode);

	while (!openList.empty()) {
		Node currentNode = openList.front();
		std::list<Node>::iterator nIterator = openList.begin();
		for (int i = 1; i < openList.size(); i++) {
			advance(nIterator, i);
			if ((*nIterator).FCost() < currentNode.FCost() || (*nIterator).FCost() == currentNode.FCost() && (*nIterator).hCost < currentNode.hCost) {
				currentNode = (*nIterator);
			}
		}
		openList.remove(currentNode);
		closedList.insert(currentNode);

		if (currentNode == targetNode) {
			GetFinalPath(startNode, targetNode);
		}

		std::list<Node>::iterator gIterator = grid.GetNeighboringNodes(currentNode).begin();
		for (int i = 0; i < grid.GetNeighboringNodes(currentNode).size(); i++) {
			advance(gIterator, i);
			bool exists = 
			if(std::find(closedList.begin(),closedList.end(),(*gIterator)))
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
