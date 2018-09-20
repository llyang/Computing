#include <iostream>
using namespace std;

int main() {

  int heads{35};
  int legs{94};

  // cut two legs from everyone
  int legs_remain{legs - heads * 2};

  int rabbits{legs_remain / 2};
  int chickens{heads - rabbits};

  cout << chickens << " chickens and " << rabbits << " rabbits" << '\n';
}
