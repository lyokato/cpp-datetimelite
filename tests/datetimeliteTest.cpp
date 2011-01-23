#include "datetimelite.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

boost::posix_time::ptime getptime(const std::string& s)
{
   
  struct std::tm ts = datetimelite::time_from_string(s);
  return boost::posix_time::ptime_from_tm(ts);
}

std::string getdatetimestring(const std::string& s)
{
  struct std::tm ts = datetimelite::time_from_string(s);
  std::ostringstream os;
  os << "Year:" << (ts.tm_year + 1900) << "|";
  os << "Month:" << (ts.tm_mon + 1) << "|";
  os << "Day:" << ts.tm_mday << "|";
  os << "Hour:" << ts.tm_hour << "|";
  os << "Min:" << ts.tm_min << "|";
  os << "Sec:" << ts.tm_sec;
  return os.str();
}

TEST(datetimeliteTest, testParse)
{
  EXPECT_EQ("Year:1994|Month:2|Day:9|Hour:22|Min:23|Sec:32", getdatetimestring("Wed, 09 Feb 1994 22:23:32 GMT")) << "HTTP";
  EXPECT_EQ("Year:1994|Month:2|Day:8|Hour:14|Min:15|Sec:29", getdatetimestring("Tuesday, 08-Feb-94 14:15:29 GMT")) << "old RFC850";
  EXPECT_EQ("Year:1994|Month:2|Day:8|Hour:14|Min:15|Sec:29", getdatetimestring("Tuesday, 08-Feb-1994 14:15:29 GMT")) << "broken RFC850";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:17|Min:3|Sec:25255", getdatetimestring("03/Feb/1994:17:03:55 -0700")) << "common log file";
  EXPECT_EQ("Year:1994|Month:2|Day:9|Hour:22|Min:23|Sec:32", getdatetimestring("09 Feb 1994 22:23:32 GMT")) << "HTTP no weekday";
  EXPECT_EQ("Year:1994|Month:2|Day:8|Hour:14|Min:15|Sec:29", getdatetimestring("08-Feb-94 14:15:29 GMT")) << "RFC850 no weekday";
  EXPECT_EQ("Year:1994|Month:2|Day:8|Hour:14|Min:15|Sec:29", getdatetimestring("08-Feb-1994 14:15:29 GMT")) << "broken RFC850 no weekday";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:14|Min:15|Sec:3629", getdatetimestring("1994-02-03 14:15:29 -0100")) << "ISO8601";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:14|Min:15|Sec:-32371", getdatetimestring("1994-02-03 14:15:29+09:00")) << "ISO8601 without space";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:14|Min:15|Sec:-32371", getdatetimestring("1994-02-03 14:15:29+0900")) << "ISO8601 without separator";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:14|Min:15|Sec:-32371", getdatetimestring("1994-02-03 14:15:29.5+0900")) << "ignore floating point";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:14|Min:15|Sec:29", getdatetimestring("1994-02-03 14:15:29")) << "zone is optional";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:0|Min:0|Sec:0", getdatetimestring("1994-02-03")) << "only date";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:14|Min:15|Sec:29", getdatetimestring("1994-02-03T14:15:29")) << "use T separator";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:14|Min:15|Sec:29", getdatetimestring("19940203T141529Z")) << "ISO8601 compact format";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:0|Min:0|Sec:0", getdatetimestring("19940203")) << "only date";
  EXPECT_EQ("Year:1994|Month:2|Day:8|Hour:0|Min:0|Sec:0", getdatetimestring("08-Feb-94")) << "old RFC850 no weekday, no time";
  EXPECT_EQ("Year:1994|Month:2|Day:8|Hour:0|Min:0|Sec:0", getdatetimestring("08-Feb-1994")) << "broken RFC850 no weekday, no time";
  EXPECT_EQ("Year:1994|Month:2|Day:9|Hour:0|Min:0|Sec:0", getdatetimestring("09 Feb 1994")) << "proposed HTTP format";
  EXPECT_EQ("Year:1994|Month:2|Day:3|Hour:0|Min:0|Sec:0", getdatetimestring("03/Feb/1994")) << "common logfile format";
  /*
  EXPECT_EQ("", getdatetimestring("")) << "";
  */
}

TEST(datetimeliteTest, testPtime)
{
  boost::posix_time::ptime t1 = getptime("Wed, 09 Feb 1994 22:23:32 GMT");
  EXPECT_EQ("1994-Feb-09 22:23:32", boost::posix_time::to_simple_string(t1));
  boost::posix_time::ptime t2 = getptime("1994-02-03T14:15:29 +09:00");
  EXPECT_EQ("1994-Feb-02 00:45:29", boost::posix_time::to_simple_string(t2));
}

