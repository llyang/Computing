#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  int sides{6};     // 从六边形开始
  double edge{1.0}; // 六边形的边长为1
  for (int i = 0; i < 20; ++i) {
    // 设n边形的边长为edge，计算2n边形的边长
    const double new_edge{sqrt(2 * (1 - sqrt(1 - edge * edge / 4.0)))};

    sides *= 2;                        // 2n边形
    const double area{(edge / 2) / 2}; // 2n边形中每个小三角形的面积
    double pi{area * double(sides)};   // 用2n边形面积来估计pi

    cout << setw(10) << setprecision(16) << sides << '\t' << pi << '\n';

    edge = new_edge;
  }
}

