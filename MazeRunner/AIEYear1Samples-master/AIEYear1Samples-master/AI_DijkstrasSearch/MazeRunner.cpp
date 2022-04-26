#include "MazeRunner.h"

//checks to see if contact has been made with the player
bool pathfinding::MazeRunner::PlayerDetection()
{
    if (abs(position.x - player->position.x) < 5 && abs(position.y - player->position.y) < 5) {
        seen = true;
        return true;
    }
    return false;
}

//adds a position for the AI to pursue
void pathfinding::MazeRunner::AddPosition(Node* node)
{
    storedPositions.push_back(node);
}

//changes to a random target from the target list for the AI to pursue
void pathfinding::MazeRunner::ChangeTargetNode() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, storedPositions.size() - 1); // define the range
    int num = distr(gen);
    if (num == currentIndex) {
        if (num == storedPositions.size() - 1) {
            num--;
        }
        else if (num == 0) {
            num++;
        }
        else {
            num++;
        }
    }
    
    currentIndex = num;

    targetNode = storedPositions[num];
}

//determines if the AI has reached its target
bool pathfinding::MazeRunner::AtTarget()
{
    if (nMap->GetClosestNode(position) == targetNode)
        return true;
    else
        return false;
}

//sets all required nodes for operating the AI
void pathfinding::MazeRunner::SetNode(Node* node, Node* nodeTarget, Node* nodeStart, playerAgent* agent, NodeMap* nodeMap) 
{
    targetNode = nodeTarget;
    startNode = nodeStart;
    player = agent;
	currentNode = node;
	position = node->position;
    nMap = nodeMap;

    runnerColor = YELLOW;

    AddPosition(nodeTarget);

    GoToNode(targetNode);
}



void pathfinding::MazeRunner::Update(float deltaTime)
{
    //if there isnt any path, return after setting node path to start
    if (path.empty()) {
        GoToNode(startNode);
        return;
    }

    //if seen by player, go to start, otherwise, go to target
    if (!PlayerDetection() && !seen) {
        GoToNode(targetNode);
    }
    else {
        runnerColor = WHITE;
        GoToNode(startNode);
        //if seen but are at start, go back to normal routine
        if (abs(position.x - startNode->position.x) < 5 && abs(position.y - startNode->position.y) < 5) {
            runnerColor = YELLOW;
            seen = false;
        }
    }
    
    //changes target after reaching first target
    if (AtTarget()) {
        ChangeTargetNode();
    }

    // find out how far we have to go to the next node
    float dx = currentNode->position.x - position.x;
    float dy = currentNode->position.y - position.y;
    float distanceToNext = sqrtf(dx * dx + dy * dy);

    // normalize the vector to the next node
    if (distanceToNext > 0)
    {
        dx /= distanceToNext;
        dy /= distanceToNext;
    }

    distanceToNext -= speed * deltaTime;
    if (distanceToNext >= 0)
    {
        // we wont get to the target node this frame - so move linearly towards it
        position.x += dx * speed * deltaTime;
        position.y += dy * speed * deltaTime;
    }
    else
    {
        currentIndex++;
        if (currentIndex >= path.size())
        {
            // we've reached the end, so stop on the node and clear our path
            position.x = currentNode->position.x;
            position.y = currentNode->position.y;
            path.clear();
        }
        else
        {
            // move on to the next node
            Node* oldNode = currentNode;
            currentNode = path[currentIndex];

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
}

//generates path for node;
void pathfinding::MazeRunner::GoToNode(Node* node)
{
    path = AStar(currentNode, node);
    currentIndex = 0;
}

void pathfinding::MazeRunner::Draw()
{
    DrawCircle(position.x, position.y, 8, runnerColor);
    DrawCircle(targetNode->position.x, targetNode->position.y, 8, RED);
}
