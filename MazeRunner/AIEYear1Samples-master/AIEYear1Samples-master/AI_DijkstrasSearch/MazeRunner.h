#pragma once
#include "raylib.h"
#include "pathfinding.h"
#include "playerAgent.h"
#include "NodeMap.h"
#include <vector>
#include <iostream>
#include <random>

namespace pathfinding
{
	class MazeRunner
	{
	public:
		Vector2 position;

		Color runnerColor;

		std::vector<Node*> storedPositions;
		std::vector<Node*> path;
		int currentIndex = 0;
		Node* currentNode;
		Node* targetNode;
		Node* startNode;
		NodeMap* nMap;
		playerAgent* player;

		bool seen = false;

		float speed;

		bool PlayerDetection();

		void AddPosition(Node* node);
		void ChangeTargetNode();
		bool AtTarget();

		void SetNode(Node* node, Node* nodeTarget, Node* nodeStart, playerAgent* agent, NodeMap* nodeMap);
		void Update(float deltaTime);
		void GoToNode(Node* node);

		void Draw();
	};
}
