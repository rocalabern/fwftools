#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace Rcpp;

static inline std::string &ltrim(std::string &s);
static inline std::string &rtrim(std::string &s);
static inline std::string &trim(std::string &s);

//' @export
// [[Rcpp::export]]
void fileFWFtoCSV (
  Rcpp::CharacterVector inputFile,
  Rcpp::CharacterVector outputFile,
  Rcpp::IntegerVector begin,
  Rcpp::IntegerVector end,
  Rcpp::CharacterVector header1 = Rcpp::CharacterVector::create(""),
  Rcpp::CharacterVector header2 = Rcpp::CharacterVector::create(""),
  long skip = 0,
  long limit = 0,
  Rcpp::CharacterVector mode = Rcpp::CharacterVector::create("n")
  ) {
  std::string strFileInput = Rcpp::as<std::string>(inputFile);
  std::string strFileOutput = Rcpp::as<std::string>(outputFile);
  std::string strHeader1 = Rcpp::as<std::string>(header1);
  std::string strHeader2 = Rcpp::as<std::string>(header2);
  std::string strMode = Rcpp::as<std::string>(mode);

  Rprintf("File input  : %s\n", strFileInput.c_str());
  Rprintf("File output: %s\n", strFileOutput.c_str());
  Rprintf("Skip lines  : %d\n", skip);
  Rprintf("Max. lines  : %d\n", limit);

  Rcpp::IntegerVector start = Rcpp::IntegerVector(begin.size());
  Rcpp::IntegerVector length = Rcpp::IntegerVector(begin.size());

  for (int i=0;i<begin.size();i++) {
    start[i]  = begin[i] - 1;
    length[i] = end[i] - begin[i] + 1;
  }

  const clock_t begin_time = clock();

	std::ifstream fin;
  std::ofstream fout;
  fin.open(strFileInput.c_str());
  if (strMode.compare("a")==0) {
    Rprintf("Append      : yes (%s)\n\n", strMode.c_str());
    fout.open(strFileOutput.c_str(), std::ios::app);
  } else {
    Rprintf("Append      : no (%s)\n\n", strMode.c_str());
    fout.open(strFileOutput.c_str(), std::ios::out | std::ios::trunc);
  }

	if (!fin.is_open()) {
		Rprintf("Error opening input file.\n");
  	if (fout.is_open()) {
			fout.close();
		}
		return;
	}
  if (!fout.is_open()) {
	  Rprintf("Error opening output file.\n");
		if (fin.is_open()) {
			fin.close();
		}
		return;
	}

	long nLinia = 0;
	std::string sLinia;
  while (!fin.eof() && nLinia<skip) {
		nLinia++;
		getline(fin, sLinia);
    Rprintf("[Line %d]:%s\n", nLinia, sLinia.c_str());
	}

	while (!fin.eof() && (limit<1 || nLinia<limit)) {
  	nLinia++;
		getline(fin, sLinia);

		try {
			if (sLinia.length()>0
			&& sLinia.find("rows selected.") == std::string::npos
			&& sLinia.find("SQL> SQL> spool off;") == std::string::npos
			&& sLinia.compare(strHeader1)!=0
			&& sLinia.compare(strHeader2)!=0)
			{
        bool first = true;
				std::string substring;

        for (int i=0;i<start.size();i++) {
          if (first) {
    				substring = sLinia.substr(start[i],length[i]);
    				substring = trim(substring);
    				fout<<substring;
            first = false;
          } else {
    				substring = sLinia.substr(start[i],length[i]);
    				substring = trim(substring);
    				fout<<";"<<substring;
          }
        }

				fout<<std::endl;
			}
		} catch(const std::exception& e) {
      Rprintf("Error (%d) : %s\n", nLinia, sLinia.c_str());
		}

    if ( nLinia % 50000 == 0 ) {
      Rprintf("Lines processed: %d\n", nLinia);
    }
	}
	fout.close();
	fin.close();

  Rprintf("\nTotal lines: %d\n", nLinia);
  Rprintf("Time used  : %f seconds\n", float( clock () - begin_time ) /  CLOCKS_PER_SEC);
	return;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}