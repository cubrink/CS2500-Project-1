/* Filename     : sorter.h
 * Author       : Curtis Brinker
 * Course       : CS 2500
 * Assignment   : Project 1 - Part 2
 * Due Date     : 2020-03-12
 */

#ifndef SORTER_H
#define SORTER_H

#include <algorithm>        // std::swap(), std::is_heap(), std::is_sorted()
#include <cassert>          // assert()

using std::swap;
using std::is_heap;
using std::is_sorted;
using std::is_same;

/* Class name:              Sorter
 * 
 * Description:             Provides different methods of sorting containers 
 *                          of elements
 */
class Sorter {
public:    
    /* To fairly test runtime of algorithms asserts may need to
     * be disabled as they can change the order of the runtime
     * complexity
     *
     * Example:
     * In HeapSort, is_sorted is called on each iteration
     * Because is_sorted is of O(n) complexity, this requires
     * HeapSort to be at least O(n^2) when assert statements are
     * enabled
     */
    static bool ignore_asserts;

    /* Function name:       Sorter::MergeSort(const Container& A)
     * 
     * Description:         Returns a container sorted in ascending order using
     *                      the elements of the provided container with the
     *                      Merge Sort algorithm
     * 
     * Returns:             Returns a container sorted in ascending order
     * 
     * Arguments:
     *  <Container>& A      The container holding values to be sorted
     * 
     * Pre-conditions:      A is an instance of a container that supports
     *                      random access to elements using the STL interface
     * 
     * Post-conditions:     A container of the same type as the input is returned
     *                      whose elements are sorted in ascending order
     */
    template <typename Container>
    static Container MergeSort(const Container& A);

    /* Function name:       Sorter::HeapSort(const Container& A)
     * 
     * Description:         Returns a container sorted in ascending order using
     *                      the elements of the provided container with the
     *                      Heap Sort algorithm
     * 
     * Returns:             Returns a container sorted in ascending order using
     *                      the Heap Sort algorithm
     * 
     * Arguments:
     *  <Container>& A      The container holding values to be sorted
     * 
     * Pre-conditions:      A is an instance of a container that supports
     *                      random access to elements using the STL interface
     * 
     * Post-conditions:     A container of the same type as the input is returned
     *                      whose elements are sorted in ascending order
     */
    template <typename Container>
    static Container HeapSort(const Container& A);


protected:
    /* Function name:       Merge(const Container& left, const Container& right)
     * 
     * Description:         Merges two sorted lists together into one sorted list.
     * 
     * Returns:             Returns a container with all elements of the left 
     *                      and right containers sorted in ascending order
     * 
     * Arguments:
     *  <Container> left    A container holding values to be merged
     *  <Container> right   A container holding values to be merged
     * 
     * Pre-conditions:      left and right are sorted in ascending order
     *                      
     *                      left and right are instances of a container that supports
     *                      random access to elements using the STL interface
     * 
     * Post-conditions:     A container of the same type as the input is returned
     *                      whose elements are sorted in ascending order
     */
    template <typename Container>
    static Container Merge(const Container& left, const Container& right);


    /* Function name:       Sorter::Heapify(const Container& A)
     * 
     * Description:         Makes a provided container into a max heap
     * 
     * Returns:             Nothing
     * 
     * Arguments:
     *  <Container>& A      The container to be converted into a max heap
     * 
     * Pre-conditions:      A is an instance of a container that supports
     *                      random access to elements using the STL interface
     * 
     * Post-conditions:     The container passed to the function is a max heap
     */
    template <typename Container>
    static void Heapify(Container& A);


    /* Function name:       Sorter::MaxHeapAdjust(Container& A, int64_t n, int64_t k)
     * 
     * Description:         Adjusts node k in a container of size n to satisfy
     *                      the max heap property
     * 
     * Returns:             Nothing
     * 
     * Arguments:
     *  <Container>& A      The container to be converted into a max heap
     *  int64_t n           The size of the heap
     *  int64_t k           The node in the heap to adjust
     * 
     * Pre-conditions:      A is an instance of a container that supports
     *                      random access to elements using the STL interface
     * 
     * Post-conditions:     The node k in A(0..n) satisfies the max heap properties
     */
    template <typename Container>
    static void MaxHeapAdjust(Container& A, int64_t n, int64_t k);


    /* Function name:       Sorter::NodeSatisfiesMaxHeapProperties(const Container& A, int64_t n, int64_t k)
     * 
     * Description:         Checks if node k in a heap of size n satisfies the
     *                      max heap property
     * 
     * Returns:             true if node k satisfies the max heap properties in
     *                      a max heap of size n
     *                      false otherwise
     * 
     * Arguments:
     *  <Container>& A      The container to check max heap properties
     *  int64_t n           The size of the heap
     *  int64_t k           The node in the heap to check max heap properies
     * 
     * Pre-conditions:      A is an instance of a container that supports
     *                      random access to elements using the STL interface
     * 
     * Post-conditions:     True is returned if the node satisfies the max heap properties, false otherwise
     */
    template <typename Container>
    static bool NodeSatisfiesMaxHeapProperties(const Container& A, int64_t n, int64_t k);


    /* Function name:       Sorter::NodesSatisfiesMaxHeapProperties(const Container& A, int64_t n, int64_t from, int64_t to)
     * 
     * Description:         Checks if nodes [from, to) in a heap of size n 
     *                      satisfy the max heap property
     * 
     * Returns:             true if nodes [from, to) satisfy the max heap properties in
     *                      a max heap of size n
     *                      false otherwise
     * 
     * Arguments:
     *  <Container>& A      The container to check max heap properties
     *  int64_t n           The size of the heap
     *  int64_t from        Lower bound of nodes in the heap to check (inclusive)
     *  int64_T to          Upper bound of nodes in the heap ot check (exclusive)
     * 
     * Pre-conditions:      A is an instance of a container that supports
     *                      random access to elements using the STL interface
     * 
     * Post-conditions:     True is returned if all nodes in range satisfy the max heap property, false otherwise
     */
    template <typename Container>
    static bool NodesSatisfiesMaxHeapProperties(const Container& A, int64_t n, int64_t from, int64_t to);
};

#include "sorter.hpp"
#endif