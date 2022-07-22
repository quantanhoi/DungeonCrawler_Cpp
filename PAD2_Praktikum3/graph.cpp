#include "graph.h"
#include"Level.h"
Graph::Graph()
{

}

void Graph::drawGraph(std::vector<Node> path)
{
    std::vector<Node> data = path;

    std::sort(data.begin(), data.end(), [](const Node& v1, const Node& v2) {
            return (v1.x == v2.x) ? (v1.y < v2.y) : (v1.x < v2.x);
        });
    for(int i{}; i < numRows; i++) {
        for(int z{}; z < numColumns; z ++) {
            if(i == data.at(0).x && z == data.at(0).y && data.size() > 1) {
                std::cout << "a";
                data.erase(data.begin()+0);
            }

            else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}
