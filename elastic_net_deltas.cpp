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
NumericMatrix delta_yC(NumericMatrix weights, NumericVector citiesX, NumericVector citiesY, NumericVector pointsX, NumericVector pointsY, double alpha, double beta, double k) {
  
  //make final matrix
  NumericMatrix delta_ys(pointsX.size()/3, 2);
  int point_size = pointsX.size()/3;
  
  for (int j = 0; j < pointsX.size()/3; j++) {
    //Work through rows second
    
    //Initiate the point sums as zero
    long double delta_yx = 0;
    long double delta_yy = 0;
    
    for  (int i = 0; i < citiesX.size(); i++) {
      
      //Work through columns first - this will  get the  point-sums and add them up as we go
      delta_yx = delta_yx + alpha*weights(i, j)*(citiesX(i) - pointsX(j));
      delta_yy = delta_yy + alpha*weights(i, j)*(citiesY(i) - pointsY(j));
    }
    
    //Add the point sums to the neighbour effect
    delta_ys(j, 0) = delta_yx + beta*k*(pointsX(j + 1 + point_size) - 2*pointsX(j + point_size) + pointsX(j - 1 + point_size));
    delta_ys(j, 1) = delta_yy + beta*k*(pointsY(j + 1 + point_size) - 2*pointsY(j + point_size) + pointsY(j - 1 + point_size));
    

  }
  
  return(delta_ys);

}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
delta_y <- function(weight.input, input, point.input, alpha.input, beta.input, k.input) {
  delta_yC(t(weight.input), input[,2], input[,3], rep(point.input[,1], 3), rep(point.input[,2], 3), alpha.input, beta.input, k.input)
}
delta_y(weight.mat, input.mat, points, 1, 2, 10)
*/
