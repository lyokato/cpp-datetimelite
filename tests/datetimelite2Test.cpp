#include "datetimelite2.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>


TEST(datetimeliteTest, testPtime)
{
  boost::optional<boost::posix_time::ptime> t1 = datetimelite2::time_from_string("Wed, 09 Feb 1994 22:23:32 GMT");
  EXPECT_EQ("1994-Feb-09 22:23:32", boost::posix_time::to_simple_string(*t1));
  boost::optional<boost::posix_time::ptime> t2 = datetimelite2::time_from_string("1994-02-03T14:15:29 +09:00");
  EXPECT_EQ("1994-Feb-02 00:45:29", boost::posix_time::to_simple_string(*t2));

  boost::optional<boost::posix_time::ptime> t3 = datetimelite2::time_from_string("invalid format");
  EXPECT_FALSE(t3);
}

