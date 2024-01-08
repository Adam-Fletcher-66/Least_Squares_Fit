/* Name: Adam_Fletcher
   Date: 05/08/2022
   Purpose: To find the best fit line of a set of data points on a graph
            using the method of least-squares fit. The program will read
            in x and y data points from a file, organize them into arrays,
            apply the least-squares fit to the data, and calculate a slope
            and y-intercept that will be the line of best fit. The program
            will then write out the data points along with the values of 
            the best fit line as a function of the ith x data point to an
            ASCII file declared by the user.
*/

#include <iostream>
#include <fstream>
#include <string>

int main() {

                       // Variable Dictionary
  std::ifstream i_file;                // Instance of input stream
  std::ofstream o_file;                // Instance of output stream
  std::string outfile_name;            // Instance name of output file
  std::string infile_name;             // Instance name of inpute file
  double x, y;                         // Var for data points
  double *xarr=nullptr, *yarr=nullptr; // Var for dynamic arrays
  double m, b;                         // Var for slope and intercept
  double sumx{0.0};                    // Sum of x elem in array
  double sumy{0.0};                    // Sum of y elem in array
  double sum_xsq{0.0};                 // Sum of x squared elem in array
  double sum_xy{0.0};                  // Sum of x*y elem in array
  double f_x;                          // Var for function of y at the ith x pt
  int i;                               // Loop index
  int npts{0};                         // Number of data points
  
  
  
                                       // Prompt user for data file to be read
                                       // and written to
  std::cout << "Enter input filename to be read from." << std::endl;
  std::cout << "Enter output filename to be written to." << std::endl;
  std::cin >> infile_name;             // Read input file name
  std::cin >> outfile_name;            // Read in output file name
  
  i_file.open(infile_name);            // Open the file to be read
  while(!i_file.fail()) {              // Loop while there is no error
      i_file >> x >> y;                // Read in x and y from file
      if(i_file.fail()) {break;}       // Exit loop upon failure
      npts=npts + 1;                   // Increment data counter
  }
  	   
  i_file.close();                      // Close the file
  i_file.clear();                      // Clear the stream so it can be reused

                                       // Allocate space for arrays
  if (xarr == nullptr) {xarr = new double [npts];}
  if (yarr == nullptr) {yarr = new double [npts];}

  i_file.open(infile_name);            // Open the data file again to be read
    for(int i=0; i < npts; i++) {      // Loop over each line of data in file
      i_file >> xarr[i] >> yarr[i];    // Read data into the arrays
    }
       
    i_file.close();                    // Close the file
    i_file.clear();                    // Clear the stream to be reused
    o_file.open(outfile_name);         // Open output file to be written to  
    
    for (i=0; i < npts; i++){          // Loop over data points to calc sums of 
                                       // least squares functions
	   sumx = xarr[i] + sumx;
	   sumy = yarr[i] + sumy;
	   sum_xsq = (xarr[i] * xarr[i]) + sum_xsq;
	   sum_xy = (xarr[i] * yarr[i]) + sum_xy;	
             
	 }
	
    m = ((npts * sum_xy) - (sumx * sumy)) / (npts * sum_xsq - (sumx * sumx));
    b =  sumy - (m * sumx) / npts;     // Calculate the slope, m, and y-int, b

    o_file << "x_i  " << "y_i " << " f(x_i)" << std::endl;

    for (i=0; i < npts; i++){          // Write data points into output file

      f_x = m * xarr[i] + b; 
	    
      o_file << xarr[i] << "    " << yarr[i] << "    " << f_x <<
	       std::endl;
             
	 }

    o_file.close();                    // Close output file
    o_file.clear();

    delete [] xarr;                    // Delete memory for the arrays
    delete [] yarr;

    xarr = nullptr;                    // Nullify the pointers of the arrays
    yarr = nullptr;
    
    return 0;                          // Return a zero error code
}
