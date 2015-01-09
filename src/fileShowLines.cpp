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

  Rprintf("File input  : %s\n", fileInput.c_str());
  Rprintf("Max. lines  : %d\n\n", n);

	std::ifstream fin;
	fin.open(fileInput.c_str());
	if (!fin.is_open()) {
    Rprintf("Error opening input file.\n");
		return;
	}

	long nLinia = 0;
	std::string sLinia;
	while (!fin.eof() && nLinia<n) {
		nLinia++;
		getline(fin, sLinia);

    Rprintf("[Line %d]:%s\n", nLinia, sLinia.c_str());
	}
	fin.close();
	return;
}