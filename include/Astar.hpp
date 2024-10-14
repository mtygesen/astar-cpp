#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <set>
#include <functional>
#include <queue>

#include "Path.hpp"

template<class T, class U>
class Astar {
    public:
     Astar(std::set<T> states, 
           std::set<U> actions, 
           std::function<double(U)> costFunction, 
           std::set<std::tuple<T, U, T>> relations,
           T initialState,
           T goalState) : states(states), 
                          actions(actions), 
                          costFunction(costFunction), 
                          relations(relations), 
                          initialState(initialState),
                          goalState(goalState) {}

     Path<T> search(std::function<double(U)> heuristic) {
        auto solution = Path<T>();
        T node = this->initialState;
        std::unordered_map<T, T> predecessor;
        std::unordered_map<T, double> cost;
        std::unordered_set<T> explored; 

        using PQElem = std::pair<double, T>;
        std::priority_queue<PQElem, std::vector<PQElem>, std::greater<PQElem>> frontier;
        frontier.emplace(0, node);
        predecessor[node] = node;
        cost[node] = 0;

        while (!frontier.empty()) {
            node = frontier.top().second;
            frontier.pop();

            if (isGoal(node)) {
                while (node != this->initialState) {
                    solution.push(node);
                    node = predecessor[node];
                }

                solution.push(node);

                return solution;
            }

            explored.insert(node);

            for (const auto& relation : relations) {
                T from, to;
                U action;
                std::tie(from, action, to) = relation;

                if (from == node) {
                    double newCost = cost[node] + costFunction(action);
                    if (cost.find(to) == cost.end() || newCost < cost[to]) {
                        cost[to] = newCost;
                        double priority = newCost + heuristic(to);
                        frontier.emplace(priority, to);
                        predecessor[to] = node;
                    }
                }
            }
        }

        return solution;
     }
    
    private:
     bool isGoal(T node) {
        return node == goalState;
     }

     std::set<T> states;
     std::set<U> actions; 
     std::function<double(T)> costFunction;
     std::set<std::tuple<T, U, T>> relations;
     T initialState;
     T goalState;
};

#endif