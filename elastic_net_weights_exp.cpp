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
NumericMatrix weights_calc_C(NumericVector citiesX, NumericVector citiesY, NumericVector pointsX, NumericVector pointsY, long double exp, double k) {
  
  //make final matrix
  //NumericMatrix weights(citiesX.size(), pointsX.size());
  NumericMatrix weights(citiesX.size(), pointsX.size());
  double k_const = 2*k*k;
  
  for (int j = 0; j < pointsX.size(); j++) {
    //Work through rows second
    
    for  (int i = 0; i < citiesX.size(); i++) {
      //Work through columns first
      weights(i, j) = pow(exp, -(pow(citiesX[i] - pointsX[j], 2) + pow(citiesY[i] - pointsY[j], 2))/k_const);
      
    }
  }
  
  return(weights);
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
weights_calc <- function(inputs, input.points, k) {
  weights <- t(weights_calc_C(inputs[,2], inputs[,3], input.points[,1], input.points[,2], exp(1), k))
  colsums <- apply(weights, 2, sum)
  nonzero <- which(colsums != 0)
  nonzero.weights <- apply(weights[,nonzero], 2, function(x) (x/sum(x)))
  weights[,nonzero] <- nonzero.weights
}

*/
