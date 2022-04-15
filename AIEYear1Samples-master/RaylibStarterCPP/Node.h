#include"raylib.h"

#pragma once
class Node
{
public:
    Node() : position(Vector2()), gridX(0), gridY(0) {};

    Node(Vector2 nPos, int nGridX, int nGridY) 
        : position(nPos), gridX(nGridX), gridY(nGridY) {};

    int gridX;   //position in node array
    int gridY;

    Vector2 position;    //world position of node

    Node* parent;     //stores previous node that agent came from

    int gCost;   //cost of moving to next square
    int hCost;   //distance to goal from current node

    int FCost() { return gCost + hCost; };

    bool operator ==(Node other);
    bool operator !=(Node other);
};

