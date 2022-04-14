#include "Node.h"

bool Node::operator==(Node other)
{
	if (gridX == other.gridX && gridY == other.gridY) 
		return true;
	else 
		false;
}

