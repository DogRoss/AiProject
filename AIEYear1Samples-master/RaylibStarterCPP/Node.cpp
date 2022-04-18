#include "Node.h"

bool Node::operator==(Node other)
{
	if (gridX == other.gridX && gridY == other.gridY && position.x == other.position.x && position.y == other.position.y)
		return true;
	else 
		false;
}

bool Node::operator!=(Node other)
{
	if (gridX != other.gridX || gridY != other.gridY && position.x == other.position.x && position.y == other.position.y)
		return true;
	else
		false;
}

