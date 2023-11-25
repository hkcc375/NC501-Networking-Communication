#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <utility>
using namespace std;

class LinkStateAlgorithm
{
      public:
	void build_topology( const string& file_name )
	{
		// Read from the testfile each link in the form (source, destination, cost) and build the topology
		// Implementation for reading the testfile and building the topology
		string file_path = file_name;
		ifstream input_file( file_path );
		if( !input_file )
			cout << "Input File could not be opened. \n";
		else
		{
			cout << "File was succesfully opened. \n";
			string source, destination;
			int cost;
			while( input_file >> source >> destination >> cost ) { add_link( source, destination, cost ); }

			// Printing the topology of the network
			unordered_map< int, vector< pair< int, int > > >::iterator entry;
			for( entry = adjacencyList.begin(); entry != adjacencyList.end(); entry++ )
			{
				cout << "Vertex " << entry->first << ": ";
				pair< int, int > neighbor;
				for( auto neighbor : entry->second )
				{
					cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
				}
				cout << endl;
			}
		}
		input_file.close();
	}

	void add_link( const string& source, const string& destination, int cost )
	{
		// Used by the above function to add a link
		// Implementation for adding a link to the topology
		int source_id      = getNodeId( source );
		int destination_id = getNodeId( destination );
		adjacencyList[source_id].push_back( make_pair( destination_id, cost ) );
		adjacencyList[destination_id].push_back( make_pair( source_id, cost ) );
	}

	void calculate_shortest_path( const string& source, const string& destination )
	{
		// Find the shortest path from A to I. For the given testcase, the output must be A -> B -> D -> F -> H
		// -> I Implementation for calculating the shortest path
		int source_id      = getNodeId( source );
		int destination_id = getNodeId( destination );

		unordered_map< int, int > predecessor;
		unordered_map< int, int > distance; // Map to store the distance from source to each node
		priority_queue< pair< int, int >, vector< pair< int, int > >, greater< pair< int, int > > > pq;

		// Initialize distances to infinity
		for( auto& entry : adjacencyList ) { distance[entry.first] = INT_MAX; }

		distance[source_id] = 0;
		pq.push( make_pair( 0, source_id ) );

		while( !pq.empty() )
		{
			int u = pq.top().second;
			pq.pop();

			for( const auto& [v, weight] : adjacencyList[u] )
			{
				if( distance[v] > distance[u] + weight )
				{
					distance[v]    = distance[u] + weight;
					predecessor[v] = u;
					pq.push( make_pair( distance[v], v ) );
				}
			}
		}

		// Reconstruct the shortest path from source to destination
		stack< int > path;
		int current = destination_id;
		while( current != source_id )
		{
			path.push( current );
			current = predecessor[current];
		}
		path.push( source_id );

		cout << "Shortest path from " << source << " to " << destination << ": ";
		while( !path.empty() )
		{
			cout << getNodeLabel( path.top() ) << " ";
			path.pop();
		}
		cout << endl;
	}

      private:
	// Network Topology
	unordered_map< int, vector< pair< int, int > > > adjacencyList;

	// Store the mapping between a vertex label and a vertex id
	unordered_map< string, int > vertexIds;

	// Gets the node id for a given node
	int getNodeId( const string& node )
	{
		unordered_map< string, int >::iterator it;
		it = vertexIds.find( node );
		if( it != vertexIds.end() ) { return it->second; }
		else
		{
			int newId       = vertexIds.size();
			vertexIds[node] = newId;
			return newId;
		}
	}

	// Gets the node label for a given node ID
	string getNodeLabel( int nodeId )
	{
		for( auto& entry : vertexIds )
		{
			if( entry.second == nodeId ) { return entry.first; }
		}
		return "The given node was not found \n"; // Handle error case if nodeId is not found
	}
};

int main( int argc, char* argv[] )
{
	if( argc != 2 )
		perror( "Pass in the file name as a command line argument. \n" );
	else
	{
		LinkStateAlgorithm linkState;
		linkState.build_topology( argv[1] );
		linkState.calculate_shortest_path( "A", "I" );
	}
}