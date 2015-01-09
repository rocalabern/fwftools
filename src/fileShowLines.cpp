#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;

//' @export
// [[Rcpp::export]]
int fileShowLines (
  Rcpp::CharacterVector rfileInput,
  Rcpp::NumericVector rnLimitLines = Rcpp::NumericVector::create(100)) {
  string fileInput = Rcpp::as<std::string>(rfileInput);
  long nLimitLines = rnLimitLines[0];

	cout<<"File input  : "<<fileInput<<endl;
	cout<<"Lines  = "<<nLimitLines<<endl;
	cout<<endl;

	ifstream fin;
	fin.open(fileInput.c_str());
	if (!fin.is_open()) {
		cout << "Error opening input file."<<endl;
		return 0;
	}

	long nLinia = 0;
	string sLinia;
	while (!fin.eof() && nLinia<nLimitLines) {
		nLinia++;
		getline(fin, sLinia);

		cout<<"(Line "<<nLinia<<") :"<<sLinia<<endl;
	}
	fin.close();
	return 0;
}