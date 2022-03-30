#include "Util.h"
Pos Util::fromVectortoPos(Vector2D v) {
	Pos p;
	p.x = (long) v.getX() * Util::n;
	p.y = (long) v.getY() * Util::n;
	return p;
}