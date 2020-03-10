/* Filename     : sorter.hpp
 * Author       : Curtis Brinker
 * Course       : CS 2500
 * Assignment   : Project 1 - Part 2
 * Due Date     : 2020-03-12
 */

#ifndef SORTER_HPP
#define SORTER_HPP

bool Sorter::ignore_asserts = false;


template <typename Container>
Container Sorter::MergeSort(const Container& A) {
    // Pre-condition: A is an indexable container
    assert(ignore_asserts || (is_same<std::random_access_iterator_tag, typename Container::iterator::iterator_category>::value));

    if (A.size() <= 1) {
        return A;
    }
    u_int32_t m = A.size() / 2;

    Container left = Container(A.begin(), A.begin() + m);
    Container right = Container(A.begin() + m, A.end());

    Container result = Merge(MergeSort(left), MergeSort(right));

    // Post-condition: result is sorted in ascending order
    assert(ignore_asserts || is_sorted(result.begin(), result.end()));

    return result;
}


template <typename Container>
Container Sorter::HeapSort(const Container& A) {
    // Pre-condition: A is an indexable container
    assert(ignore_asserts || (is_same<std::random_access_iterator_tag, typename Container::iterator::iterator_category>::value));
    
    Container result = A;

    // Make a heap from the provided container
    Heapify(result);

    for (int64_t k = result.size() - 1; k > 0; k--) {
        // Invariant: result(0..k) is a max heap
        assert(ignore_asserts || NodesSatisfiesMaxHeapProperties(result, k+1, 0, k+1));
        // Invariant: result(k+1..n) is sorted in ascending order
        assert(ignore_asserts || is_sorted(result.begin() + (k+1), result.end()));

        swap(result.at(k), result.at(0));
        MaxHeapAdjust(result, k, 0);

        // Invariant: result(0..k-1) is a max heap
        assert(ignore_asserts || NodesSatisfiesMaxHeapProperties(result, k, 0, k));
        // Invariant: result(k..n) is sorted in ascending order
        assert(ignore_asserts || is_sorted(result.begin() + k, result.end()));
    }


    // Post-condition: result is sorted in ascending order
    assert(ignore_asserts || is_sorted(result.begin(), result.end()));

    return result;
}


template <typename Container>
Container Sorter::Merge(const Container& left, const Container& right) {
    // Pre-condition: left and right are indexable containers
    assert(ignore_asserts || (is_same<std::random_access_iterator_tag, typename Container::iterator::iterator_category>::value));
    // Pre-condition: left is sorted in ascending order
    assert(ignore_asserts || is_sorted(left.begin(), left.end()));
    // Pre-condition: right is sorted in ascending order
    assert(ignore_asserts || is_sorted(right.begin(), right.end()));
    
    // Container to hold the merged lists
    Container result;

    // Current index of the left, right containers, respectively
    int64_t l_index = 0;
    int64_t r_index = 0;

    // Invariant: Length of result container <= length of left + length of right
    assert(ignore_asserts || result.size() <= (left.size() + right.size()));

    // While every element in the left and right list
    // has not been added to result
    while ( result.size() < (left.size() + right.size()) ) {
        // Invariant: Length of result container = l_index + r_index
        assert(ignore_asserts || result.size() == (l_index + r_index));
        // Invariant: result is sorted in ascending order
        assert(ignore_asserts || is_sorted(result.begin(), result.end()));

        // If elements remain in both left and right list
        if (l_index < left.size() && r_index < right.size()) {
            // Add item from left container
            if (left.at(l_index) < right.at(r_index)) {
                result.push_back(left.at(l_index));
                l_index++;
            }
            // Add item from right container
            else {
                result.push_back(right.at(r_index));
                r_index++;
            }
        }
        // If only elements in left container has not been used
        else if (l_index < left.size()) {
            result.push_back(left.at(l_index));
            l_index++;
        }
        // Else if only elements in right container has not been used
        else {
            result.push_back(right.at(r_index));
            r_index++;
        }

        // Invariant: Length of result container = l_index + r_index
        assert(ignore_asserts || result.size() == (l_index + r_index));
        // Invariant: result is sorted in ascending order
        assert(ignore_asserts || is_sorted(result.begin(), result.end()));
    }

    // Post-condition: Length of result container == length of left + length of right
    assert(ignore_asserts || result.size() == (left.size() + right.size()));
    // Post-condition: result is sorted in ascending order
    assert(ignore_asserts || is_sorted(result.begin(), result.end()));

    return result;
}


template <typename Container>
void Sorter::Heapify(Container& A) {
    // Pre-condition: A is an indexable container
    assert(ignore_asserts || (is_same<std::random_access_iterator_tag, typename Container::iterator::iterator_category>::value));
    
    for (int64_t k = (A.size() / 2) - 1; k >=0; k--) {
        // Invariant: A(k+1..n) satisfies the max heap property
        assert(ignore_asserts || NodesSatisfiesMaxHeapProperties(A, A.size(), k+1, A.size()));
        
        MaxHeapAdjust(A, A.size(), k);

        // Invariant: A(k..n) satisfies the max heap property
        assert(ignore_asserts || NodesSatisfiesMaxHeapProperties(A, A.size(), k, A.size()));
    }

    // Post-condition: A is a max heap
    assert(ignore_asserts || is_heap(A.begin(), A.end()));
}


template <typename Container>
void Sorter::MaxHeapAdjust(Container& A, int64_t n, int64_t k) {
    // Pre-condition: A is an indexable container
    assert(ignore_asserts || (is_same<std::random_access_iterator_tag, typename Container::iterator::iterator_category>::value));
    
    int64_t index = 2*k + 1;

    // If node k has no children
    if (index + 1 > n) { return; }
 
    // If they have a right child, determine the greatest node
    if (index + 1 < n) {
        index = A.at(index) < A.at(index+1) ? index + 1 : index;
    }

    // If node k is less than the greatest child
    // swap then re-adjust
    if (A.at(k) < A.at(index)) {
        swap(A.at(k), A.at(index));
        MaxHeapAdjust(A, n, index);
    }

    // Post-condition: A(k) satisifies the max_heap properties
    assert(ignore_asserts || NodeSatisfiesMaxHeapProperties(A, n, k));
}


template <typename Container>
bool Sorter::NodeSatisfiesMaxHeapProperties(const Container& A, int64_t n, int64_t k) {
    int64_t left_index = 2*k + 1;
    int64_t right_index = left_index + 1;

    bool valid = true;

    // If no child node
    if (left_index >= n) {
        return valid;
    }
    // If there is a right child
    if (right_index < n) {
        valid = valid && (A.at(right_index) <= A.at(k));
        
    }
    // Else there is only a left child
    valid = valid && (A.at(left_index) <= A.at(k));
    return valid;
}


template <typename Container>
bool Sorter::NodesSatisfiesMaxHeapProperties(const Container& A, int64_t n, int64_t from, int64_t to) {
    bool valid = true;
    for (int64_t k = from; valid && k < to; k++) {
        valid = valid && NodeSatisfiesMaxHeapProperties(A, n, k);
    }
    return valid;
}


#endif