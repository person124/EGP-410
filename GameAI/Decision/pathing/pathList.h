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

	//Misc Function
	void connect(Node& node);

	//Members
	bool dummy;
	int cost, estimatedCost;
	int x, y;
	int connectX, connectY;
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

		//TODO reorder
		Node& find(Node& node);
		Node& smallest();
		Node& smallestEstimate();
		Node* connections(Node& node);

		Node& getNode(int x, int y);
	private:
		int findPos(Node& node);

		Grid* mGrid;
		std::vector<Node> mNodes;
};

#endif