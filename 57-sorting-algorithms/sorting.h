#pragma once

#include <string>
#include <vector>

#include "util.h"

using std::string, std::vector;

/** Base class for sorting algorithms. */
class Sorting {
public:
    /**
     * Initializes list and returns pointer to corresponding
     * algorithm sorting subclass.
     */
    static Sorting * init(
        const vector<int> &list, const string &algorithm
    );

    /** Visually draws list as a graph on screen. */
    void draw_list() const;

    virtual void sort() {}

    virtual ~Sorting() {}

protected:
    /** How many values in list. */
    int n;

    /** The list to be sorted. */
    vector<int> list;
};

/** Bubble sort, O(n²). */
class Bubble : public Sorting {
public:
    /**
     * Compares adjacent values and swaps them if out of order,
     * moving the smallest value to the start of the unordered portion.
     */
    void sort();
};

/** Selection sort, O(n²). */
class Selection : public Sorting {
public:
    /**
     * Compares first unordered element to all the others,
     * moving a smaller one to the start whenever it's found.
     */
    void sort();
};

/** Insertion sort, O(n²). */
class Insertion : public Sorting {
public:
    /**
     * Swaps first unordered element with previously ordered ones
     * until it's moved to the right position in the ordered prefix.
     */
    void sort();
};

/** Merge sort, O(n * log(n)). */
class Merge : public Sorting {
public:
    /**
     * Recursively splits list into segments of half the calling size,
     * merging both resulting segments into a single ordered one.
     */
    void sort();

private:
    void inner_sort(int l, int r);
};

/** Quicksort, O(n * log(n)). */
class Quick : public Sorting {
public:
    /**
     * Randomly chooses a pivot, which is moved to the correct position
     * and then algorithm recursively applied to the split segments.
     */
    void sort();

private:
    void inner_sort(int l, int r);
};

/** Heapsort, O(n * log(n)). */
class Heap : public Sorting {
public:
    /**
     * Builds a max heap from list values, then sorted array by
     * moving top elements to the end whilst maintaining heap integrity.
     */
    void sort();
};
