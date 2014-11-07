#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <fstream>

class State {
  size_t _node;
  double _dist;
public:
  State( size_t aNode, double aDist ) : _node{aNode}, _dist{aDist} {}
  inline size_t node() const { return _node; }
  inline double dist() const { return _dist; }
    inline void print() const { std::cout << "(" << _node << ", " << _dist << ")\n"; }
};


class AdjacencyList {
  std::vector< std::vector<State> > _vert;
  AdjacencyList() = delete;
public:
  AdjacencyList( std::istream &input );
  inline size_t size() const { return _vert.size(); }
  inline const std::vector<State>& vert( size_t node ) const { return _vert[node]; }
  void print();
};

class CompareState {
public:
    bool operator() ( State& state_1, State& state_2 ){
        return state_1.dist() > state_2.dist();
    }
};

AdjacencyList::AdjacencyList ( std::istream &input ) {
    int node_count, n;
    input >> node_count >> n;
    for ( int i = 0; i < node_count ; i ++ ) {
        std::vector< State > v;
        _vert.push_back(v);
    }
    size_t first_node, second_node;
    double dist;
    for ( int i = 0; i < n ; i ++ ) {
        input >> first_node >> second_node >> dist;
        
        // To increase the speed, I decided to put the states in both nodes.
        State state1(second_node, dist);
        _vert[first_node].push_back(state1);
        
        State state2(first_node, dist);
        _vert[second_node].push_back(state2);
        
    }
}

void AdjacencyList::print() {
    size_t out_size = _vert.size();
    for ( int i = 0 ; i < out_size ; i ++ ) {
        std::vector<State> states = _vert[i];
        size_t in_size = states.size();
        std::cout << "adj[" << i << "]: ";
        for ( int j = 0 ; j < in_size ; j ++ ) {
            std::cout << "(" << states[j].node() << " " << states[j].dist() << ") ";
        }
        std::cout << "\n";
    }
}


double find_mst( AdjacencyList *adj ){
    // Initializtions.
    double weight = 0;
    size_t size = adj->size();
    std::set< size_t > included_nodes;
    std::priority_queue< State, std::vector< State >, CompareState > edges;
    size_t current_node = 0;
    while ( included_nodes.size() != size ) {
        included_nodes.insert( current_node );
        std::vector< State > adjs = adj->vert( current_node );
        for ( auto state: adjs ) {
            edges.push( state );
        }
        while ( !edges.empty() ) {
            State min_state = edges.top();
            edges.pop();
            if ( included_nodes.count( min_state.node()) == 0) {
                current_node = min_state.node();
                weight += min_state.dist();
                break;
            }
        }
    }
    
    return weight;
}

int main(int argc, const char * argv[]){
    if ( argc == 1 ) {
        perror( "Usage: ./Mst [test file name]\n" );
        exit( EXIT_FAILURE );
    }
    std::ifstream file;
    std::string filename = argv[1];
    file.open( filename );
    std::string line;
    if ( file.is_open() ) {
        AdjacencyList adj ( file );
        std::cout.precision(8);
        std::cout.setf( std::ios::fixed, std:: ios::floatfield );
        std::cout << find_mst( &adj ) << "\n";
        file.close();
    } else {
        perror( "File not found.\n" );
        exit( EXIT_FAILURE );
    }
	return 0;
}
