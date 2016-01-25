#include <map>

#include "Colour.h"
#include "../StreamAsString.h"

namespace Kriti {
namespace Math {

Colour::Colour(std::string description) {
    // HTML colour value?
    if(description[0] == '#') {
        std::map<char, int> hexmap{
            {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},
            {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
            {'8', 8}, {'9', 9}, {'a', 10}, {'b', 11},
            {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
        };
        int r = 0, g = 0, b = 0, a = 255;
        if(description.length() == 4 || description.length() == 5) {
            r = hexmap[description[1]]*17;
            g = hexmap[description[2]]*17;
            b = hexmap[description[3]]*17;
            if(description.length() == 5) {
                a = hexmap[description[4]]*17;
            }
            else {
                a = 255;
            }
        }
        else if(description.length() == 7 || description.length() == 9) {
            r = hexmap[description[1]]*16 + hexmap[description[2]];
            g = hexmap[description[3]]*16 + hexmap[description[4]];
            b = hexmap[description[5]]*16 + hexmap[description[6]];
            if(description.length() == 9) {
                a = hexmap[description[7]]*16 + hexmap[description[8]];
            }
            else {
                a = 255;
            }
            
        }
        m_r = r/255.0;
        m_g = g/255.0;
        m_b = b/255.0;
        m_a = a/255.0;
    }
}

std::string Colour::toString() const {
    return StreamAsString() << "(" << m_r << "," << m_g << "," << m_b << ","
        << m_a << ")";
}

}  // namespace Math
}  // namespace Kriti
