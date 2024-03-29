#include <Geometry/io/CLocalizer.h>

#include <string>
#include <clocale>

using namespace std;

namespace GEOMETRY {
namespace io {

CLocalizer::CLocalizer()
{
    char* p = std::setlocale(LC_NUMERIC, NULL);
    if (0 != p)
    {
        saved_locale = p;
    }
    std::setlocale(LC_NUMERIC, "C");
}

CLocalizer::~CLocalizer()
{
    std::setlocale(LC_NUMERIC, saved_locale.c_str());
}

} // namespace GEOMETRY.io
} // namespace GEOMETRY

