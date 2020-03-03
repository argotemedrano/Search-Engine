#include "searcheng.h"

/**
 * @param[in] setA
 * @param[in] setB
 * @return WebPageSet with setA (intersection) setB
 * Description: Everything in setA must be found in setB. That is, combine them
 *  in the pages they have in common
 * All the web pages with
 * Similar to set intersection: setA (intersection) setB
 */
WebPageSet AndCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
    WebPageSet combined;
    WebPageSet::iterator setA_itr;
    
    WebPageSet::iterator setB_itr = setB.begin();
    for (; setB_itr != setB.end(); ++setB_itr) {
        // Find B in A
        setA_itr = setA.find(*setB_itr);

        // Add to combined if found in both sets
        if (setA_itr != setA.end()) {
            combined.insert(*setA_itr);
        }
    }
    return combined;
}

/**
 * @param[in] setA
 * @param[in] setB
 * @return WebPageSet with setA (union) setB
 * Description: Any webpage in setA or setB will be merged into one set
 * Similar to set union: setA (union) setB
 */
WebPageSet OrCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
    WebPageSet combined;

    // Add all of B
    combined = setA;

    // Add all of A
    WebPageSet::iterator setB_itr = setB.begin();

    // Add all of B
    for (; setB_itr != setB.end(); ++setB_itr) {
        combined.insert(*setB_itr);
    }

    return combined;
}

/**
 * @param[in] setA: Set of pages with terms wanted
 * @param[in] setB: Set of pages with terms not wanted
 * @return WebPageSet with setA difference setB
 * Similar to set difference: setA - setB. setA cannot contain webpages with terms in setB
 */
WebPageSet DiffCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
    WebPageSet combined;

    WebPageSet::iterator setA_itr = setA.begin();

    WebPageSet::iterator setB_itr;

    // Add all of A
    for (; setA_itr != setA.end(); ++setA_itr) {
        // Find A in B
        setB_itr = setB.find(*setA_itr);

        // Element of A must not be in B
        if (setB_itr == setB.end()) {
            combined.insert(*setA_itr);
        }
    }

    return combined;
}
