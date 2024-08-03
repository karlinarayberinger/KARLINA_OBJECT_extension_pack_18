  /**
 * file: reimann_sum.cpp
 * type: plain-text
 * date: 02_AUGUST_2024
 * author: karbytes
 * license: PUBLIC_DOMAIN
 */

/** preprocessing directives */
#include <iostream> // standard input (std::cin), standard output (std::cout)
#include <fstream> // file input, file output, file open, file close
#include <cmath> // sine function (sin(x)), cosine function (cos(x)), square root function (sqrt(x))
#include <functional> // define custom Function type
#define MINIMUM_a -999 // constant which represents the minimum a value
#define MAXIMUM_a 999 // constant which represents the maximum a value
// #define MINIMUM_b -999 // constant which represents the minimum b value
// #define MAXIMUM_b 999 // constant which represents the maximum b value
#define MINIMUM_n 1 // constant which represents the minimum n value
#define MAXIMUM_n 999 // constant which represents the maximum n value

// Define the data type for an object which represents a single variable function.
using Function = std::function<double(double)>;

/** 
 * Define a struct-type variable named Parameters which stores the three variables needed to take the Reimann Sum 
 * of some single-variable function (whose dependent variable is x) over some positive-length interval of the x-axis
 * of a Cartesian grid
 * where the left end of that interval is represented by a double-type variable named a,
 * where the right end of that interval is represented by a double-type variable named b,
 * and where the natural number of times which that interval is divided into equally-sized partitions 
 * is represented by an int-type variable named n.
 */
struct Parameters { 
    double a; 
    double b; 
    int n; 
};

/** function prototypes */
double computeRiemannSum(Function func, double a, double b, int n, const std::string& method);
Function selectFunctionFromListOfFunctions(std::ofstream & file);
Parameters selectPartitioningValues(std::ofstream & file);

/** program entry point */
int main() {

    // Declare a file output stream object.
    std::ofstream file;

    // Set the number of digits of floating-point numbers which are printed to the command line terminal to 100 digits.
    std::cout.precision(100);

    // Set the number of digits of floating-point numbers which are printed to the file output stream to 100 digits.
    file.precision(100);

    /**
     * If the file named reimann_sum_output.txt does not already exist 
     * inside of the same file directory as the file named reimann_sum.cpp, 
     * create a new file named reimann_sum_output.txt in that directory.
     * 
     * Open the plain-text file named reimann_sum_output.txt
     * and set that file to be overwritten with program data.
     */
    file.open("reimann_sum_output.txt");

    // Print an opening message to the command line terminal.
    std::cout << "\n\n--------------------------------";
    std::cout << "\nStart Of Program";
    std::cout << "\n--------------------------------";

    // Print an opening message to the file output stream.
    file << "--------------------------------";
    file << "\nStart Of Program";
    file << "\n--------------------------------";

    /**
     * Prompt the user to select one of multiple single-variable functions from a list.
     * Store the selected function in a Function type variable named func.
     */
    Function func = selectFunctionFromListOfFunctions(file);

    //...
    Parameters parameters = selectPartitioningValues(file);

    /****/

    // Print a closing message to the command line terminal.
    std::cout << "\n\n--------------------------------";
    std::cout << "\nEnd Of Program";
    std::cout << "\n--------------------------------\n\n";

    // Print a closing message to the file output stream.
    file << "\n\n--------------------------------";
    file << "\nEnd Of Program";
    file << "\n--------------------------------";

    // Close the file output stream.
    file.close();

    // Exit the program.
    return 0; 

    /****/
    /*
    // example function: f(x) = x^2
    Function func = [](double x) { return x * x; };

    // x-axis interval [a, b]
    double a = 0.0;
    double b = 1.0;

    // number of partitions
    int n = 100;

    // method: "left", "right", or "midpoint"
    std::string method = "midpoint";

    // Compute the Riemann sum.
    double sum = computeRiemannSum(func, a, b, n, method);

    // Print the Reimann sum to the command line terminal.
    std::cout << "Riemann sum: " << sum << "\n\n";

    // Exit the program.
    return 0;
    */
}

/**
 * This function computes the Reimann sum for some arbitrary interval of the x-axis, 
 * some arbitrary number of equally sized partitions of the x-axis, 
 * some arbitrary single variable function (whose dependent variable is x), 
 * and the option to generate rectangles whose left sides either align with 
 * the left end point, 
 * right end point, 
 * or middle point of that rectangle's respective x-axis partition.
 */
double computeRiemannSum(Function func, double a, double b, int n, const std::string& method) {

    // Initialize sum, dx, and x to each store the value zero.
    double sum = 0.0, dx = 0.0, x = 0.0;

    /**
     * Print an error message to the console window if
     * a is smaller than MINIMUM_a or if
     * a is larger than MAXIMUM_a
     * and exit the function by returning zero.
     */
    if ((a < MINIMUM_a) || (a > MAXIMUM_a))
    {
        std::cout << "\n\nInvalid interval end-point. a is required to be within range [" << MINIMUM_a << "," << MAXIMUM_a << "].";
        return 0.0;
    }

    /**
     * Print an error message to the console window if
     * b is smaller than MINIMUM_b or if
     * b is larger than MAXIMUM_b
     * and exit the function by returning zero.
     */
    if ((b < MINIMUM_a) || (b > MAXIMUM_a))
    {
        std::cout << "\n\nInvalid interval end-point. b is required to be within range [" << MINIMUM_a << "," << MAXIMUM_a << "].";
        return 0.0;
    }

    /**
     * Print an error message to the console window if
     * b is smaller than or equal to a
     * and exit the function by returning zero.
     */
    if ((b < a) || (b == a))
    {
        std::cout << "\n\nInvalid interval. b is required to represent a larger value than is a.";
        return 0.0;
    }

    /**
     * Print an error message to the console window if
     * n is smaller than one (or larger than MAXIMUM_n)
     * and exit the function by returning zero.
     */
    if ((n < MINIMUM_n) || (n > MAXIMUM_n))
    {
        std::cout << "Invalid partition number. n is required to represent a natural number.";
        return 0.0;
    }

    // Set dx to represent the length of each one of the n equally-sized partitions of the x-axis interval [a,b].
    dx = (b - a) / n;
        
    /**
     * For each one of the n equally-sized partitions of the x-axis,
     * compute the approximate area of the region bounded by y = f(x) = func,
     * the x-axis, and the vertical lines which intersect with the endpoints (or mid points)
     * of the respective x-axis partition.
     *
     * Then add that area (which is the area of some rectangle) to sum.
     */
    for (int i = 0; i < n; ++i) 
    {
        if (method == "left") 
        {
            x = a + i * dx;
        } 
        else if (method == "right") 
        {
            x = a + (i + 1) * dx;
        } 
        else if (method == "midpoint") 
        {
        	x = a + (i + 0.5) * dx;
        }

        /**
         * Print an error message to the console window if 
         * method is not either 'left', 'right', or 'midpoint'
         * and exit the function by returning the value 0.0.
         */
        else 
        {
            std::cout << "\n\nInvalid method. Use 'left', 'right', or 'midpoint'.";
            return 0.0;
        }

        // Add the area of the current rectangle to the running total sum.
        sum += func(x) * dx; 
    }

    // Return the Reimann sum obtained by adding each of the n rectangle areas.
    return sum;
}

/**
 * This function displays a list of single-variable algebraic functions
 * on the command line terminal and in the output file stream and
 * prompts the program user to input an option number which corresponds
 * with exactly one of the aforementioned functions. 
 * 
 * After the user enters some value, the corresponding Function type
 * object is returned.
 */
Function selectFunctionFromListOfFunctions(std::ofstream & file)
{
    // example function: f(x) = x^2
    Function func_0 = [](double x) { return x * x; };

    // example function: f(x) = x^3
    Function func_1 = [](double x) { return x * x * x; };

    // example function: f(x) = sin(x)
    Function func_2 = [](double x) { return sin(x); };

    // example function: f(x) = cos(x)
    Function func_3 = [](double x) { return cos(x); };

    // example function: f(x) = sqrt(x)
    Function func_4 = [](double x) { return sqrt(x); };

    // example function: f(x) = 2x + 3
    Function func_5 = [](double x) { return 2 * x + 3; };

    // Initialize option to represent 0 (which is the associated with the first function in the above list).
    int option = 0;

    // Print menu options and the instruction to input an option number to the command line terminal.
    std::cout << "\n\nEnter the number which corresponds with one of the following functions:";
    std::cout << "\n\n0 --> f(x) = x^2";
    std::cout << "\n\n1 --> f(x) = x^3";
    std::cout << "\n\n2 --> f(x) = sin(x)";
    std::cout << "\n\n3 --> f(x) = cos(x)";
    std::cout << "\n\n4 --> f(x) = sqrt(x)";
    std::cout << "\n\n5 --> f(x) = 2x + 3";
    std::cout << "\n\nEnter Option Here: ";

    // Print menu options and the instruction to input an option number to the file output stream.
    file << "\n\nEnter the number which corresponds with one of the following functions:";
    file << "\n\n0 --> f(x) = x^2";
    file << "\n\n1 --> f(x) = x^3";
    file << "\n\n2 --> f(x) = sin(x)";
    file << "\n\n3 --> f(x) = cos(x)";
    file << "\n\n4 --> f(x) = sqrt(x)";
    file << "\n\n5 --> f(x) = 2x + 3";
    file << "\n\nEnter Option Here: ";

    /**
     * Scan the command line terminal for the most recent keyboard input value. 
     * Store that value (which is coerced to be of type int upon storage) in the variable named option.
     */
    std::cin >> option;

    // Print "The value which was entered for option is {option}." to the command line terminal.
    std::cout << "\nThe value which was entered for option is " << option << ".";

    // Print "The value which was entered for option is {option}." to the file output stream.
    file << "\n\nThe value which was entered for option is " << option << ".";

    /**
     * If option is smaller than 0 or if option is larger than 5, set option to 0
     * and print a message stating that fact to the command line terminal and to the output file stream.
     */
    if ((option < 0) || (option > 5))
    {
        option = 0;
        std::cout << "\n\noption was set to 0 by default due to the fact that the value input by the user was not recognized.";
        file << "\n\noption was set to 0 by default due to the fact that the value input by the user was not recognized.";
    }

    /**
     * Print a message about which function was selected by the user to the command line terminal and to the file output stream 
     * and return that selected function's corresponding Function type object.
     */
    if (option == 0) 
    {
        std::cout << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = x^2.";
        file << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = x^2.";
        return func_0;
    }
    if (option == 1) 
    {
        std::cout << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = x^3.";
        file << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = x^3.";
        return func_1;
    }
    if (option == 2) 
    {
        std::cout << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = sin(x).";
        file << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = sin(x).";
        return func_2;
    }
    if (option == 3) 
    {
        std::cout << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = cos(x).";
        file << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = cos(x).";
        return func_3;
    }
    if (option == 4) 
    {
        std::cout << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = sqrt(x).";
        file << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = sqrt(x).";
        return func_4;
    }
    if (option == 5) 
    {
        std::cout << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = 2x + 3.";
        file << "\n\nThe single-variable function which was selected from the list of such functions is f(x) = 2x + 3.";
        return func_5;
    }
    return func_0;
}

/**
 * If an invalid input to this function is detected, then this function will return a Parameters instance with default values as follows:
 * 
 * { a : 0.0, b : 1.0, n : 10 }.
 */
Parameters selectPartitioningValues(std::ofstream & file)
{
    // Define two double-type variables for storing values which represent the end points of an x-axis interval.
    double a = 0.0, b = 0.0;

    // Define one int-type variable for storing the number of equally sized partitions to divide the aforementioned x-axis interval into.
    int n = 1;

    // Define a read-only default Parameters value to use as a reference to replace invalid user-input values with correct values.
    const Parameters default_params = { 0.0, 1.0, 10 };

    /*****************************/
    /* Get User Input: a         */
    /*****************************/

    // Print a message to the command line terminal which prompts the user to input a value to store in the variable named a.
    std::cout << "\n\nEnter a value to store in double-type variable a (which represents the left end of the x-axis interval): ";

    // Print a message to the output file stream which prompts the user to input a value to store in the variable named a.
    file << "\n\nEnter a value to store in double-type variable a (which represents the left end of the x-axis interval): ";

    /**
     * Scan the command line terminal for the most recent keyboard input value. 
     * Store that value in the variable named a.
     */
    std::cin >> a;

    // Print "The value which was entered for a is {a}." to the command line terminal.
    std::cout << "\nThe value which was entered for a is " << a << ".";

    // Print "The value which was entered for a is {a}." to the file output stream.
    file << "\n\nThe value which was entered for a is " << a << ".";

    /**
     * Print an error message to the command line terminal and to the output file stream if
     * a is smaller than MINIMUM_a or if
     * a is larger than MAXIMUM_a
     * and return a default Parameters instance.
     */
    if ((a < MINIMUM_a) || (a > MAXIMUM_a))
    {
        std::cout << "\n\nInvalid interval end-point. a is required to be within range [" << MINIMUM_a << "," << MAXIMUM_a << "].";
        std::cout << "\n\nHence, default program values are being used to replace user inputs for the Reimann Sum partitioning parameters.";
        file << "\n\nInvalid interval end-point. a is required to be within range [" << MINIMUM_a << "," << MAXIMUM_a << "].";
        file << "\n\nHence, default program values are being used to replace user inputs for the Reimann Sum partitioning parameters.";
        return default_params;
    }

    /*****************************/
    /* Get User Input: b         */
    /*****************************/

    // Print a message to the command line terminal which prompts the user to input a value to store in the variable named b.
    std::cout << "\n\nEnter a value to store in double-type variable b (which represents the right end of the x-axis interval): ";

    // Print a message to the output file stream which prompts the user to input a value to store in the variable named b.
    file << "\n\nEnter a value to store in double-type variable b (which represents the right end of the x-axis interval): ";

    /**
     * Scan the command line terminal for the most recent keyboard input value. 
     * Store that value in the variable named a.
     */
    std::cin >> b;

    // Print "The value which was entered for b is {b}." to the command line terminal.
    std::cout << "\nThe value which was entered for b is " << b << ".";

    // Print "The value which was entered for b is {b}." to the file output stream.
    file << "\n\nThe value which was entered for b is " << b << ".";

    /**
     * Print an error message to the command line terminal and to the output file stream if
     * b is smaller than or equal to a or if
     * a is larger than MAXIMUM_a
     * and return a default Parameters instance.
     */
    if ((b <= a) || (b > MAXIMUM_a))
    {
        std::cout << "\n\nInvalid interval end-point. b is required to be within range (" << a << "," << MAXIMUM_a << "].";
        std::cout << "\n\nHence, default program values are being used to replace user inputs for the Reimann Sum partitioning parameters.";
        file << "\n\nInvalid interval end-point. b is required to be within range (" << a << "," << MAXIMUM_a << "].";
        file << "\n\nHence, default program values are being used to replace user inputs for the Reimann Sum partitioning parameters.";
        return default_params;
    }

   //...

    Parameters parameters;
/*
    parameters.a = a;
    parameters.b = b;
    parameters.n = n;*/

    return parameters;
}
