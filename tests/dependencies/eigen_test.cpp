#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
 
int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);

  MatrixXd propagator(6, 6);
  // std::cout << propagator << "\n" << propagator.determinant() << std::endl;

  Eigen::Vector3d u(1, 2, 3);
  Eigen::Vector3d v(4, 5, 6);

  std::cout << "dot product\n" << u.dot(v) << std::endl;
  std::cout << "cross product\n" << u.cross(v) << std::endl;
  std::cout << "outer product\n" << u * v.transpose() << std::endl;
  std::cout << "inner (dot) product\n" << u.transpose() * v << std::endl;
  
  return 0;
}
