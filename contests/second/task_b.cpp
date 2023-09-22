// Google style code
#include <iostream>
#include <vector>
#include <numeric>
#include <list>

class Graph {
 public:
   explicit Graph(uint32_t n) : adjacency_lists_(n, std::list<int>()), count_vertex_(n) {}
   
   void ReadFromStream(std::istream& stream) {
     
   }
   
   
 private:
   std::vector<std::list<int>> adjacency_lists_;
   uint32_t count_vertex_;
};
