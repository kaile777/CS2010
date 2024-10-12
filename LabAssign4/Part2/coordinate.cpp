
#include <iostream>
#include <vector>

using namespace std;

using COORD = vector<int>;
using POINTS = vector<COORD>;
int main()
{
    POINTS p;
    int x,y;
    while ( 0 != x) {
      cout<<"Enter x and y coordinates : ";
      cin >> x >> y;
      p.push_back(COORD{x,y});
    }
    for (auto i : p) {
        if (i == COORD{0,0})
            cout << i[0] << "," << i[1] << " ";
    }
    return 0;
}
