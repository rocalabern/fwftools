#include <Rcpp.h>
#include <iostream>
#include <fstream>

using namespace Rcpp;

//' @export
// [[Rcpp::export]]
void fileShowMidLines (
  Rcpp::CharacterVector file,
  long nini = 1, long nend = 100) {
  std::string fileInput = Rcpp::as<std::string>(file);

  Rprintf("File input  : %s\n\n", fileInput.c_str());

	std::ifstream fin;
	fin.open(fileInput.c_str());
	if (!fin.is_open()) {
    Rprintf("Error opening input file.\n");
		return;
	}

	long nLinia = 0;
	std::string sLinia;
  while (!fin.eof() && nLinia<(nini-1)) {
		nLinia++;
		getline(fin, sLinia);
	}
	while (!fin.eof() && nLinia<nend) {
		nLinia++;
		getline(fin, sLinia);
    Rprintf("[Line %d]:%s\n", nLinia, sLinia.c_str());
	}
	fin.close();
	return;
}