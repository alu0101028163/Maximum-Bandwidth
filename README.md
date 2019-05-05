# Anti-Bandwidth Maximization Problem

## Problem definition:

## Construction of a starting solution for the different heuristic methods:

For the moment, two different approaches have been considered, given an instance of a __graph G(V, E)__ and a solution represented as
a __permutation of the different vertices in V__ in a set of size __|V|__:

* The first, to simply choose the different labels as __random integers__ within the available numbers from 1 to |V|, which is,
in itself, efficient, but not enoughly consistent for the methods applied afterwards.

* The second, a __greedy algorithm__ that decides with a __breadth first__ search starting in a first labeled vertex, the labeling 
for the neighbors of the currently visited vertex, based on the __optimality criteria AB(V_i)__ applied to each neighbor following a
first-come-first-served approach. A pseudocode for the described method is provided:

```c++
char[] starting solution = {A,  ...}; // A is assigned to the label 1 by default
int[] non-visited = {2, 3, 4, 5...};  // Rest of the labels

for (auto vertex : GRAPH) {
  for (auto neighbor : vertex.neighborhood) {
    if (!neighbor.isLabeled()) {      // If neighbor does not have a label assigned
      int min_label = 0;    // Position in the array
      for (int i = 1; i < non-visited.size(); i++) {
        if (AB_vertex(vertex.label, non-visited[i]) < AB_vertex(vertex.label, non-visited[min_label])) {  
          //min{f[v_i] - f[n_i]}
          min_label = i;
        }
      }
      
      // label neighbor as min_label
      starting_solution[min_label] = neighbor;
      non_visited.erase(neighbor);     
    }
  }

  if (non-visited.empty()) break;   // optimization
}


```

*DISCLAIMER: actual implementation may vary the data structures utilized in provided examples.
