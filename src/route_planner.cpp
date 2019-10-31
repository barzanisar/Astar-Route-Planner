/**
 * @file route_planner.cpp
 * @author Barza Nisar (barzanisar@sabanciuniv.edu)
 * @brief Implementation of A star route planner.
 * @date 2019-10-31
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "route_planner.h"
#include <assert.h>
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel& model, float start_x, float start_y,
                           float end_x, float end_y)
    : m_Model(model) {
  // Convert inputs to percentage:
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;

  // Find the closest nodes to the starting and ending coordinates.
  // Store the nodes found in the RoutePlanner's start_node and end_node
  // attributes.
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);
}

float RoutePlanner::CalculateHValue(RouteModel::Node const* node) {
  return node->distance(*end_node);
}

void RoutePlanner::AddNeighbors(RouteModel::Node* current_node) {
  current_node->FindNeighbors();
  for (auto& node : current_node->neighbors) {
    if (!node->visited) {
      node->parent = current_node;
      node->g_value = current_node->g_value + current_node->distance(*node);
      node->h_value = CalculateHValue(node);
      node->visited = true;
      open_list.push_back(node);
    }
  }
}

RouteModel::Node* RoutePlanner::NextNode() {
  // Sort the open_list in descending order according to the sum of the h value
  // and g value.
  std::sort(open_list.begin(), open_list.end(),
            [](const auto& _1st, const auto& _2nd) {
              return (_1st->g_value + _1st->h_value) >
                     (_2nd->g_value + _2nd->h_value);
            });

  // Create a pointer to the node in the list with the lowest sum and
  // remove that node from the open_list.
  RouteModel::Node* lowest_f_node = open_list.back();
  open_list.pop_back();

  return lowest_f_node;
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(
    RouteModel::Node* current_node) {
  // Create path_found vector
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;

  RouteModel::Node* node = current_node;
  while (node != start_node) {
    // Until we reach the start node, any node's parent should not be a null ptr
    assert(node->parent != NULL);

    // For each node in the chain, add the distance from the node to its parent
    // to the distance attribute.
    distance += node->distance(*(node->parent));
    path_found.push_back(*node);
    node = node->parent;
  }

  // Add the start node
  path_found.push_back(*node);

  // Reverse the vector so that the start node is the first element
  // and the end node is the last element.
  std::reverse(path_found.begin(), path_found.end());

  // Multiply the distance by the scale of the map to get meters.
  distance *= m_Model.MetricScale();

  return path_found;
}

void RoutePlanner::AStarSearch() {
  RouteModel::Node* current_node = start_node;

  // Add current node to the open list and mark it as visited.
  open_list.push_back(current_node);
  current_node->visited = true;

  // Loop until open list is empty or we find the end node.
  while (open_list.size() > 0) {
    current_node = NextNode();
    if (current_node == end_node) {
      m_Model.path = ConstructFinalPath(current_node);
      return;
    }

    AddNeighbors(current_node);
  }
}