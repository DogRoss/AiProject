#pragma once
#include "raylib.h"
#include "pathfinding.h"
#include <vector>
#include <iostream>

namespace pathfinding
{
	class playerAgent
	{
	public:
		Vector2 position;

		Node* nextNode = nullptr;
		Node* currentNode;

		float speed;

		void SetNode(Node* node);
		void Update(float deltaTime);
		void GoToNode(Node* node);

		void Draw();
	};
}
