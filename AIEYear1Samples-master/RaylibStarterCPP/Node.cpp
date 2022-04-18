#include "Node.h"

bool Node::HasParent()
{
	if (parent == nullptr) {
		return false;
	}
	else if (parent->gridX && parent->gridY) {
		return true;
	}
	else {
		return false;
	}
}

bool Node::operator==(Node other)
{
	if (gridX == other.gridX && gridY == other.gridY && position.x == other.position.x && position.y == other.position.y) {
		return true;
	}
	else {
		return false;
	}
}

bool Node::operator!=(Node other)
{
	if (gridX != other.gridX || gridY != other.gridY && position.x == other.position.x && position.y == other.position.y)
		return true;
	else
		false;
}

