/*
 *  test-serialization.h
 *  Parthenon
 *
 *  Created by Ed Zavada on 4/10/10.
 *  Copyright 2010 Dream Rock Studios, LLC. All rights reserved.
 *
 */

#ifndef PDG_TEST_SERIALIZATION
#define PDG_TEST_SERIALIZATION

//#include <cppunit/TestCase.h>
#include <string>

namespace pdg_test {
	
class SerializationTest /*: public CppUnit::TestCase*/ { 
public: 
	SerializationTest( std::string name ) /*: CppUnit::TestCase( name )*/ {}
	
	void runTest();
};

}

#endif // PDG_TEST_SERIALIZATION