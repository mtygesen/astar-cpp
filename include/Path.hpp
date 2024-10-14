#ifndef PATH_HPP
#define PATH_HPP

#include <stack>
#include <iostream>

template<class T>
class Path {
    public:
     void push(T node) {
        _path.push(node);
     }

     T pop() {
        T top = _path.top();
        _path.pop();
        return top;
     }

     size_t size() {
        return _path.size();
     }

     friend std::ostream &operator<<(std::ostream &os, Path<T> path) {
        while (path.size() != 0) {
            std::cout << path.pop() << ' ';
        }

        return os;
     }

    private:
     std::stack<T> _path;
};

#endif