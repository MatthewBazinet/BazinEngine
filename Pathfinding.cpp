#include "Pathfinding.h"


bool operator==(GridVec a, GridVec b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator!=(GridVec a, GridVec b)
{
	return !(a == b);
}

bool operator<(GridVec a, GridVec b)
{

	return std::tie(a.x, a.y) < std::tie(b.x, b.y);

}


void Grid::addRect(int x1, int y1, int x2, int y2)
{
		for (int x = x1; x < x2; x++) {
			for (int y = y1; y < y2; y++) {
				walls.insert(GridVec{ x, y });
			}
		}
}


void GridWithWeights::addRoughTerrain(int x1, int y1, int x2, int y2)
{
	for (int x = x1; x < x2; x++) {
		for (int y = y1; y < y2; y++) {
			roughTerrain.insert(GridVec{ x, y });
		}
	}
}

void Pathfinding::aStarSearch(GridWithWeights graph, GridVec start, GridVec goal, std::unordered_map<GridVec, GridVec>& cameFrom, std::unordered_map<GridVec, double>& costSoFar)
{
	PriorityQueue<GridVec, double> frontier;
	frontier.put(start, 0);

	//start at start with no cost
	cameFrom[start] = start;
	costSoFar[start] = 0;

	while (!frontier.empty()) {
		GridVec current = frontier.get();

		if (current == goal) {
			break;
		}

		for (GridVec next : graph.neighbors(current)) { //checks for each non-wall in-bounds neighboring node (determined by the DIRS array)
			double new_cost = costSoFar[current] + graph.cost(current, next);
			if (costSoFar.find(next) == costSoFar.end() || new_cost < costSoFar[next]) { //checks which neighboring node adds the least cost and adds them to the frontier based on cost and the heuristic
				costSoFar[next] = new_cost;
				double priority = new_cost + heuristic(next, goal);
				frontier.put(next, priority);
				cameFrom[next] = current; //sets the map up so the path can be reversed by using the next node as the key for the current one
			}
		}
	}
}

std::vector<GridVec> Pathfinding::makePath(
	GridVec start, GridVec goal,
	std::unordered_map<GridVec, GridVec> cameFrom
) {
	std::vector<GridVec> path;
	GridVec current = goal;
	while (current != start) {
		path.push_back(current);
		current = cameFrom[current]; //uses current as key to retrieve the previous node from the map
	}
	path.push_back(start);
	std::reverse(path.begin(), path.end());
	return path;
}

