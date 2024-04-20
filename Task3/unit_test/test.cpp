#include "pch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include"text_processing.h"

using namespace std;

TEST(InputTest, IncorrectSignatureTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "", "", "", ""};
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "Incorrect input signature";
	cerr.rdbuf(oldCoutStreamBuf);
	
	EXPECT_EQ(content, expected);
}

TEST(InputTest, IncorrectSignatureExitCodeTest) {
	const char* argv[] = { "text_processing", "", "", "", "" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 1);
}

TEST(InputTest, IncorrectStraregyTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "some_cipher", "encryption", "TextToEncrypt", "2" };
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "Incorrect strategy";
	cerr.rdbuf(oldCoutStreamBuf);

	EXPECT_EQ(content, expected);
}

TEST(InputTest, IncorrectStraregyExitCodeTest) {
	const char* argv[] = { "text_processing", "some_cipher", "encryption", "TextToEncrypt", "2" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 1);
}

TEST(InputTest, IncorrectKeyTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "caesar_cipher", "encryption", "TextToEncrypt", "not_key" };
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "Incorrect key format";
	cerr.rdbuf(oldCoutStreamBuf);

	EXPECT_EQ(content, expected);
}

TEST(InputTest, IncorrectKeyExitCodeTest) {
	const char* argv[] = { "text_processing", "caesar_cipher", "encryption", "TextToEncrypt", "not_key" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 1);
}

TEST(InputTest, IncorrectFunctionTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "caesar_cipher", "recryption", "TextToEncrypt", "2" };
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "Incorrect function";
	cerr.rdbuf(oldCoutStreamBuf);

	EXPECT_EQ(content, expected);
}

TEST(InputTest, IncorrectFunctionExitCodeTest) {
	const char* argv[] = { "text_processing", "caesar_cipher", "recryption", "TextToEncrypt", "2" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 1);
}

TEST(InputTest, UnsupportedTextTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "caesar_cipher", "encryption", "22:47!", "2" };
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "Unsupported text";
	cerr.rdbuf(oldCoutStreamBuf);

	EXPECT_EQ(content, expected);
}

TEST(InputTest, UnsupportedTextExitCodeTest) {
	const char* argv[] = { "text_processing", "caesar_cipher", "encryption", "22:47!", "2" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 1);
}

TEST(EncryptionTest, CaesarCipherEncryptionTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "caesar_cipher", "encryption", "TextToEncrypt", "2" };
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "VgzvVqGpetarv";
	cerr.rdbuf(oldCoutStreamBuf);

	EXPECT_EQ(content, expected);
}

TEST(EncryptionTest, CaesarCipherEncryptionExitCodeTest) {
	const char* argv[] = { "text_processing", "caesar_cipher", "encryption", "TextToEncrypt", "2" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 0);
}

TEST(EncryptionTest, RailFenceCipherEncryptionTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "rail_fence_cipher", "encryption", "TextToEncrypt", "4" };
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "TEteonpxTcytr";
	cerr.rdbuf(oldCoutStreamBuf);

	EXPECT_EQ(content, expected);
}

TEST(EncryptionTest, RailFenceCipherEncryptionExitCodeTest) {
	const char* argv[] = { "text_processing", "rail_fence_cipher", "encryption", "TextToEncrypt", "4" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 0);
}

TEST(DecryptionTest, CaesarCipherDecryptionTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "caesar_cipher", "decryption", "VgzvVqGpetarv", "2" };
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "TextToEncrypt";
	cerr.rdbuf(oldCoutStreamBuf);

	EXPECT_EQ(content, expected);
}

TEST(DecryptionTest, CaesarCipherDecryptionExitCodeTest) {
	const char* argv[] = { "text_processing", "caesar_cipher", "decryption", "VgzvVqGpetarv", "2" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 0);
}

TEST(DecryptionTest, RailFenceCipherDecryptionTest) {
	streambuf* oldCoutStreamBuf = cerr.rdbuf();
	stringstream stringStream;
	cerr.rdbuf(stringStream.rdbuf());

	const char* argv[] = { "text_processing", "rail_fence_cipher", "decryption", "TEteonpxTcytr", "4" };
	int argc = 1;
	text_processing(argc, argv);

	string content = stringStream.str();
	string expected = "TextToEncrypt";
	cerr.rdbuf(oldCoutStreamBuf);

	EXPECT_EQ(content, expected);
}

TEST(DecryptionTest, RailFenceCipherDecryptionExitCodeTest) {
	const char* argv[] = { "text_processing", "rail_fence_cipher", "decryption", "TEteonpxTcytr", "4" };
	int argc = 1;
	int code;
	code = text_processing(argc, argv);

	EXPECT_EQ(code, 0);
}