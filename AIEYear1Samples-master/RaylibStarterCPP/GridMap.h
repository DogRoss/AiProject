#include <stdio.h>
#include <list>
#include <math.h>
#include <algorithm>

#include "Node.h"
#include "MathHandler.h"

#pragma once
class GridMap
{
	/*
	width/height of node map (number of nodes on each axis)
	node radius (radius is half the full length of a side)
	*/

public:
	GridMap(int nRadius, Vector2 gWorldSize, Vector2 gPosition);
	
	Vector2 gridPosition;
	Vector2 gridWorldSize; //width/height in world space
	float nodeRadius; //size of nodes
	float distance; //distance between each node;

	Node* grid; //1D array, use as if a 2D array
	std::list<Node> finalPath; //path of nodes in which the agent will follow

	float nodeDiameter; //stores diameter of nodes, is double the nodeRadius
	int gridSizeX, gridSizeY; //Node grid array size

	
	void CreateGrid();

	int TraverseGrid(int x, int y); //traverse grid to specific position in array

	Vector2 AddVectors(Vector2 lhs, Vector2 rhs); //adds two specified vectors together

	Node NodeFromWorldPosition(Vector2 gWorldPos);

	std::list<Node> GetNeighboringNodes(Node gNode);

	void Draw();
};

