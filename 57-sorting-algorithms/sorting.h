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