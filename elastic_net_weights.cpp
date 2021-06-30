#include <Rcpp.h>
using namespace Rcpp;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]
NumericMatrix weights_calc_C(IntegerVector citiesX, IntegerVector citiesY, NumericVector pointsX, NumericVector pointsY) {
  
  //make final matrix
  //NumericMatrix weights(citiesX.size(), pointsX.size());
  NumericMatrix weights(citiesX.size(), pointsX.size());
  
  for (int i = 0; i < citiesX.size(); i++) {
    //Work through columns second
    
    for (int j = 0; j < pointsX.size(); j++) {
      //Work through rows first
      weights(i, j) = sqrt( pow(citiesX[i] - pointsX[j], 2) + pow(citiesY[i] - pointsY[j], 2));
      
    }
  }

  return(weights);
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
exp(-weights_calc_C(input.mat[,2], input.mat[,3], points[,1], points[,2])/(2*0.5^2))


*/
