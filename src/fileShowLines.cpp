#include <Rcpp.h>
#include <iostream>
#include <fstream>

using namespace Rcpp;

//' @export
// [[Rcpp::export]]
void fileShowLines (
  Rcpp::CharacterVector file,
  long n = 100) {
  std::string fileInput = Rcpp::as<std::string>(file);

	std::cout<<"File input  : "<<fileInput<<std::endl;
	std::cout<<"Max. lines  : "<<n<<std::endl;
	std::cout<<std::endl;

	std::ifstream fin;
	fin.open(fileInput.c_str());
	if (!fin.is_open()) {
		std::cout << "Error opening input file."<<std::endl;
		return;
	}

	long nLinia = 0;
	std::string sLinia;
	while (!fin.eof() && nLinia<n) {
		nLinia++;
		getline(fin, sLinia);

		std::cout<<"[Line "<<nLinia<<"]:"<<sLinia<<std::endl;
	}
	fin.close();
	return;
}