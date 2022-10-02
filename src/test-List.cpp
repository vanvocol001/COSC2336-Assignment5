/** @file test-List.cpp
 *
 * @brief Unit tests for Assignment Sorting and Searching:
 *   Recursive Sorting and Searching with Merge Sort and Binary Search.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Sorting and Searching
 * @date   June 1, 2021
 *
 * Implement recursive sorting and searching algorithms in a
 * class ADT.
 *
 * This file contains test cases and individual unit tests for the
 * Assignment Sorting and Searching implementation.  This file uses
 * the catch2 unit test framework to define the test cases and test
 * assertions.
 */
#include "List.hpp"
#include "catch.hpp"
#include <iostream>
using namespace std;

/** Tests of the List type you have been given to use for
 * this assignment.
 */
TEST_CASE("<List> test of List user defined type for this assignment", "[task0]")
{
  // construct an empty list
  List l1;
  CHECK(l1.getSize() == 0);
  CHECK(l1.str() == "<list> size: 0 [ ]");

  // construct with a static array
  string values2[] = {"neo", "morpheus", "trinity", "cypher", "oracle"};
  List l2(5, values2);
  CHECK(l2.getSize() == 5);

  // check the overloaded [] indexing operator
  CHECK(l2[0] == "neo");
  CHECK(l2[1] == "morpheus");
  CHECK(l2[2] == "trinity");
  CHECK(l2[3] == "cypher");
  CHECK(l2[4] == "oracle");
  CHECK(l2.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");

  // check we are getting a valid reference back, allows us to modify
  // the list
  l2[0] = "smith";
  CHECK(l2[0] == "smith");

  l2[4] = "switch";
  CHECK(l2[4] == "switch");

  l2[2] = "agent " + l2[0];
  CHECK(l2[2] == "agent smith");

  CHECK(l2.str() == "<list> size: 5 [ smith, morpheus, agent smith, cypher, switch ]");

  // check that the values were copied into a new block of memory
  CHECK(values2[0] == "neo");
  CHECK(values2[4] == "oracle");
  CHECK(values2[2] == "trinity");

  // test bounds checking for operator[]
  CHECK_THROWS_AS(l2[5], ListMemoryBoundsException);
  CHECK_THROWS_AS(l2[-1], ListMemoryBoundsException);

  // test copy constructor works.
  List l3 = l2;
  CHECK(l3[0] == "smith");
  CHECK(l3[1] == "morpheus");
  CHECK(l3[2] == "agent smith");
  CHECK(l3[3] == "cypher");
  CHECK(l3[4] == "switch");
  CHECK(l3.str() == "<list> size: 5 [ smith, morpheus, agent smith, cypher, switch ]");

  // make sure l3 is truly a copy of l2
  l3[0] = "mouse";
  l3[2] = "tank";
  l3[4] = "dozer";
  CHECK(l3[0] == "mouse");
  CHECK(l3[1] == "morpheus");
  CHECK(l3[2] == "tank");
  CHECK(l3[3] == "cypher");
  CHECK(l3[4] == "dozer");
  CHECK(l3.str() == "<list> size: 5 [ mouse, morpheus, tank, cypher, dozer ]");

  // was l2 modified when we changed l3?
  CHECK(l2[0] == "smith");
  CHECK(l2[1] == "morpheus");
  CHECK(l2[2] == "agent smith");
  CHECK(l2[3] == "cypher");
  CHECK(l2[4] == "switch");
  CHECK(l2.str() == "<list> size: 5 [ smith, morpheus, agent smith, cypher, switch ]");

  // is l3 modified by changing l2?
  l2[1] = "merovingian";
  l2[3] += " white rabbit";
  CHECK(l2[0] == "smith");
  CHECK(l2[1] == "merovingian");
  CHECK(l2[2] == "agent smith");
  CHECK(l2[3] == "cypher white rabbit");
  CHECK(l2[4] == "switch");
  CHECK(l2.str() == "<list> size: 5 [ smith, merovingian, agent smith, cypher white rabbit, switch ]");

  CHECK(l3[0] == "mouse");
  CHECK(l3[1] == "morpheus");
  CHECK(l3[2] == "tank");
  CHECK(l3[3] == "cypher");
  CHECK(l3[4] == "dozer");
  CHECK(l3.str() == "<list> size: 5 [ mouse, morpheus, tank, cypher, dozer ]");

  // a bit more bounds checking on l3 for operator[]
  CHECK_THROWS_AS(l3[100], ListMemoryBoundsException);
  CHECK_THROWS_AS(l3[-100], ListMemoryBoundsException);

  // test overloaded boolean operator==
  // a list should be equal to itself
  CHECK(l2 == l2);
  CHECK(l3 == l3);

  // test unequal lists are not equal
  CHECK_FALSE(l2 == l3);
  CHECK_FALSE(l3 == l2);

  // test empty lists are equal
  List l4; // another empty list, like l1
  CHECK(l1 == l4);
  CHECK(l4 == l1);

  // test that different lists can be equal and not equal again
  // l5 should be a copy of l3, so initially equal
  List l5 = l3;
  CHECK(l5 == l3);
  CHECK(l3 == l5);

  // modify 1 value of l5, now lists are not equal
  l5[3] = "architect";
  CHECK_FALSE(l5 == l3);
  CHECK_FALSE(l3 == l5);

  // make equal again, and change values on both ends of both lists, just to
  // make sure about ending index manipulations
  l3[3] = "architect";
  l5[0] = "keymaker";
  l5[4] = "link";
  l3[0] = "keymaker";
  l3[4] = "link";
  CHECK(l5 == l3);
  CHECK(l3 == l5);

  // actually haven't checked if lists of unequal size are false yet
  string values6[] = {"persophne", "seraph", "niobe"};
  List l6(3, values6);
  string values7[] = {"persophne", "seraph", "niobe", "ghost"};
  List l7(4, values7);
  CHECK_FALSE(l6 == l7);
  CHECK_FALSE(l7 == l6);
}

/** Task 1: implement a sublist copy constructor for the List class.
 */

TEST_CASE("<List constructor> test of new sublist copy constructor", "[task1]")
{
  string values1[] = {"neo", "morpheus", "trinity", "cypher", "oracle"};
  List l1(5, values1);

  // copy from beginning of list
  List l2 = List(l1, 0, 2);
  CHECK(l1.getSize() == 5);
  CHECK(l1.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");
  CHECK(l2.getSize() == 3);
  CHECK(l2.str() == "<list> size: 3 [ neo, morpheus, trinity ]");

  // copy to end of list
  List l3 = List(l1, 2, 4);
  CHECK(l1.getSize() == 5);
  CHECK(l1.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");
  CHECK(l3.getSize() == 3);
  CHECK(l3.str() == "<list> size: 3 [ trinity, cypher, oracle ]");

  // copy middle values out of list
  List l4 = List(l1, 1, 3);
  CHECK(l1.getSize() == 5);
  CHECK(l1.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");
  CHECK(l4.getSize() == 3);
  CHECK(l4.str() == "<list> size: 3 [ morpheus, trinity, cypher ]");

  // copy only first value of list
  List l5 = List(l1, 0, 0);
  CHECK(l1.getSize() == 5);
  CHECK(l1.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");
  CHECK(l5.getSize() == 1);
  CHECK(l5.str() == "<list> size: 1 [ neo ]");

  // copy only last value of list
  List l6 = List(l1, 4, 4);
  CHECK(l1.getSize() == 5);
  CHECK(l1.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");
  CHECK(l6.getSize() == 1);
  CHECK(l6.str() == "<list> size: 1 [ oracle ]");

  // copy a middle value
  List l7 = List(l1, 2, 2);
  CHECK(l1.getSize() == 5);
  CHECK(l1.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");
  CHECK(l7.getSize() == 1);
  CHECK(l7.str() == "<list> size: 1 [ trinity ]");

  // it should be possible to create an empty list with the sublist constructor
  List l8 = List(l1, 1, 0);
  CHECK(l1.getSize() == 5);
  CHECK(l1.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");
  CHECK(l8.getSize() == 0);
  CHECK(l8.str() == "<list> size: 0 [ ]");

  // this should be equal to a default empty list
  List l0;
  CHECK(l8 == l0);

  // another empty sublist
  List l9 = List(l1, 4, 3);
  CHECK(l1.getSize() == 5);
  CHECK(l1.str() == "<list> size: 5 [ neo, morpheus, trinity, cypher, oracle ]");
  CHECK(l9.getSize() == 0);
  CHECK(l9.str() == "<list> size: 0 [ ]");
  CHECK(l9 == l0);

  // finally this was not mentioned in assignment description, but
  // you need to add in check that illegal bounds are not being
  // attempted and throw a ListMemoryBoundsException.  You can see
  // the operator[] for an example of how this is done
  
  CHECK_THROWS_AS(List(l1, -1, 4), ListMemoryBoundsException);
  CHECK_THROWS_AS(List(l1, 5, 4), ListMemoryBoundsException);
  CHECK_THROWS_AS(List(l1, 0, -1), ListMemoryBoundsException);
  CHECK_THROWS_AS(List(l1, 0, 5), ListMemoryBoundsException);
  
}


/** Task 2: implement merge member function
 */

TEST_CASE("<List> implement merge member function", "[task2]")
{
  SECTION("test merge order lower, upper, lower, upper")
  {
    string lowerValues[] = {"cypher", "neo"};
    List lower(2, lowerValues);

    string upperValues[] = {"morpheus", "trinity"};
    List upper(2, upperValues);

    List result(4); // constructure for list of size 4 of "" strings

    result.merge(lower, upper);
    CHECK(result.str() == "<list> size: 4 [ cypher, morpheus, neo, trinity ]");
  }

  SECTION("test merge order upper, lower, upper, lower")
  {
    string lowerValues[] = {"morpheus", "trinity"};
    List lower(2, lowerValues);

    string upperValues[] = {"cypher", "neo"};
    List upper(2, upperValues);

    List result(4); // constructure for list of size 4 of "" strings

    result.merge(lower, upper);
    CHECK(result.str() == "<list> size: 4 [ cypher, morpheus, neo, trinity ]");
  }

  SECTION("test merge order lower, upper, upper, lower")
  {
    string lowerValues[] = {"cypher", "trinity"};
    List lower(2, lowerValues);

    string upperValues[] = {"morpheus", "neo"};
    List upper(2, upperValues);

    List result(4); // constructure for list of size 4 of "" strings

    result.merge(lower, upper);
    CHECK(result.str() == "<list> size: 4 [ cypher, morpheus, neo, trinity ]");
  }

  SECTION("test merge order upper, lower, lower, upper")
  {
    string lowerValues[] = {"morpheus", "neo"};
    List lower(2, lowerValues);

    string upperValues[] = {"cypher", "trinity"};
    List upper(2, upperValues);

    List result(4); // constructure for list of size 4 of "" strings

    result.merge(lower, upper);
    CHECK(result.str() == "<list> size: 4 [ cypher, morpheus, neo, trinity ]");
  }

  SECTION("test merge order lower, lower, upper, upper")
  {
    string lowerValues[] = {"cypher", "morpheus"};
    List lower(2, lowerValues);

    string upperValues[] = {"neo", "trinity"};
    List upper(2, upperValues);

    List result(4); // constructure for list of size 4 of "" strings

    result.merge(lower, upper);
    CHECK(result.str() == "<list> size: 4 [ cypher, morpheus, neo, trinity ]");
  }

  SECTION("test merge order upper, upper, lower, lower")
  {
    string lowerValues[] = {"neo", "trinity"};
    List lower(2, lowerValues);

    string upperValues[] = {"cypher", "morpheus"};
    List upper(2, upperValues);

    List result(4); // constructure for list of size 4 of "" strings

    result.merge(lower, upper);
    CHECK(result.str() == "<list> size: 4 [ cypher, morpheus, neo, trinity ]");
  }

  SECTION("test merge with empty list")
  {
    string lowerValues[] = {"cypher", "morpheus", "neo", "trinity"};
    List lower(4, lowerValues);

    List upper;

    List result1(4);
    result1.merge(lower, upper);
    CHECK(result1.str() == "<list> size: 4 [ cypher, morpheus, neo, trinity ]");

    List result2(4);
    result2.merge(upper, lower);
    CHECK(result2.str() == "<list> size: 4 [ cypher, morpheus, neo, trinity ]");

    // merge 2 empty lists should be possible, nothing will happen to original list
    // though, which may be a bug?
    List otherEmpty;
    List result3;
    result3.merge(upper, otherEmpty);
    CHECK(result3.str() == "<list> size: 0 [ ]");
  }

  SECTION("test some more general mixed merges")
  {
    string i1Values[] = {"agent smith", "dozer", "dujour", "morpheus", "neo", "spoon boy"};
    List i1(6, i1Values);

    string i2Values[] = {"apoc", "cypher", "dozer", "mouse", "switch"};
    List i2(5, i2Values);

    string i3Values[] = {"neo", "oracle", "tank", "trinity", "woman in red"};
    List i3(5, i3Values);

    string i4Values[] = {"agent brown", "architect", "cypher", "keymaker", "merovingian", "morpheus", "persophene", "trinity"};
    List i4(8, i4Values);

    List r1(11);
    r1.merge(i1, i2);
    CHECK(r1.str() == "<list> size: 11 [ agent smith, apoc, cypher, dozer, "
                      "dozer, dujour, morpheus, mouse, neo, spoon boy, switch ]");

    List r2(10);
    r2.merge(i3, i2);
    CHECK(r2.str() == "<list> size: 10 [ apoc, cypher, dozer, mouse, neo, "
                      "oracle, switch, tank, trinity, woman in red ]");

    List r3(13);
    r3.merge(i3, i4);
    CHECK(r3.str() == "<list> size: 13 [ agent brown, architect, cypher, "
                      "keymaker, merovingian, morpheus, neo, oracle, persophene, tank, "
                      "trinity, trinity, woman in red ]");

    List r4(24);
    r4.merge(r3, r1);
    CHECK(r4.str() == "<list> size: 24 [ agent brown, agent smith, apoc, architect, "
                      "cypher, cypher, dozer, dozer, dujour, keymaker, merovingian, "
                      "morpheus, morpheus, mouse, neo, neo, oracle, persophene, "
                      "spoon boy, switch, tank, trinity, trinity, woman in red ]");
  }

  // You need to make sure for now that the destination of the merge is large enough
  // to hold the two merged input lists.  If there is not enough space you should
  // be throwing an exception
  SECTION("test some more general mixed merges")
  {
    string i1Values[] = {"agent smith", "dozer", "dujour", "morpheus", "neo", "spoon boy"};
    List i1(6, i1Values);

    string i2Values[] = {"apoc", "cypher", "dozer", "mouse", "switch"};
    List i2(5, i2Values);

    List r1(1); // way too small
    CHECK_THROWS_AS(r1.merge(i1, i2), ListMemoryBoundsException);

    List r2(10); // just a bit too small
    CHECK_THROWS_AS(r2.merge(i1, i2), ListMemoryBoundsException);

    // for now too big is fine, but undefined result can occur
    List r3(15); // just a bit too small
    r3.merge(i1, i2);
    CHECK(r3.str() == "<list> size: 15 [ agent smith, apoc, cypher, dozer, dozer, "
                      "dujour, morpheus, mouse, neo, spoon boy, switch, , , ,  ]");
  }
}


/** Task 3: implement the recursive sort member function
 */

TEST_CASE("<List> implement sort member function", "[task3]")
{
  SECTION("test base case sorts")
  {
    // empty list should sort fine and still be empty
    List l1;
    l1.sort();
    CHECK(l1.str() == "<list> size: 0 [ ]");

    // list of 1 item will also sort to itself
    string l2Values[] = {"neo"};
    List l2(1, l2Values);
    l2.sort();
    CHECK(l2.str() == "<list> size: 1 [ neo ]");
  }

  SECTION("test size 2 list which is even sized, both unsorted and already sorted")
  {
    // unsorted
    string l1Values[] = {"trin", "neo"};
    List l1(2, l1Values);
    l1.sort();
    CHECK(l1.str() == "<list> size: 2 [ neo, trin ]");

    // already sorted
    string l2Values[] = {"neo", "trin"};
    List l2(2, l2Values);
    l2.sort();
    CHECK(l1.str() == "<list> size: 2 [ neo, trin ]");
  }

  SECTION("test size 3 list which is odd sized")
  {
    string l1Values[] = {"trin", "morpheus", "neo"};
    List l1(3, l1Values);
    l1.sort();
    CHECK(l1.str() == "<list> size: 3 [ morpheus, neo, trin ]");

    // reversed
    string l2Values[] = {"trin", "neo", "morpheus"};
    List l2(3, l2Values);
    l2.sort();
    CHECK(l2.str() == "<list> size: 3 [ morpheus, neo, trin ]");

    string l3Values[] = {"morpheus", "trin", "neo"};
    List l3(3, l3Values);
    l3.sort();
    CHECK(l3.str() == "<list> size: 3 [ morpheus, neo, trin ]");

    // already sorted
    string l4Values[] = {"morpheus", "neo", "trin"};
    List l4(3, l4Values);
    l4.sort();
    CHECK(l4.str() == "<list> size: 3 [ morpheus, neo, trin ]");
  }

  SECTION("test some general bigger lists")
  {
    // even sized
    string l1Values[] = {"persophene", "trinity", "keymaker", "merovingian", "agent brown", "morpheus", "architect", "cypher"};
    List l1(8, l1Values);
    l1.sort();
    CHECK(l1.str() == "<list> size: 8 [ agent brown, architect, cypher, keymaker, merovingian, morpheus, persophene, trinity ]");

    // bigger odd sized
    string l2Values[] = {
      "oracle", "persophene", "trinity", "agent smith", "keymaker", "merovingian", "agent brown", "morpheus", "architect", "cypher", "neo"};
    List l2(11, l2Values);
    l2.sort();
    CHECK(l2.str() == "<list> size: 11 [ agent brown, agent smith, architect, cypher, keymaker, "
                      "merovingian, morpheus, neo, oracle, persophene, trinity ]");

    // bigger reversed list even sized
    string l3Values[] = {"woman in red", "trinity", "tank", "persophene", "oracle", "neo", "mouse", "morpheus", "merovingian", "keymaker",
      "dujour", "cypher", "architect", "apoc", "agent smith", "agent brown"};
    List l3(16, l3Values);
    l3.sort();
    CHECK(l3.str() == "<list> size: 16 [ agent brown, agent smith, apoc, "
                      "architect, cypher, dujour, keymaker, merovingian, morpheus, "
                      "mouse, neo, oracle, persophene, tank, trinity, woman in red ]");

    // a bit bigger odd sized, with a few out of reverse order items and a duplicate
    string l4Values[] = {"neo", "woman in red", "trinity", "tank", "persophene", "oracle", "spoon boy", "neo", "mouse", "dozer", "morpheus",
      "merovingian", "keymaker", "dujour", "cypher", "architect", "switch", "apoc", "agent smith", "agent brown"};
    List l4(20, l4Values);
    l4.sort();
    CHECK(l4.str() == "<list> size: 20 [ agent brown, agent smith, apoc, "
                      "architect, cypher, dozer, dujour, keymaker, merovingian, "
                      "morpheus, mouse, neo, neo, oracle, persophene, spoon boy, "
                      "switch, tank, trinity, woman in red ]");
  }

  SECTION("test some more lists where we use List features")
  {
    // sort a list of values
    string l4Values[] = {"neo", "woman in red", "trinity", "tank", "persophene", "oracle", "spoon boy", "neo", "mouse", "dozer", "morpheus",
      "merovingian", "keymaker", "dujour", "cypher", "architect", "switch", "apoc", "agent smith", "agent brown"};
    List l4(20, l4Values);
    l4.sort();
    CHECK(l4.str() == "<list> size: 20 [ agent brown, agent smith, apoc, "
                      "architect, cypher, dozer, dujour, keymaker, merovingian, "
                      "morpheus, mouse, neo, neo, oracle, persophene, "
                      "spoon boy, switch, tank, trinity, woman in red ]");

    // copy the list and sort again, it should still be sorted
    List l5 = l4;
    l5.sort();
    CHECK(l5.str() == "<list> size: 20 [ agent brown, agent smith, apoc, "
                      "architect, cypher, dozer, dujour, keymaker, merovingian, "
                      "morpheus, mouse, neo, neo, oracle, persophene, "
                      "spoon boy, switch, tank, trinity, woman in red ]");

    // lists should compare as equal
    CHECK(l4 == l5);

    // but they are copies of each other, so if I change one they aren't equal anymore
    l5[0] = "seraph";
    l5[19] = "kali";
    CHECK_FALSE(l4 == l5);
    CHECK(l5.str() == "<list> size: 20 [ seraph, agent smith, apoc, "
                      "architect, cypher, dozer, dujour, keymaker, merovingian, morpheus, "
                      "mouse, neo, neo, oracle, persophene, spoon boy, switch, tank, "
                      "trinity, kali ]");

    // resort l5, still not equal to l4 but l5 now sorted
    l5.sort();
    CHECK_FALSE(l4 == l5);
    CHECK(l5.str() == "<list> size: 20 [ agent smith, apoc, architect, cypher, "
                      "dozer, dujour, kali, keymaker, merovingian, morpheus, "
                      "mouse, neo, neo, oracle, persophene, seraph, spoon boy, switch, "
                      "tank, trinity ]");
  }
}


/** Task 4: implement the recursive search member function
 */

TEST_CASE("<List> implement search member function", "[task4]")
{

  // the section for task 4
  SECTION("test base case search, search empty list should fail")
  {
    List l0; // empty list
    int result = l0.search("trinity", 1, 0);
    CHECK(result == NOT_FOUND);
  }

  SECTION("test some general cases on list of 20 values")
  {
    string l1Values[] = {"neo", "woman in red", "trinity", "tank", "persophene", "oracle", "spoon boy", "neo", "mouse", "dozer", "morpheus",
      "merovingian", "keymaker", "dujour", "cypher", "architect", "switch", "apoc", "agent smith", "agent brown"};
    List l1(20, l1Values);

    // need to sort it before we can search
    l1.sort();
    CHECK(l1.str() == "<list> size: 20 [ agent brown, agent smith, apoc, architect, "
                      "cypher, dozer, dujour, keymaker, merovingian, morpheus, "
                      "mouse, neo, neo, oracle, persophene, spoon boy, switch, "
                      "tank, trinity, woman in red ]");

    // best case scenario, item is at very middle index so search stops in 1 step
    int result = l1.search("morpheus", 0, 19);
    CHECK(result == 9);

    // check bounds conditions
    result = l1.search("agent brown", 0, 19);
    CHECK(result == 0);

    result = l1.search("woman in red", 0, 19);
    CHECK(result == 19);

    // check a few other searches
    result = l1.search("apoc", 0, 19);
    CHECK(result == 2);
    result = l1.search("keymaker", 0, 19);
    CHECK(result == 7);
    result = l1.search("keymaker", 0, 19);
    CHECK(result == 7);
    result = l1.search("spoon boy", 0, 19);
    CHECK(result == 15);

    // we did not define a deterministic result for duplicate items, so which duplicate neo
    // is found will depend on its position
    result = l1.search("neo", 0, 19);
    CHECK(result == 11);

    // can only do this with version that exposes begin and end, this should end up
    // finding duplicate at index 12 instead
    result = l1.search("neo", 1, 19);
    CHECK(result == 12);

    // test failing searches
    result = l1.search("ghost", 0, 19);
    CHECK(result == NOT_FOUND);
    result = l1.search("seraph", 0, 19);
    CHECK(result == NOT_FOUND);
    result = l1.search("noe", 0, 19);
    CHECK(result == NOT_FOUND);
  }
}


/** Task 5: implement the isSorted() member function
 */

TEST_CASE("<List> implement isSorted member function", "[task5]")
{
  SECTION("test list of size 0 and 1")
  {
    // list of size 0, or empty list is sorted
    List l0;
    CHECK(l0.isSorted());

    // list of size 1 is also sorted always
    string l1Values[] = {"neo"};
    List l1(1, l1Values);

    CHECK(l1.isSorted());

    l1[0] = "morpheus";
    CHECK(l1.isSorted());
  }

  SECTION("test specifically for bounds errors when checking last pair of values")
  {
    // create a list that is sorted except last pair, but
    // only use all but last value in creation
    string l1Values[] = {"agent smith", "morpheus", "neo", "oracle", "trinity"};
    List l1(4, l1Values);
    CHECK(l1.isSorted());
  }

  SECTION("test in general sorted detection")
  {
    // not sorted
    string l1Values[] = {"neo", "woman in red", "trinity", "tank", "persophene", "oracle", "spoon boy", "neo", "mouse", "dozer", "morpheus",
      "merovingian", "keymaker", "dujour", "cypher", "architect", "switch", "apoc", "agent smith", "agent brown"};
    List l1(20, l1Values);

    CHECK_FALSE(l1.isSorted());

    // sorted
    l1.sort();
    CHECK(l1.isSorted());

    // not sorted
    l1[0] = "ghost";
    CHECK_FALSE(l1.isSorted());

    // sorted again
    l1.sort();
    CHECK(l1.isSorted());
  }
}


/** Task 5: implement public/private search API
 */

TEST_CASE("<List> implement public/private search member function", "[task5-2]")
{
  SECTION("test base case search, search empty list should fail")
  {
    List l0; // empty list
    int result = l0.search("trinity");
    CHECK(result == NOT_FOUND);
  }

  SECTION("test some general cases on list of 20 values")
  {
    string l1Values[] = {"neo", "woman in red", "trinity", "tank", "persophene", "oracle", "spoon boy", "neo", "mouse", "dozer", "morpheus",
      "merovingian", "keymaker", "dujour", "cypher", "architect", "switch", "apoc", "agent smith", "agent brown"};
    List l1(20, l1Values);

    // list is not sorted, but after first search it should have been sorted for us.
    // best case scenario, item is at very middle index so search stops in 1 step
    int result = l1.search("morpheus");
    CHECK(result == 9);

    // is list now sorted?
    CHECK(l1.str() == "<list> size: 20 [ agent brown, agent smith, apoc, "
                      "architect, cypher, dozer, dujour, keymaker, merovingian, "
                      "morpheus, mouse, neo, neo, oracle, persophene, spoon boy, "
                      "switch, tank, trinity, woman in red ]");

    // check bounds conditions
    result = l1.search("agent brown");
    CHECK(result == 0);

    result = l1.search("woman in red");
    CHECK(result == 19);

    // check a few other searches
    result = l1.search("apoc");
    CHECK(result == 2);
    result = l1.search("keymaker");
    CHECK(result == 7);
    result = l1.search("keymaker");
    CHECK(result == 7);
    result = l1.search("spoon boy");
    CHECK(result == 15);

    // we did not define a deterministic result for duplicate items, so which duplicate neo
    // is found will depend on its position
    result = l1.search("neo");
    CHECK(result == 11);

    // test failing searches
    result = l1.search("ghost");
    CHECK(result == NOT_FOUND);
    result = l1.search("seraph");
    CHECK(result == NOT_FOUND);
    result = l1.search("noe");
    CHECK(result == NOT_FOUND);
  }
}

