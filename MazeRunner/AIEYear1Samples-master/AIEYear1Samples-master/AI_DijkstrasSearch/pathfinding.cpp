#include "pathfinding.h"
#include <algorithm>
#include <vector> 

namespace pathfinding
{
	//Use this function to sort nodes using their gScore value
	bool NodeSort(Node* i, Node* j) 
	{ 
		return (i->fScore < j->fScore); 
	}

	void Node::ConnectTo(Node* other, float cost)
	{
		connections.push_back(Edge(other, cost));
	}

	Node* Node::FindNeighborNode(int direction)
	{
		for (Edge e : connections) {
			switch (direction) {
			case 0:
				if (e.target->position.y < position.y) {
					return e.target;
				}
				break;
			case 1:
				if (e.target->position.x < position.x) {
					return e.target;
				}
				break;

			case 2:
				if (e.target->position.y > position.y) {
					return e.target;
				}
				break;

			case 3:
				if (e.target->position.x > position.x) {
					return e.target;
				}
				break;
			}
		}

		return nullptr;
	}

	int Node::CalculateHeuristic(Node* other)
	{
		hScore = 0;

		//hScore = sqrt(pow(position.x - position.y) + pow(other->position.x - other->position.y));
		hScore = hypot((position.x - position.y), (other->position.x - other->position.y));
		//std::cout << hScore << +" hCost" << std::endl;
		return hScore;
	}

	int Node::CalculateFScore(Node* other)
	{
		hScore = CalculateHeuristic(other);
		fScore = hScore + gScore;
		return fScore;
	}

	

	std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode)
	{
		//Validate the input
		if (startNode == nullptr || endNode == nullptr)
		{
			return std::vector<Node*>();
		}

		if (startNode == endNode)
		{
			std::vector<Node*> singleNodePath;
			singleNodePath.push_back(startNode);
			return singleNodePath;
		}

		//Initialize the starting node
		startNode->gScore = 0;
		startNode->previous = nullptr;

		//Create our temporary lists for storing nodes
		std::vector<Node*> openList;
		std::vector<Node*> closedList;

		//Add the starting node to openList
		openList.push_back(startNode);


		while (!openList.empty())
		{
			std::sort(openList.begin(), openList.end(), NodeSort);

			auto current_it = openList.begin();
			Node* current = *current_it;

			if (current == endNode) {
				break;
			}

			closedList.push_back(current);
			openList.erase(current_it);

			for (Edge e : current->connections) {
				if (!std::count(closedList.begin(), closedList.end(), e.target)) {
					e.target->gScore = current->gScore + e.cost;
					e.target->hScore = e.target->CalculateHeuristic(endNode);
					e.target->fScore = e.target->gScore + e.target->hScore;

					if (!std::count(openList.begin(), openList.end(), e.target)) {
						e.target->gScore = current->gScore; //error might be thrown here, replace rhs with currentNode scores
						e.target->fScore = current->fScore; 
						e.target->previous = current;
						openList.push_back(e.target);
					}
					else if (e.target->previous->fScore < e.target->fScore) {
						e.target->gScore = current->gScore; //error might be thrown here, replace rhs with currentNode scores
						e.target->fScore = current->fScore;
						e.target->previous = current;
					}
				}
			}
		}

		std::vector<Node*> path;
		Node* current = endNode;
		while (current) {
			path.insert(path.begin(), current);
			current = current->previous;
		}

		return path;
	}

	void DrawPath(std::vector<Node*>& path, Color lineColor)
	{
		for (int i = 1; i < path.size(); i++)
			DrawLine(path[i - 1]->position.x, path[i - 1]->position.y, path[i]->position.x, path[i]->position.y, lineColor);
	}

	void DrawNode(Node* node, bool selected)
	{
		static char buffer[10];
		sprintf_s(buffer, "%.0f", node->gScore);

		//Draw the circle for the outline
		DrawCircle(node->position.x, node->position.y, 25, YELLOW);
		//Draw the inner circle
		if (selected)
		{
			DrawCircle(node->position.x, node->position.y, 22, BROWN);
		}
		else
		{
			DrawCircle(node->position.x, node->position.y, 22, BLACK);
		}
		//Draw the text
		DrawText(buffer, node->position.x - 10, node->position.y - 10, 15, WHITE);
	}

	void DrawGraph(Node* node, std::vector<Node*>* drawnList)
	{
		DrawNode(node);
		drawnList->push_back(node);

		//For each Edge in this node's connections
		for (Edge e : node->connections)
		{
			//Draw the Edge
			DrawLine(node->position.x, node->position.y, e.target->position.x, e.target->position.y, WHITE);
			//Draw the cost
			Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
			static char buffer[10];
			sprintf_s(buffer, "%.0f", e.cost);
			DrawText(buffer, costPos.x, costPos.y, 15, WHITE);
			//Draw the target node
			if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end())
			{
				DrawGraph(e.target, drawnList);
			}
		}
	}
}