#include "PathFinding.h"

void PathFinding::OnUpdate()
{
	FindPath(startPos, targetPos);
}

void PathFinding::FindPath(Vector2 pStartPos, Vector2 pTargetPos)
{
	Node startNode = grid.NodeFromWorldPosition(pStartPos);
	Node targetNode = grid.NodeFromWorldPosition(pTargetPos);

	std::list<Node> openList;
	std::unordered_set<Node> closedList;

	openList.push_front(startNode);

	while (!openList.empty()) {
		openList[];
		Node* currentNode = ;

	}
}
