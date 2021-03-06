#include "ellipse/ellipse.h"
#include "laser_line_extraction/line.h"

namespace ellipse_extraction
{

Ellipse::Ellipse(const line_extraction::Line &line, const double height, const double width):
  _line(line),
  _height(height + 0.4),
  _width(width),
  _p1(5.0),
  _p2(5.0)
{
  double norm_length = sqrt(pow(_line.getStart()[0] - _line.getEnd()[0], 2) + pow(_line.getStart()[1] - _line.getEnd()[1], 2));
  boost::array<double, 2> norm = {{(_line.getEnd()[0] - _line.getStart()[0]) / norm_length, (_line.getEnd()[1] - _line.getStart()[1]) / norm_length}};
  _start = {{norm[0] * 0.2 + _line.getStart()[0], norm[1] * 0.2 + _line.getStart()[1]}};
  _end = {{norm[0] * (-1) * (0.2 + line.length()) + _line.getStart()[0], norm[1] * (-1) * (0.2 + line.length()) + _line.getStart()[1]}};
  // _p_point = {{norm[0] * (line.length() / 2) + _line.getEnd()[0], norm[1] * (line.length() / 2) + _line.getEnd()[1]}};
  _p_point = {{(_line.getStart()[0] + _line.getEnd()[0])/2, (_line.getStart()[1] + _line.getEnd()[1])/2}};
  // _alpha = acos((_line.getStart()[0] - _line.getEnd()[0])/norm_length);
  _alpha = -atan2(_line.getStart()[1] - _line.getEnd()[1], _line.getStart()[0] - _line.getEnd()[0]);
}

Ellipse::~Ellipse()
{

}

double Ellipse::getAngle() {
  return _line.getAngle();
}

boost::array<double, 2>& Ellipse::getStart() {
  return _start;
}

boost::array<double, 2>& Ellipse::getEnd() {
  return _end;
}

bool Ellipse::onLine(boost::array<double, 2>& point) {
  double test = 1 - (pow(point[0] / _height, _p1) + pow(point[1] / _width, _p2));
  if (test < 0.001) {
    return true;
  }
  return false;
}


double Ellipse::getWidth() {
  return _width;
}

double Ellipse::getHeight() {
  return _height;
}

double Ellipse::getP1() {
  return _p1;
}

double Ellipse::getP2() {
  return _p2;
}

double Ellipse::getAlpha() {
  return _alpha;
}

line_extraction::Line Ellipse::getLine() {
  return _line;
}

boost::array<double, 2>& Ellipse::getPPoint() {
  return _p_point;
}

}
