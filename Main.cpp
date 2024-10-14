#include <Astar.hpp>

int main() {
    std::set<char> states{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    std::set<int> actions{1, 2, 3, 4, 5};
    std::function<double(int)> costFunction = [](int c) { return c; }; 
    std::set<std::tuple<char, int, char>> relations = {{'A', 5, 'C'}, 
        {'A', 2, 'B'},
        {'A', 4, 'D'},
        {'B', 2, 'E'},
        {'B', 1, 'A'},
        {'E', 1, 'B'},
        {'F', 1, 'E'},
        {'I', 1, 'F'},
        {'C', 2, 'A'},
        {'C', 1, 'G'},
        {'C', 2, 'H'},
        {'G', 3, 'D'},
        {'G', 4, 'I'},
        {'H', 1, 'I'},
    };
    auto initial = *states.find('A');
    auto goal = *states.find('I');

    Astar<char, int> astar(states, actions, costFunction, relations, initial, goal);

    std::function<double(int)> heuristic = [](int) { return 0; };
    Path<char> result = astar.search(heuristic);
    std::cout << "Path: " << result << '\n';
}