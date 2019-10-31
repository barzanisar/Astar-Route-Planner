/**
 * @file route_planner.h
 * @author https://github.com/udacity/CppND-Route-Planning-Project
 * @author Comments added by Barza Nisar (barzanisar@sabanciuniv.edu)
 * @brief Header file for A star route planner.
 * @date 2019-10-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    /**
     * @brief Construct a new Route Planner object
     * 
     * @param model Model containing the map information e.g. nodes, ways etc
     * @param start_x Start position's x coordinate.
     * @param start_y Start position's y coordinate.
     * @param end_x End position's x coordinate.
     * @param end_y End position's y coordinate.
     */
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    
    /**
     * @brief Get the distance of the final path.
     * 
     * @return distance
     */
    float GetDistance() const {return distance;}

    /**
     * @brief Finds shortest path from start_node to end_node via A star search method.
     */
    void AStarSearch();


    /*************************************************************************************
     * The following methods have been made public so we can test them individually.
     * They are not intended to be used by the main.cpp
     * ***********************************************************************************/

    /**
     * @brief Expands the current node by adding all its unvisited neighbors to the open list.
     * 
     * @param current_node Node to expand.
     */
    void AddNeighbors(RouteModel::Node *current_node);

    /**
     * @brief Calculates h value i.e. the distance from the input node to the end_node.
     * 
     * @param node Input node
     * @return h value
     */
    float CalculateHValue(RouteModel::Node const *node);

    /**
     * @brief Constructs the final path found from A* search.
     * 
     * This method takes the current (final) node as an argument and iteratively constructs the final path 
     * by following the chain of parents of nodes until the starting node is found.
     * It also calculates the distance of the final path.
     * 
     * @return final path
     */
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);

    /**
     * @brief Returns a pointer to the node in open list with lowest g+h value.
     * 
     * This method sorts the open list in descending order of g+h value 
     * and pops out the lowest sum node from the list.
     * 
     * @return A pointer to the node in open list with lowest g+h
     */
    RouteModel::Node *NextNode();

  private:
    std::vector<RouteModel::Node*> open_list; // Open list of nodes for A star search
    RouteModel::Node *start_node; // Start node for search
    RouteModel::Node *end_node; // End node for search

    float distance = 0.0f; // Final path distance
    RouteModel &m_Model; // Model containing the map information e.g. nodes, ways etc
};

#endif