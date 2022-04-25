#pragma once
#include "raylib.h"
#include "pathfinding.h"
#include "playerAgent.h"
#include <vector>
#include <iostream>

namespace pathfinding
{
	class MazeRunner
	{
	public:
		Vector2 position;

		std::vector<Node*> path;
		int currentIndex;
		Node* currentNode;
		Node* targetNode;
		Node* startNode;
		playerAgent* player;

		bool seen = false;

		float speed;

		bool PlayerDetection();

		void SetNode(Node* node, Node* nodeTarget, Node* nodeStart, playerAgent* agent);
		void Update(float deltaTime);
		void GoToNode(Node* node);

		void Draw();
	};
}
