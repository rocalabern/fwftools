#include <Rcpp.h>
#include <ctime>

using namespace Rcpp;

//' @export
// [[Rcpp::export]]
Rcpp::IntegerVector cppTest (
  Rcpp::IntegerVector begin,
  Rcpp::IntegerVector end
  ) {
  const clock_t begin_time = clock();

  Rcpp::IntegerVector start = Rcpp::IntegerVector(begin.size());
  Rcpp::IntegerVector length = Rcpp::IntegerVector(begin.size());

  for (int i=0;i<begin.size();i++) {
    start[i]  = begin[i] - 1;
    length[i] = end[i] - begin[i] + 1;
  }

  for (int i=0;i<start.size();i++) {
    std::cout<<" "<<start[i];
  }
  std::cout<<std::endl;

  for (int i=0;i<length.size();i++) {
    std::cout<<" "<<length[i];
  }
  std::cout<<std::endl;

  Rprintf("Time used  : %f\n", float( clock () - begin_time ) /  CLOCKS_PER_SEC);
	return length;
}