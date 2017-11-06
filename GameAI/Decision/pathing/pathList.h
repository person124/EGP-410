#ifndef PATH_LIST_H
#define PATH_LIST_H

#include <vector>

#include <Trackable.h>

class Grid;

struct Node
{
	//Constructors
	Node();
	Node(int xPos, int yPos);
	Node(const Node& node);

	//Members
	bool dummy;
	int cost;
	int x, y;
	Node* connection;
};

bool operator==(Node& left, Node& right);
bool operator!=(Node& left, Node& right);

class PathList : public Trackable
{
	public:
		PathList(Grid* grid);
		~PathList();

		void add(Node node);

		void remove(Node node);

		bool contains(Node& node);

		int size();

		Node& find(Node& node);
		Node& smallest();
		Node* connections(Node& node);
	private:
		int findPos(Node& node);

		//Use a vector for the backend
		Grid* mGrid;
		std::vector<Node> mNodes;
};

#endif