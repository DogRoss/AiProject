#include <unordered_set>

#include "GridMap.h"

#pragma once
class PathFinding
{
public:
	GridMap grid;
	Vector2 startPos;
	Vector2 targetPos;


	void OnUpdate();

	void FindPath(Vector2 pStartPos, Vector2 pTargetPos);
};

