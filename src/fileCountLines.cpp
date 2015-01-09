#include <Rcpp.h>
#include <iostream>
#include <fstream>

using namespace Rcpp;

//' @export
// [[Rcpp::export]]
int fileCountLines (Rcpp::CharacterVector file) {
  std::string fileInput = Rcpp::as<std::string>(file);

  std::cout<<"File input  : "<<fileInput<<std::endl;
	std::cout<<std::endl;

	std::ifstream fin;
	fin.open(fileInput.c_str());
	if (!fin.is_open()) {
		std::cout << "Error opening input file."<<std::endl;
		return 0;
	}

	long nLinia = 0;
	std::string sLinia;
	while (!fin.eof()) {
		nLinia++;
		getline(fin, sLinia);
	}
	fin.close();

  std::cout<<"Total lines: "<<nLinia<<std::endl;
	return nLinia;
}