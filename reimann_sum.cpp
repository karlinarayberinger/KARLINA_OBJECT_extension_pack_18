/**
 * file: reimann_sum.cpp
 * type: plain-text
 * date: 02_AUGUST_2024
 * author: karbytes
 * license: PUBLIC_DOMAIN
 */

/** preprocessing directives */
#include <iostream> // standard input (std::cin), standard output (std::cout)
#include <functional> // define custom Function type

// Define the data type for an object which represents a single variable function.
using Function = std::function<double(double)>;

/** function prototypes */
double computeRiemannSum(Function func, double a, double b, int n, const std::string& method);

/** program entry point */
int main() {

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
    double sum = 0.0;
    double dx = (b - a) / n;

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
        double x;
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
            std::cerr << "Invalid method. Use 'left', 'right', or 'midpoint'." << std::endl;
            return 0.0;
        }

        // Add the area of the current rectangle to the running total sum.
        sum += func(x) * dx; 
    }

    // Return the Reimann sum obtained by adding each of the n rectangle areas.
    return sum;
}
