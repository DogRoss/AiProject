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

	void OnUpdate();

	void FindPath(Vector2 pStartPos, Vector2 pTargetPos);

	void GetFinalPath(Node pStartNode, Node pEndNode);

	int GetManhattenDistance(Node pNodeA, Node pNodeB);

};

