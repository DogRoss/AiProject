#include "playerAgent.h"



void pathfinding::playerAgent::SetNode(Node* node)
{
	currentNode = node;
	position = node->position;
}

void pathfinding::playerAgent::Update(float deltaTime)
{
    if (currentNode == nullptr) return;
    

    if (IsKeyDown(87) && currentNode->FindNeighborNode(0)) { //W
        if (abs(position.x - currentNode->position.x) < 5 && abs(position.y - currentNode->position.y) < 5) {
            currentNode = currentNode->FindNeighborNode(0);
        }
    }
    else if (IsKeyDown(65) && currentNode->FindNeighborNode(1)) { //A
        if (abs(position.x - currentNode->position.x) < 5 && abs(position.y - currentNode->position.y) < 5) {
            currentNode = currentNode->FindNeighborNode(1);
        }
    }
    else if (IsKeyDown(83) && currentNode->FindNeighborNode(2)) { //S
        if (abs(position.x - currentNode->position.x) < 5 && abs(position.y - currentNode->position.y) < 5) {
            currentNode = currentNode->FindNeighborNode(2);
        }
    }
    else if (IsKeyDown(68) && currentNode->FindNeighborNode(3)) { //D
        if (abs(position.x - currentNode->position.x) < 5 && abs(position.y - currentNode->position.y) < 5) {
            currentNode = currentNode->FindNeighborNode(3);
        }
    }
    // find out how far we have to go to the next node
    float dx = currentNode->position.x - position.x;
    float dy = currentNode->position.y - position.y;
    float distanceToNext = sqrtf(abs(dx * dx) + abs(dy * dy));

    if (distanceToNext < 2) {
        
        position = currentNode->position;
        return;
    }

    // normalize the vector to the next node
    if (distanceToNext > 1)
    {
        dx /= distanceToNext;
        dy /= distanceToNext;
    }
    //distanceToNext -= speed * deltaTime;
    if (distanceToNext >= 1)
    {

        // we wont get to the target node this frame - so move linearly towards it
        position.x += dx * speed * deltaTime;
        position.y += dy * speed * deltaTime;
    }
    else
    {
        // move on to the next node
        Node* oldNode = *&currentNode;
        currentNode = nextNode;
        // get the unit vectore from the old node to the new one
        dx = currentNode->position.x - oldNode->position.x;
        dy = currentNode->position.y - oldNode->position.y;
        float mag = sqrtf(dx * dx + dy * dy);
        dx /= mag;
        dy /= mag;

        // move along the path from the previous node to the new current node by the amount by which we overshot
        // (which is -distanceToNext)
        position.x = oldNode->position.x - distanceToNext * dx;
        position.y = oldNode->position.y - distanceToNext * dy;        
    }
}



void pathfinding::playerAgent::Draw()
{
    DrawCircle(position.x, position.y, 8, { 255,0,255,255 });
}
