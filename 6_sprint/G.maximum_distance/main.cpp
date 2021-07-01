#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

enum class color {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2
};

std::vector<int> BFS(const std::vector<std::vector<int>>& list_of_adjacency, int start_vertex) {

   std::vector<color> color(list_of_adjacency.size(), color::WHITE);
   std::vector<int> distance(list_of_adjacency.size(), 0);
   std::queue<int> planned;

   planned.push(start_vertex);
   color[start_vertex] = color::GRAY;

   while (!planned.empty()) {

      int current_vertex = planned.front();
      planned.pop();

      for (const int adjacency_vertex : list_of_adjacency[current_vertex]) {

         if (color[adjacency_vertex] == color::WHITE) {

            color[adjacency_vertex] = color::GRAY;
            distance[adjacency_vertex] = distance[current_vertex] + 1;
            planned.push(adjacency_vertex);

         }

      }

      color[current_vertex] = color::BLACK;

   }

   return distance;

}

int main() {

   int number_of_vertices, number_of_edges;

   std::cin >> number_of_vertices >> number_of_edges;

   std::vector<std::pair<int, int>> list_of_edges(number_of_edges);

   for (auto& edge : list_of_edges) {

      std::cin >> edge.first >> edge.second;

      if (edge.second < edge.first) {

         std::swap(edge.first, edge.second);

      }

   }

   int start_vertex;

   std::cin >> start_vertex;

   std::sort(list_of_edges.begin(), list_of_edges.end());

   std::vector<std::vector<int>> list_of_adjacency(number_of_vertices);

   for(const auto& edge : list_of_edges) {

      list_of_adjacency[edge.first - 1].emplace_back(edge.second - 1);
      list_of_adjacency[edge.second - 1].emplace_back(edge.first - 1);

   }

   auto answer = BFS(list_of_adjacency, start_vertex - 1);

   std::cout << *std::max_element(answer.begin(), answer.end());

   return 0;

}