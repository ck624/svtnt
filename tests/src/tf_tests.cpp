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
	std::string testcase = testing::UnitTest::GetInstance()->current_test_info()->test_case_name();
	std::string test = testing::UnitTest::GetInstance()->current_test_info()->name();
	SVTNT svtnt;
	std::istringstream in(doc);


	ASSERT_TRUE(svtnt.parse(in, testcase + "." + test));
	ASSERT_TRUE(svtnt.link());
	ASSERT_TRUE(svtnt.generate(testcase + "." + test + "/outdir"));
}

TEST(tf_tests, func) {
	const char *doc = R"(
      package my_pkg;
        function void doit();
			for (int i=0; i<10; i++) begin
				$display("Hello World!!");
			end
        endfunction
      endpackage
			)";

	run_test(doc);
}

TEST(tf_tests, task) {
	const char *doc = R"(
      package my_pkg;
        task doit();
        endtask
      endpackage
			)";

	run_test(doc);
}

TEST(tf_tests, task_params) {
	const char *doc = R"(
      package my_pkg;
        task doit(string msg, int count);
        endtask
      endpackage
			)";

	run_test(doc);
}

TEST(tf_tests, ext_variadic_params) {
	const char *doc = R"(
      package my_pkg;
        function void variadic(string msg, ...);
        endfunction
      endpackage
			)";

	run_test(doc);
}

TEST(tf_tests, svtnt_import) {
	const char *doc = R"(
      package svtnt_pkg;
        import "SVTNT" __svtnt_display=function void \$display (string msg, ...);
      endpackage
      package my_pkg;
       function void doit();
         svtnt_pkg::doit();
       endfunction
      endpackage
			)";

	run_test(doc);
}

TEST(tf_tests, escaped_identifiers) {
	const char *doc = R"(
      package my_pkg;
        function void \$display (string msg, ...);
        endfunction
      endpackage
			)";

	run_test(doc);
}

TEST(tf_tests, cls) {
	const char *doc = R"(
      package my_pkg;
        class c1;
			rand int a;
        endclass
      endpackage
			)";

	run_test(doc);
}


