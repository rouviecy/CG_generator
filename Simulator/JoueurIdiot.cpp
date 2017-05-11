#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(){
	while(true){
		int nbShips, nbEntities;
		cin >> nbShips; cin.ignore();
		cin >> nbEntities; cin.ignore();
		for(int i = 0; i < nbEntities; i++){
			int id, x, y, arg1, arg2, arg3, arg4;
			string entityType;
			cin >> id >> entityType >> x >> y >> arg1 >> arg2 >> arg3 >> arg4; cin.ignore();
		}
		for(int i = 0; i < nbEntities; i++){
			cout << "MOVE 5 5" << endl;
		}
	}
}
