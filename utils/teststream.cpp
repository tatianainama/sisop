#include "engine.h"

int main(){

	std::stringstream ss;
	std::stringstream s2;
	std::string segment;
	std::string dat;
	int x,y,status;
	 ss << "1,200,400|0,30,60|1,87,39";

	for(int i=0;i<3;i++){
		std::getline(ss, segment, '|');

		std::cout << segment;
		std::cout << "\n";

		s2 << segment;
		std::getline(s2, dat, ',');
		std::stringstream ( dat ) >> status;
		std::cout << dat;
		std::cout << "\n";

		std::getline(s2, dat, ',');
		std::stringstream ( dat ) >> x;
		std::cout << dat;
		std::cout << "\n";

		std::getline(s2, dat, ',');
		std::stringstream ( dat ) >> y;
		std::cout << dat;
		std::cout << "\n";


		std::cout << "Datos Finales:: " << status << "," << x << "," << y << "\n";

		s2.str("");
		s2.clear();
		//ss.str(std::string());
	}

}