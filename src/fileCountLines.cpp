#include <Rcpp.h>
#include <iostream>
#include <fstream>

using namespace Rcpp;

//' @export
// [[Rcpp::export]]
int fileCountLines (Rcpp::CharacterVector file) {
  std::string fileInput = Rcpp::as<std::string>(file);

  Rprintf("File input  : %s\n\n", fileInput.c_str());

	std::ifstream fin;
	fin.open(fileInput.c_str());
	if (!fin.is_open()) {
		Rprintf("Error opening input file.\n");
		return 0;
	}

	long nLinia = 0;
	std::string sLinia;
	while (!fin.eof()) {
		nLinia++;
		getline(fin, sLinia);
	}
	fin.close();

  Rprintf("Total lines: %d\n", nLinia);
	return nLinia;
}