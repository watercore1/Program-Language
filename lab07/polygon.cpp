#include "polygon.h"

bool Polygon::CoverPoint(const Point& p)const
{
    //是否在外环内部
    if(Ring::CoverPoint(p))
    {
        // && 运算符是短路求值
        // 是否在内环的内部
        if(has_inner_ && inner_ring_.CoverPoint(p))
        {
            return false;
        }
        else return true;
    }
    else return false;
}

string Polygon::ToString() const{
    string temp = "outer=" + Ring::ToString() + ", inner=" + inner_ring_.ToString();
    return temp;
}

ofstream &operator<<(ofstream &ofs, const Polygon &p) {
  ofs << "polygon " << p.id_ << " " << p.ToString() << ", name=" << p.name_
      << ", length=" << p.length_ << ", area=" << p.area_ << endl;
  return ofs;
}

