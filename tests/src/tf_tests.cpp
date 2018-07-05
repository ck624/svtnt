/*
 * tf_tests.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#include "gtest/gtest.h"
#include <string>
#include <iostream>
#include "SVTNT.h"

static void run_test(const std::string &doc) {
	std::string test = testing::UnitTest::GetInstance()->current_test_info()->name();
	SVTNT svtnt;
	std::istringstream in(doc);


	ASSERT_TRUE(svtnt.parse(in, test));
	ASSERT_TRUE(svtnt.generate("outdir"));
}

TEST(tf_tests, func) {
	const char *doc = R"(
      package my_pkg;
        function void doit();
        endfunction
      endpackage
			)";

	run_test(doc);

}


