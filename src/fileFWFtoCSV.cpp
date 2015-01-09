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
  Rcpp::CharacterVector header1 = Rcpp::CharacterVector::create("a"),
  Rcpp::CharacterVector header2 = Rcpp::CharacterVector::create("a"),
  long skip = 0,
  long limit = 0,
  Rcpp::CharacterVector mode = Rcpp::CharacterVector::create("a")
  ) {
  std::string strFileInput = Rcpp::as<std::string>(inputFile);
  std::string strFileOutput = Rcpp::as<std::string>(outputFile);
  std::string strHeader1 = Rcpp::as<std::string>(header1);
  std::string strHeader2 = Rcpp::as<std::string>(header2);
  std::string strMode = Rcpp::as<std::string>(mode);

  std::cout<<"File input  : "<<strFileInput<<std::endl;
  std::cout<<"File output : "<<strFileOutput<<std::endl;
	std::cout<<"Skip lines  : "<<skip<<std::endl;
  std::cout<<"Max. lines  : "<<limit<<std::endl;
	std::cout<<std::endl;

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
  if (strMode.compare("a")) {
    fout.open(strFileOutput.c_str(), std::ios::app);
  } else {
    fout.open(strFileOutput.c_str(), std::ios::out | std::ios::trunc);
  }

	if (!fin.is_open()) {
		std::cout << "Error opening input file."<<std::endl;
  	if (fout.is_open()) {
			fout.close();
		}
		return;
	}
  if (!fout.is_open()) {
	  std::cout << "Error opening output file."<<std::endl;
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
		std::cout<<"[Line "<<nLinia<<"]:"<<sLinia<<std::endl;
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
			std::cout<<"Error ("<<nLinia<<") :"<<sLinia<<std::endl;
		}

    if ( nLinia % 50000 == 0 ) {
        std::cout<<"Lines processed: "<<nLinia<<std::endl;
    }
	}
	fout.close();
	fin.close();

  std::cout<<std::endl;
  std::cout<<"Total lines processed: "<<nLinia<<std::endl;
  std::cout<<"Time used: "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC<<std::endl;
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