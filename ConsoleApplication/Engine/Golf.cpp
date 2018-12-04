#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum FloorType {
	GRASS,
	HOLE,
	WATER,
	BALL
};

FloorType getType(char& t) {
	if (t == '.') return GRASS;
	if (t == 'H') return HOLE;
	if (t == 'X') return WATER;
	return BALL;
}

char toChar(FloorType& type) {
	switch (type) {
	case GRASS: return '.';
	case HOLE: return 'H';
	case WATER: return 'X';
	case BALL: return 'B';
	default: return '?';
	}
}

// return a <= x <= b or b <= x <= a
bool isPointBetween(int x, int a, int b) {
	return x >= a && x <= b
		|| x >= b && x <= a;
}

class Point {
private:
	int m_x;
	int m_y;

public:
	Point(int x, int y) : m_x(x), m_y(y) {}

	int getX() { return m_x; }

	int getY() { return m_y; }

	bool operator== (const Point& point) {
		return m_x == point.m_x && m_y == point.m_y;
	}

	bool isBetween(const Point& pointA, const Point& pointB) {
		if (m_x == pointA.m_x && m_x == pointB.m_x) {
			return isPointBetween(m_y, pointA.m_y, pointB.m_y);
		}

		if (m_y == pointA.m_y && m_y == pointB.m_y) {
			return isPointBetween(m_x, pointA.m_x, pointB.m_x);
		}

		return false;
	}

	friend ostream& operator<< (ostream& os, const Point& point) {
		os << "(" << point.m_x << "," << point.m_y << ")";
		return os;
	}
};

class Field {
private:
	int m_width;
	int m_height;
	FloorType** m_type;

public:
	Field(int width, int height) : m_width(width), m_height(height) {
		m_type = new FloorType*[m_height];
		for (int i = 0; i < m_height; i++) {
			m_type[i] = new FloorType[m_width];
		}
	}

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	void set(int x, int y, FloorType type) {
		if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
			m_type[y][x] = type;
			return;
		}

		throw "SET";
	}

	FloorType& get(Point& point) const {
		int x = point.getX();
		int y = point.getY();
		if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
			return m_type[y][x];
		}

		throw "GET";
	}

	friend ostream& operator<< (ostream& os, const Field& field) {
		for (int i = 0; i < field.m_height; i++) {
			for (int j = 0; j < field.m_width; j++) {
				os << toChar(field.m_type[i][j]) << " ";
			}
			os << endl;
		}
		return os;
	}

	~Field() {
		for (int i = 0; i < m_height; i++) {
			delete[] m_type[i];
		}

		delete[] m_type;
	}
};

class RoutePath : public vector<Point> {
public:
	bool contains(Point& point) {
		for (Point p : *this) {
			if (p == point) {
				return true;
			}
		}

		return false;
	}

	bool isOnPath(Point& point) {
		if (size() == 0) {
			return false;
		}

		Point* previous = &at(0);
		Point* next;
		for (int k = 1; k < size(); k++) {
			next = &at(k);
			if (point.isBetween(*previous, *next)) {
				return true;
			}

			previous = next;
		}

		return false;
	}

	bool hasIntersection(vector<RoutePath>& paths) {
		for (RoutePath route : paths) {
			if (hasIntersection(route)) {
				return true;
			}
		}

		return false;
	}

	friend ostream& operator<< (ostream& os, const RoutePath& route) {
		os << "Route";
		for (Point p : route) {
			os << " " << p;
		}

		return os;
	}

private:
	bool hasIntersection(RoutePath& route) {
		if (this->size() == 0 || route.size() == 0) {
			return false;
		}

		if (this->size() == 1) {
			return route.isOnPath(this->at(0));
		}

		if (route.size() == 1) {
			return this->isOnPath(route.at(0));
		}

		// Comparing each segments
		Point* previousThis = &this->at(0);
		for (int k = 1; k < this->size(); k++) {
			Point* nextThis = &this->at(k);

			Point* previousOther = &route.at(0);
			for (int l = 1; l < route.size(); l++) {
				Point* nextOther = &route.at(l);

				if (segmentsIntersect(previousThis, nextThis, previousOther, nextOther)) {
					return true;
				}

				previousOther = nextOther;
			}

			previousThis = nextThis;
		}

		return false;
	}

	// Do [pA1, pA2] and [pB1, pB2] intersect
	bool segmentsIntersect(Point* pA1, Point* pA2, Point* pB1, Point* pB2) {
		bool isHorizontalA = pA1->getY() == pA2->getY();
		bool isHorizontalB = pB1->getY() == pB2->getY();

		if (isHorizontalA == isHorizontalB) {
			// PARALLEL
			if (isHorizontalA) {
				return pA1->getY() == pB1->getY()
					&& segmentsIntersect(pA1->getX(), pA2->getX(), pB1->getX(), pB2->getX());
			}
			else {
				return pA1->getX() == pB1->getX()
					&& segmentsIntersect(pA1->getY(), pA2->getY(), pB1->getY(), pB2->getY());
			}
		}
		else {
			// PERPENDICULAR
			if (isHorizontalA) {
				return isPointBetween(pA1->getY(), pB1->getY(), pB2->getY())
					&& isPointBetween(pB1->getX(), pA1->getX(), pA2->getX());
			}
			else {
				return isPointBetween(pA1->getX(), pB1->getX(), pB2->getX())
					&& isPointBetween(pB1->getY(), pA1->getY(), pA2->getY());
			}
		}
	}

	// Do [pA1, pA2] and [pB1, pB2] intersect
	bool segmentsIntersect(int pA1, int pA2, int pB1, int pB2) {
		return max(pA1, pA2) >= min(pB1, pB2)
			&& max(pB1, pB2) >= min(pA1, pA2);
	}
};

class Ball {
private:
	Point m_position;
	int m_number_of_shots;
	vector<RoutePath> m_routes;

public:
	Ball(Point position, int shots) : m_position(position), m_number_of_shots(shots) {}

	vector<RoutePath>& getRoutes() { return m_routes; }

	const Point& getStartingPosition() { return m_position; }
	
	void computeRoutes(const Field& field) {
		m_routes.clear();
		RoutePath visited;
		visited.push_back(m_position);
		exploreRoutes(field, visited, m_number_of_shots);
	}

	friend ostream& operator<< (ostream& os, const Ball& ball) {
		os << "Ball" << ball.m_position << " = " << ball.m_number_of_shots;
		return os;
	}

private:
	void exploreRoutes(const Field& field, RoutePath& visited, int number_shots) {
		Point current_position = visited.back();
		if (field.get(current_position) == HOLE) {
			m_routes.push_back(visited);
			return;
		}

		if (number_shots == 0) {
			return;
		}

		int next_shots = number_shots - 1;
		int x = current_position.getX();
		int y = current_position.getY();
		int nx, ny;

		// Up
		ny = y - number_shots;
		if (ny >= 0) {
			Point next_point(x, ny);
			exploreNextPoint(field, visited, next_shots, next_point);
		}

		// Down
		ny = y + number_shots;
		if (ny < field.getHeight()) {
			Point next_point(x, ny);
			exploreNextPoint(field, visited, next_shots, next_point);
		}

		// Left
		nx = x - number_shots;
		if (nx >= 0) {
			Point next_point(nx, y);
			exploreNextPoint(field, visited, next_shots, next_point);
		}

		// Right
		nx = x + number_shots;
		if (nx < field.getWidth()) {
			Point next_point(nx, y);
			exploreNextPoint(field, visited, next_shots, next_point);
		}
	}

	void exploreNextPoint(
		const Field& field,
		RoutePath& visited,
		const int& next_shots,
		Point& next_point)
	{
		FloorType point_type = field.get(next_point);
		if (point_type == WATER
			|| point_type == BALL
			|| visited.isOnPath(next_point)) {
			return;
		}

		visited.push_back(next_point);
		exploreRoutes(field, visited, next_shots);
		visited.pop_back();
	}
};

bool lessRoutesFirst(Ball* a, Ball* b) {
	return a->getRoutes().size() < b->getRoutes().size();
}

class Solution {
private:
	Field m_field;
	vector<Ball*> m_balls;

public:
	Solution(Field& field, vector<Ball*>& balls): m_field(field), m_balls(balls) {}

	string* getSolution() {
		// Computing viable routes for each ball
		for (Ball* ball : m_balls) {
			ball->computeRoutes(m_field);
		}

		// Sorting balls according to the number of possible route
		sort(m_balls.begin(), m_balls.end(), lessRoutesFirst);

		// Keeping track of the current selected route for each ball
		vector<RoutePath> selectedRoutes = getMatchingRoutes();

		// Transforming routes to output
		return transformToOutput(selectedRoutes);
	}

private:
	vector<RoutePath> getMatchingRoutes() {
		vector<RoutePath> selectedRoutes;
		if (!exploreMatchingRoutes(selectedRoutes)) {
			throw "ROUTE";
		}

		return selectedRoutes;
	}

	bool exploreMatchingRoutes(vector<RoutePath>& previousPaths) {
		if (previousPaths.size() == m_balls.size()) {
			return true;
		}

		Ball* ball_ptr = m_balls.at(previousPaths.size());
		for (RoutePath path : ball_ptr->getRoutes()) {
			// path compatible if intersection is empty
			if (path.hasIntersection(previousPaths)) {
				continue;
			}

			previousPaths.push_back(path);
			if (exploreMatchingRoutes(previousPaths)) {
				// Found a match
				return true;
			}
			previousPaths.pop_back();
		}

		return false;
	}

	string* transformToOutput(vector<RoutePath>& selectedRoutes) {
		string* output = new string[m_field.getHeight()];
		for (int i = 0; i < m_field.getHeight(); i++) {
			output[i].assign(m_field.getWidth(), '.');
		}

		for (RoutePath route : selectedRoutes) {
			int x = route[0].getX();
			int y = route[0].getY();
			for (int k = 1; k < route.size(); k++) {
				int nx = route[k].getX();
				int ny = route[k].getY();

				int diffX = nx - x;
				int diffY = ny - y;

				if ((diffX == 0) == (diffY == 0)) {
					throw "MOVE";
				}

				for (int j = x; j < nx; j++) {
					output[y][j] = '>';
				}

				for (int j = x; j > nx; j--) {
					output[y][j] = '<';
				}

				for (int i = y; i < ny; i++) {
					output[i][x] = 'v';
				}

				for (int i = y; i > ny; i--) {
					output[i][x] = '^';
				}

				x = nx;
				y = ny;
			}
		}

		return output;
	}
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
	int width;
	int height;
	cin >> width >> height; cin.ignore();

	Field field(width, height);
	vector <Ball*> balls;

	for (int i = 0; i < height; i++) {
		string row;
		cin >> row; cin.ignore();
		for (int j = 0; j < width; j++) {
			char field_type_char = row.at(j);
			FloorType field_type_enum = getType(field_type_char);
			if (field_type_enum == BALL) {
				int shots = field_type_char - 48;
				balls.push_back(new Ball(Point(j, i), shots));
			}

			field.set(j, i, field_type_enum);
		}
	}

	Solution solution(field, balls);

	string* output = solution.getSolution();

	for (int i = 0; i < height; i++) {
		cout << output[i] << endl;
	}
}