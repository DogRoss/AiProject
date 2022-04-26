#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>
#include <iostream>

namespace pathfinding {
	struct Node;

	struct Edge {
		Edge() { target = nullptr; cost = 0; }
		Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}

		Node* target;
		float cost;
	};

	struct Node {

		Node() {}
		Node(float x, float y) { position.x = x; position.y = y; gScore = 0; previous = nullptr; }

		Vector2 position;

		float gScore;
		float hScore;
		float fScore;
		Node* previous;

		std::vector<Edge> connections;

		void ConnectTo(Node* other, float cost);
		Node* FindNeighborNode(int direction);
		int CalculateHeuristic(Node* other);
		int CalculateFScore(Node* other);
	};

	std::vector<Node*> AStar(Node* startNode, Node* endNode);
	void DrawPath(std::vector<Node*>& path, Color lineColor);
	void DrawNode(Node* node, bool selected = false);
	void DrawGraph(Node* node, std::vector<Node*>* drawnList);
}