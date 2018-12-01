//=====================================//
//               					   //
//				  MATH 				   //
//									   //
//=====================================//

//--------------------------------------//

struct Point
{
	float x;
	float y;
};

struct Direction
{
	int x; 
	int y;
};

//--------------------------------------//

// Calcula a distância entre dois pontos.
float points_distance (Point * p1, Point * p2);