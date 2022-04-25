#include <unordered_set>

#include "GridMap.h"

#pragma once
class PathFinding
{
public:
	GridMap* grid;
	Vector2 startPos;
	Vector2 targetPos;

	PathFinding(Vector2 pStartPos, Vector2 pTargetPos, GridMap* pGrid);

	/*struct NodeSort{
		bool operator()(const Node* first, const Node* second) const {
			return (first < second);
		}
	};*/

	void OnUpdate();

	void FindPath(Node* startNode, Node* endNode);

	void GetFinalPath(Node* pStartNode, Node* pEndNode);

	int GetManhattenDistance(Node* pNodeA, Node* pNodeB);

	bool ContainsNode(Node pNode, std::vector<Node*> nodeList);

	//bool NodeSort(Node* first, Node* second);

};

