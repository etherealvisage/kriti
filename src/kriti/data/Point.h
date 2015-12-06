#ifndef KRITI_DATA__POINT_H
#define KRITI_DATA__POINT_H

#include <stdarg.h>
#include <algorithm>

namespace Kriti {
namespace Data {

template<typename Key, int Dimensions>
class Point {
private:
	Key m_coordinates[Dimensions];
public:
	Point() {
		for(int i = 0; i < Dimensions; i ++) {
			m_coordinates[i] = 0;
		}
	}
	Point(Key c1, ...) {
		va_list ap;
		va_start(ap, c1);
		
		m_coordinates[0] = c1;
		
		for(int i = 1; i < Dimensions; i ++) {
			m_coordinates[i] = va_arg(ap, Key);
		}
		
		va_end(ap);
	}
	
	Key coordinate(int which) const { return m_coordinates[which]; }
	void setCoordinate(int which, Key value) { m_coordinates[which] = value; }
};

}  // namespace Data
}  // namespace Kriti

#endif
