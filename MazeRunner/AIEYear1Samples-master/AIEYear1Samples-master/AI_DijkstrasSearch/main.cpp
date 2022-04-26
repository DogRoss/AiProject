/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <iostream>
#include "pathfinding.h"
#include "NodeMap.h"
#include "playerAgent.h"
#include "MazeRunner.h"

using namespace pathfinding;

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	//Nodes
	Node* a = new Node();
	a->position = Vector2{ 125.0f, 75.0f };
	Node* b = new Node();
	b->position = Vector2{ 250.0f, 75.0f };
	Node* c = new Node();
	c->position = Vector2{ 250.0f, 150.0f };
	Node* d = new Node();
	d->position = Vector2{ 250.0f, 225.0f };
	Node* e = new Node();
	e->position = Vector2{ 187.0f, 300.0f };
	Node* f = new Node();
	f->position = Vector2{ 125.0f, 225.0f };
	//Edges
	a->connections.push_back(Edge{ b, 2 });
	a->connections.push_back(Edge{ f, 5 });
	b->connections.push_back(Edge{ c, 3 });
	c->connections.push_back(Edge{ a, 3 });
	c->connections.push_back(Edge{ d, 1 });
	d->connections.push_back(Edge{ e, 4 });
	d->connections.push_back(Edge{ f, 4 });
	f->connections.push_back(Edge{ e, 6 });

	std::vector<Node*> shortestPath = AStar(a, e);

	for (Node* node : shortestPath) {
		std::cout << node->gScore << std::endl;
	}

	// create a map of nodes from some grid-based ASCII art
	NodeMap nodeMap;
	nodeMap.cellSize = 32;
	std::vector<std::string> asciiMap;
	asciiMap.push_back("000000000000");
	asciiMap.push_back("010111011100");
	asciiMap.push_back("010101110110");
	asciiMap.push_back("011100000010");
	asciiMap.push_back("010111111110");
	asciiMap.push_back("010000001000");
	asciiMap.push_back("011111111110");
	asciiMap.push_back("000000000000");
	nodeMap.Initialise(asciiMap);

	Node* start = nodeMap.GetNode(1, 1);
	Node* playerStart = nodeMap.GetNode(10, 6);
	Node* end = nodeMap.GetNode(10, 6);
	std::vector<Node*> nodeMapPath = AStar(start, end);
	Color lineColor = { 255, 255, 255, 255 };

	playerAgent pAgent;
	pAgent.SetNode(playerStart);
	pAgent.speed = 200;

	MazeRunner runner; //AI maze runner
	runner.SetNode(start, end, start, &pAgent, &nodeMap);
	runner.speed = 100;

	//position goals for runner
	Vector2 vec1, vec2, vec3;
	vec1.x = 300, vec1.y = 50;
	vec2.x = 115, vec2.y = 50;
	vec3.x = 75, vec3.y = 210;
	runner.AddPosition(nodeMap.GetClosestNode(vec1));
	runner.AddPosition(nodeMap.GetClosestNode(vec2));
	runner.AddPosition(nodeMap.GetClosestNode(vec3));
	runner.AddPosition(start);
	runner.AddPosition(end);

    float time = (float)GetTime();
    float deltaTime;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		runner.Update(deltaTime);
		pAgent.Update(deltaTime);

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        bool drawNodeMap = true;

        nodeMap.Draw(true);
        DrawPath(runner.path, lineColor);

        runner.Draw();

		pAgent.Draw();

        EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}