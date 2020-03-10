/* Filename     : driver.cpp
 * Author       : Curtis Brinker
 * Course       : CS 2500
 * Assignment   : Project 1 - Part 2
 * Due Date     : 2020-03-12
 */
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <fstream>
#include <iomanip> 
#include <iostream>
#include <algorithm>
#include "sorter.h"

using namespace std;

/* Function name:                                       test_runtime(Container (*algorithm)(const Container&), 
 *                                                                   const vector<Container>& test_data);
 *                              
 * Description:                                         Returns vector times required (in seconds) to sort 
 *                                                      each test item, stored as doubles
 *                              
 * Returns:                                             Returns a vector doubles
 *      
 * Arguments:       
 *  const Container (*algorithm)(const Container&)      Algorithm to use to sort the test_data
 *  const vector<Container>& test_data                  vector of containers to be sorted
 */
template <typename Container>
vector<double> test_runtime(Container (*algorithm)(const Container&), 
                            const vector<Container>& test_data);


/* Function name:               gen_worst_cases(const uint32_t item_length, 
 *                                              const uint32_t test_cases,
 *                                              const uint32_t seed = 0);
 *      
 * Description:                 Returns vector of vectors of integers such that
 *                              each vector is sorted in decending order
 *      
 * Returns:                     Returns a vector of vectors of integers
 *                              sorted in decending order
 *      
 * Arguments:       
 *  const uint32_t item_length  Length of each vector
 *  const uint32_t test_cases   Total vectors to be generated
 *  const uint32_t seed         Seed used to generate the vectors
 */
vector<vector<int32_t>> gen_worst_cases(const uint32_t item_length, 
                                        const uint32_t test_cases,
                                        const uint32_t seed = 0);


/* Function name:               gen_average_cases(const uint32_t item_length, 
 *                                                const uint32_t test_cases,
 *                                                const uint32_t seed = 0);
 *      
 * Description:                 Returns vector of vectors of integers such that
 *                              each vector contains random integers
 *      
 * Returns:                     Returns a vector of vectors of integers
 *                              sorted in decending order
 *      
 * Arguments:       
 *  const uint32_t item_length  Length of each vector
 *  const uint32_t test_cases   Total vectors to be generated
 *  const uint32_t seed         Seed used to generate the vectors
 */
vector<vector<int32_t>> gen_average_cases(const uint32_t item_length, 
                                          const uint32_t test_cases,
                                          const uint32_t seed = 0);


/* Function name:               gen_best_cases(const uint32_t item_length, 
 *                                             const uint32_t test_cases,
 *                                             const uint32_t seed = 0);
 *      
 * Description:                 Returns vector of vectors of integers such that
 *                              each vector is sorted in ascendingn order
 *      
 * Returns:                     Returns a vector of vectors of integers
 *                              sorted in decending order
 *      
 * Arguments:       
 *  const uint32_t item_length  Length of each vector
 *  const uint32_t test_cases   Total vectors to be generated
 *  const uint32_t seed         Seed used to generate the vectors
 */
vector<vector<int32_t>> gen_best_cases(const uint32_t item_length, 
                                       const uint32_t test_cases,
                                       const uint32_t seed = 0);



/* Function name:                               gen_runtime_report(string filename);
 *                      
 * Description:                                 Writes a runtime analysis report as a .csv to the filename
 *                      
 * Returns:                                     Nothing
 *      
 * Arguments:       
 *  string filename                             Name of file to be written to
 *  const uint32_t sample_size                  Size of each sample for a given length of container
 *  const <vector32_t>& container_lengths       Size of containers to be tested
 */
void gen_runtime_report(string filename, 
                        const uint32_t sample_size, 
                        const vector<uint32_t>& container_lengths);


/* Function name:                               test_boundaries(Container (*algorithm)(Container));
 *                      
 * Description:                                 Tests boundary conditions on the specified algorithm
 *                      
 * Returns:                                     Returns true if boundary tests are passed
 *      
 * Arguments:       
 *  Container (*algorithm)(const Container&)    Algorithm to have boundary test applied on
 */
template <typename Container>
bool boundary_test(Container (*algorithm)(const Container&));


int main() {
    // Store results of boundary testing
    bool boundary_test_result;

    // Define parameter to test the algorithms
    const uint32_t SAMPLE_SIZE = 25;
    const vector<uint32_t> container_lengths = {0, 1, 10, 100, 500, 1000, 5000, 10000, 25000, 50000, 100000, 250000};
    const string filename = "report.csv";

    // Output testing status
    cout << "Beginning boundary testing..." << endl << endl;

    cout << "Testing MergeSort" << endl;
    boundary_test_result = boundary_test<vector<int32_t>>(Sorter::MergeSort);
    cout << "MergeSort result: " << (boundary_test_result ? "Success!" : "Failed!") << endl << endl;

    cout << "Testing HeapSort" << endl;
    boundary_test_result = boundary_test<vector<int32_t>>(Sorter::HeapSort);
    cout << "HeapSort result: " << (boundary_test_result ? "Success!" : "Failed!") << endl << endl;

    cout << "Boundary testing complete!" << endl << endl;


    cout << "Begining runtime analysis..." << endl << endl;

    // Asserts must be disabled to fairly analyze runtimes
    // See note in sorter.h
    Sorter::ignore_asserts = true;
    gen_runtime_report(filename, SAMPLE_SIZE, container_lengths);
    Sorter::ignore_asserts = false;

    cout << endl << "Runtime analysis complete!" << endl;
    cout << "Runtime report written to " << filename << endl << endl;

    return 0;
}


template <typename Container>
vector<double> test_runtime(Container (*algorithm)(const Container&), const vector<Container>& test_data) {
    // Declare variables for measuring runtime
    decltype(chrono::high_resolution_clock::now()) start, finish;
    chrono::duration<double> delta;

    // Holds runtimes of each item in test_data (in seconds)
    vector<double> runtimes;

    for (Container data: test_data) {
        // Measure runtime with sample data
        start = chrono::high_resolution_clock::now();
        Container result = algorithm(data);
        finish = chrono::high_resolution_clock::now();

        // Calculate time required
        delta = finish - start;
        // Push runtime to vector (in seconds)
        runtimes.push_back(delta.count());
    }

    return runtimes;
}


vector<vector<int32_t>> gen_worst_cases(const uint32_t item_length, 
                                        const uint32_t test_cases,
                                        const uint32_t seed) {
    // Set initial seed
    srand(seed);

    // Maximum step size taken by random number
    const uint32_t MAX_STEP_SIZE = 1000;

    // Vector to hold each test case
    vector<vector<int32_t>> test_data;


    // Create test cases
    for (uint32_t i = 0; i < test_cases; i++) {
        vector<int32_t> test_case;
        
        // Starting value
        int32_t value = rand() - RAND_MAX;

        // Add value while more items need to be added
        while (test_case.size() < item_length) {
            test_case.push_back(value);
            value -= (rand() % MAX_STEP_SIZE);
        }

        // Add test case to test_data
        test_data.push_back(test_case);
    }

    // Return all test cases
    return test_data;
}


vector<vector<int32_t>> gen_average_cases(const uint32_t item_length, 
                                        const uint32_t test_cases,
                                        const uint32_t seed) {
    // Set initial seed
    srand(seed);

    // Maximum step size taken by random number
    const uint32_t MAX_STEP_SIZE = 1000;

    // Vector to hold each test case
    vector<vector<int32_t>> test_data;


    // Create test cases
    for (uint32_t i = 0; i < test_cases; i++) {
        vector<int32_t> test_case;
        
        // Starting value
        int32_t value;

        // Add value while more items need to be added
        while (test_case.size() < item_length) {
            value = rand() - RAND_MAX;
            test_case.push_back(value);
        }

        // Add test case to test_data
        test_data.push_back(test_case);
    }

    // Return all test cases
    return test_data;
}


vector<vector<int32_t>> gen_best_cases(const uint32_t item_length, 
                                        const uint32_t test_cases,
                                        const uint32_t seed) {
    // Set initial seed
    srand(seed);

    // Maximum step size taken by random number
    const uint32_t MAX_STEP_SIZE = 1000;

    // Vector to hold each test case
    vector<vector<int32_t>> test_data;


    // Create test cases
    for (uint32_t i = 0; i < test_cases; i++) {
        vector<int32_t> test_case;
        
        // Starting value
        int32_t value = rand() - RAND_MAX;

        // Add value while more items need to be added
        while (test_case.size() < item_length) {
            test_case.push_back(value);
            value += (rand() % MAX_STEP_SIZE);
        }

        // Add test case to test_data
        test_data.push_back(test_case);
    }

    // Return all test cases
    return test_data;
}


void gen_runtime_report(string filename, const uint32_t sample_size, const vector<uint32_t>& container_lengths) {
    // Open output file
    ofstream outfile(filename);

    // Create vectors to hold test data
    vector<vector<int32_t>> worst, average, best;

    // Write csv header
    outfile << "N,merge_worst,merge_avg,merge_best,heap_worst,heap_avg,heap_best" << '\n';

    // Set output format
    outfile << fixed << showpoint << setprecision(9);

    // Run a test for each length
    for (uint32_t length: container_lengths) {
        cout << "Generating data for length = " << length << endl;

        worst = gen_worst_cases(length, sample_size);
        average = gen_average_cases(length, sample_size);
        best = gen_best_cases(length, sample_size);

        // Hold runtime for worst/average/best case
        vector<double> merge_w, merge_a, merge_b;
        vector<double> heap_w, heap_a, heap_b;

        // Run tests for each category
        merge_w = test_runtime(Sorter::MergeSort, worst);
        merge_a = test_runtime(Sorter::MergeSort, average);
        merge_b = test_runtime(Sorter::MergeSort, best);
        heap_w = test_runtime(Sorter::HeapSort, worst);
        heap_a = test_runtime(Sorter::HeapSort, average);
        heap_b = test_runtime(Sorter::HeapSort, best);
        
        // Write results to row
        for (uint32_t s = 0; s < sample_size; s++) {
            outfile << length << ","
                    << merge_w[s] << ","
                    << merge_a[s] << ","
                    << merge_b[s] << ","
                    << heap_w[s] << ","
                    << heap_a[s] << ","
                    << heap_b[s] << '\n';
        }
    }

    // Close file when done
    outfile.close();
}


template <typename Container>
bool boundary_test(Container (*algorithm)(const Container&)) {
    // Test on very small input sizes where something could go wrong
    vector<uint32_t> boundary_lengths = {0, 1, 2, 3, 4, 1000};
    uint32_t sample_size = 10;  // Run each test 10 times

    // Create vectors to hold test data
    vector<vector<int32_t>> worst, average, best;

    for (uint32_t length: boundary_lengths) {
        cout << "Verifying correctness on boundary: n = " << length << "...";
        // Hold data for test cases
        worst = gen_worst_cases(length, sample_size);
        average = gen_average_cases(length, sample_size);
        best = gen_best_cases(length, sample_size);

        for (Container w: worst) {
            // Sort the test data
            // Assert statements in specifed algorithm verify
            // that the data has been sorted correctly
            Container tmp = algorithm(w);
        }
        for (Container a: average) {
            // Sort the test data
            // Assert statements in specifed algorithm verify
            // that the data has been sorted correctly
            Container tmp = algorithm(a);
        }
        for (Container b: best) {
            // Sort the test data
            // Assert statements in specifed algorithm verify
            // that the data has been sorted correctly
            Container tmp = algorithm(b);
        }
        cout << "test passed!" << endl;
    }

    // If any of the tests fail an assert will fail, thus causing the program to fail
    return true;
}