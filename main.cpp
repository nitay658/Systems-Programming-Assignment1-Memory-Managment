#include <iostream>
#include <fstream>
#include "Session.h"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    Session sess(argv[1]);
    sess.simulate();
    /*
    vector<vector<int>> a = {{1,2,3},{5,6,7}};
    cout << &a[0] <<"\n";
    vector<vector<int>> b =std::move(a);
    cout << &b[0];
    for(int i=0;i<b.size();i++)
    {
        for(int j=0;j<b[i].size();j++)
            cout << b[i][j] << " ";
        cout << "\n";
    }
    cout << &a[0];
    */
    std::vector<std::vector<int>> a ={{1,2,3},{4,5,6}};
    cout << a[0][0];
    ifstream i("config1.json");
    json j;
    j<< i;
    for(auto elem :j["agents"])
    {
        cout<<elem;
    }
    return 0;
}
