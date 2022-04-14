#include "GridMap.h"

GridMap::GridMap(int nRadius, Vector2 gWorldSize, Vector2 gPosition)
{
	gridPosition = gPosition; //sets position of grid in world space, and sets size of nodes
	nodeRadius = nRadius;
	nodeDiameter = nodeRadius * 2;

	gridWorldSize = gWorldSize; //sets size of grid in world space
	gridSizeX = round(gridWorldSize.x / nodeDiameter);
	gridSizeY = round(gridWorldSize.y / nodeDiameter);

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

Node GridMap::NodeFromWorldPosition(Vector2 nWorldPos) //grabs the node found at the specified world pos
{
	float xPoint = ((nWorldPos.x + gridWorldSize.x / 2) / gridWorldSize.x);
	float yPoint = ((nWorldPos.y + gridWorldSize.y / 2) / gridWorldSize.y);

	float min = 0, float max = 0;
	xPoint = std::clamp(xPoint, min, max);
	yPoint = std::clamp(yPoint, min, max);

	int x = round((gridSizeX - 1) * xPoint);
	int y = round((gridSizeY - 1) * yPoint);

	return grid[TraverseGrid(x, y)];
}

void GridMap::Draw()
{
	Color regNode = BLACK;
	Color fPathNode = RED;
	for (int i = 0; i < gridSizeX * gridSizeY; i++) {

		if (!finalPath.empty()) {
			if (std::find(finalPath.begin(), finalPath.end(), grid[i]) != finalPath.end()) {
				DrawRectangle(grid[i].position.x - nodeRadius, grid[i].position.y - nodeRadius, nodeRadius, nodeRadius, fPathNode);
			}
		}
		else {
			DrawRectangle(grid[i].position.x - nodeRadius, grid[i].position.y - nodeRadius, nodeRadius, nodeRadius, regNode);
		}
	}
}
