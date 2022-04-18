#include "GridMap.h"

GridMap::GridMap()
{
	Vector2 gPosition;
	gPosition.x = 200, gPosition.y = 200;

	Vector2 gWorldSize;
	gWorldSize.x = 200, gWorldSize.y = 200;

	gridPosition = gPosition; //sets position of grid in world space, and sets size of nodes
	nodeRadius = 5;
	nodeDiameter = nodeRadius * 2;

	gridWorldSize = gWorldSize; //sets size of grid in world space
	gridSizeX = round(gridWorldSize.x / nodeDiameter);
	gridSizeY = round(gridWorldSize.y / nodeDiameter);

	CreateGrid();
}

GridMap::GridMap(int nRadius, Vector2 gWorldSize, Vector2 gPosition)
{
	gridPosition = gPosition; //sets position of grid in world space, and sets size of nodes
	nodeRadius = nRadius;
	nodeDiameter = nodeRadius * 2;

	gridWorldSize = gWorldSize; //sets size of grid in world space
	double xTemp = 0, yTemp = 0;

	xTemp = round(gridWorldSize.x / nodeDiameter);
	yTemp = round(gridWorldSize.y / nodeDiameter);
	gridSizeX = (int)xTemp, gridSizeY = (int)yTemp;

	CreateGrid();
}

void GridMap::CreateGrid()
{
	grid = new Node[gridSizeX * gridSizeY];

	Vector2 bottomLeft = gridPosition;

	bottomLeft.x -= gridWorldSize.x / 2;
	bottomLeft.y -= gridWorldSize.y / 2;

	for (int x = 0; x < gridSizeX; x++) {		//iterates through each position in the array and assigns them to proper positions
		for (int y = 0; y < gridSizeY; y++) {
			Vector2 right;
			Vector2 up;
			right.x = (x * nodeDiameter + nodeRadius), right.y = 0;
			up.y = (y * nodeDiameter + nodeRadius), up.x = 0;
			
			Vector2 rightUp = AddVectors(right, up);
			Vector2 worldPoint = AddVectors(bottomLeft, rightUp);

			grid[TraverseGrid(x, y)] = Node(worldPoint, x, y); //creates node at specified point in grid with a world position to match
		}
	}
}

int GridMap::TraverseGrid(int x, int y)
{
	int result = y * gridSizeX;
	result += x;

	return result;
}

Vector2 GridMap::AddVectors(Vector2 lhs, Vector2 rhs)
{
	Vector2 result;
	result.x = (lhs.x + rhs.x);
	result.y = (lhs.y + rhs.y);
	return result;
}

Node GridMap::NodeFromWorldPosition(Vector2 gWorldPos) //grabs the node found at the specified world pos
{
	float xPoint = ((gWorldPos.x + gridWorldSize.x / 2) / gridWorldSize.x);
	float yPoint = ((gWorldPos.y + gridWorldSize.y / 2) / gridWorldSize.y);

	float min = 0, max = 1;
	xPoint = std::clamp(xPoint, min, max);
	yPoint = std::clamp(yPoint, min, max);

	double xTemp, yTemp;
	xTemp = round((gridSizeX - 1) * xPoint), yTemp = round((gridSizeY - 1) * yPoint);
	int x = (int)xTemp;
	int y = (int)yTemp;

	return grid[TraverseGrid(x, y)];
}

std::vector<Node> GridMap::GetNeighboringNodes(Node* gNode, std::vector<Node> &neighborList)//TODO: unfinished
{
	neighborList.clear();
	int xCheck, yCheck;

	//right side
	xCheck = gNode->gridX + 1;
	yCheck = gNode->gridY;

	if (xCheck >= 0 && xCheck < gridSizeX) {
		if (yCheck >= 0 && yCheck < gridSizeY) {
			neighborList.push_back(grid[TraverseGrid(xCheck, yCheck)]);
		}
	}

	//left side
	xCheck = gNode->gridX - 1;
	yCheck = gNode->gridY;

	if (xCheck >= 0 && xCheck < gridSizeX) {
		if (yCheck >= 0 && yCheck < gridSizeY) {
			neighborList.push_back(grid[TraverseGrid(xCheck, yCheck)]);
		}
	}

	//top side
	xCheck = gNode->gridX;
	yCheck = gNode->gridY + 1;

	if (xCheck >= 0 && xCheck < gridSizeX) {
		if (yCheck >= 0 && yCheck < gridSizeY) {
			neighborList.push_back(grid[TraverseGrid(xCheck, yCheck)]);
		}
	}

	//bottom side
	xCheck = gNode->gridX ;
	yCheck = gNode->gridY - 1;

	if (xCheck >= 0 && xCheck < gridSizeX) {
		if (yCheck >= 0 && yCheck < gridSizeY) {
			neighborList.push_back(grid[TraverseGrid(xCheck, yCheck)]);
		}
	}


	return neighborList;
}

void GridMap::Draw()
{
	Color regNode = BLACK;
	Color fPathNode = RED;
	for (int i = 0; i < gridSizeX * gridSizeY; i++) {

		//if (!finalPath.empty()) {
		//	if (std::find(finalPath.begin(), finalPath.end(), grid[i]) != finalPath.end()) {
		//		DrawRectangle(grid[i].position.x - nodeRadius, grid[i].position.y - nodeRadius, nodeRadius, nodeRadius, RED);
		//	}
		//}
		if (grid[i].finalPath == true) {
			DrawRectangle(grid[i].position.x - nodeRadius, grid[i].position.y - nodeRadius, nodeDiameter, nodeDiameter, RED);
		}
		else {
			DrawRectangle(grid[i].position.x - nodeRadius, grid[i].position.y - nodeRadius, nodeDiameter, nodeDiameter, BLACK);
		}
	}
}

