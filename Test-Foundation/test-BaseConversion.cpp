#include "pch.h"
#include <Base-Conversion.h>




TEST(Base64, HelloWorld) {

	const char* zString = "Hello, World!";



	const char* zBase64 = "SGVsbG8sIFdvcmxkIQ==";

	EXPECT_EQ(sec::toBase64(zString), std::string_view(zBase64));

	EXPECT_EQ(sec::toBase64url(zString), std::string_view(zBase64));
}

TEST(Base64, OneLetterEncode)
{
	const char* zString = "z";

	const char* zBase64 = "eg==";

	EXPECT_EQ(sec::toBase64(zString), std::string_view(zBase64));

	EXPECT_EQ(sec::toBase64url(zString), std::string_view(zBase64));
}

TEST(Base64, TwoLetterEncode)
{
	const char* zString = "yz";

	const char* zBase64 = "eXo=";

	EXPECT_EQ(sec::toBase64(zString), std::string_view(zBase64));

	EXPECT_EQ(sec::toBase64url(zString), std::string_view(zBase64));
}

TEST(Base64, ThreeLetterEncode)
{
	const char* zString = "xyz";

	const char* zBase64 = "eHl6"; // Calculated from already existing tool.

	EXPECT_EQ(sec::toBase64(zString), std::string_view(zBase64));

	EXPECT_EQ(sec::toBase64url(zString), std::string_view(zBase64));
}