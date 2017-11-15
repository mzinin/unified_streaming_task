#include "../error.hpp"
#include "../payload_parser.hpp"

#include <iostream>
#include <set>
#include <sstream>
#include <vector>


// audio payloads and raw data
namespace
{
	const uint16_t audioPid = 0x22;

	const std::vector<uint8_t> audioPayload1{ 0x00, 0x00, 0x01, 0xC0, 0x0A, 0xF5, 0x84, 0x80, 0x05, 0x21, 0x00, 0x37, 0x77, 0x41, 0xFF, 0xF1,
		                                      0x4C, 0x80, 0x04, 0x3F, 0xFC, 0xDE, 0x04, 0x00, 0x00, 0x6C, 0x69, 0x62, 0x66, 0x61, 0x61, 0x63,
		                                      0x20, 0x31, 0x2E, 0x32, 0x38, 0x00, 0x00, 0x42, 0x00, 0x93, 0x20, 0x04, 0x32, 0x00, 0x47, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF,
		                                      0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC };

	const std::vector<uint8_t> audioRawData1{ 0xFF, 0xF1, 0x4C, 0x80, 0x04, 0x3F, 0xFC, 0xDE, 0x04, 0x00, 0x00, 0x6C, 0x69, 0x62, 0x66, 0x61,
		                                      0x61, 0x63, 0x20, 0x31, 0x2E, 0x32, 0x38, 0x00, 0x00, 0x42, 0x00, 0x93, 0x20, 0x04, 0x32, 0x00,
		                                      0x47, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23,
		                                      0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23,
		                                      0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23,
		                                      0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23,
		                                      0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23,
		                                      0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23,
		                                      0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23,
		                                      0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC, 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23,
		                                      0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC };

	const std::vector<uint8_t> audioPayload2{ 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23 };

	const std::vector<uint8_t> audioRawData2{ 0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23, 0x80, 0xFF, 0xF1, 0x4C, 0x80, 0x02, 0x1F, 0xFC,
		                                      0x21, 0x00, 0x49, 0x90, 0x02, 0x19, 0x00, 0x23 };
}

// video payloads and raw data
namespace
{
	const uint16_t videoPid = 0x21;

	const std::vector<uint8_t> videoPayload1{ 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x84, 0x80, 0x05, 0x21, 0x00, 0x37, 0x77, 0x41, 0x00, 0x00,
		                                      0x00, 0x01, 0x09, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0xC0, 0x14, 0xDB, 0x04, 0x04, 0xE8,
		                                      0x40, 0x00, 0xCB, 0x73, 0x40, 0x26, 0x25, 0xA0, 0x07, 0xC5, 0x0A, 0xB8, 0x00, 0x00, 0x00, 0x01,
		                                      0x68, 0xCA, 0x8C, 0xB2, 0x00, 0x00, 0x01, 0x06, 0x05, 0xFF, 0xFF, 0x66, 0xDC, 0x45, 0xE9, 0xBD,
		                                      0xE6, 0xD9, 0x48, 0xB7, 0x96, 0x2C, 0xD8, 0x20, 0xD9, 0x23, 0xEE, 0xEF, 0x78, 0x32, 0x36, 0x34,
		                                      0x20, 0x2D, 0x20, 0x63, 0x6F, 0x72, 0x65, 0x20, 0x31, 0x32, 0x30, 0x20, 0x72, 0x32, 0x31, 0x35,
		                                      0x31, 0x20, 0x61, 0x33, 0x66, 0x34, 0x34, 0x30, 0x37, 0x20, 0x2D, 0x20, 0x48, 0x2E, 0x32, 0x36,
		                                      0x34, 0x2F, 0x4D, 0x50, 0x45, 0x47, 0x2D, 0x34, 0x20, 0x41, 0x56, 0x43, 0x20, 0x63, 0x6F, 0x64,
		                                      0x65, 0x63, 0x20, 0x2D, 0x20, 0x43, 0x6F, 0x70, 0x79, 0x6C, 0x65, 0x66, 0x74, 0x20, 0x32, 0x30,
		                                      0x30, 0x33, 0x2D, 0x32, 0x30, 0x31, 0x31, 0x20, 0x2D, 0x20, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F,
		                                      0x2F, 0x77, 0x77, 0x77, 0x2E, 0x76, 0x69, 0x64, 0x65, 0x6F, 0x6C, 0x61, 0x6E, 0x2E, 0x6F, 0x72 };

	const std::vector<uint8_t> videoRawData1{ 0x00, 0x00, 0x00, 0x01, 0x09, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0xC0, 0x14, 0xDB, 0x04,
		                                      0x04, 0xE8, 0x40, 0x00, 0xCB, 0x73, 0x40, 0x26, 0x25, 0xA0, 0x07, 0xC5, 0x0A, 0xB8, 0x00, 0x00,
		                                      0x00, 0x01, 0x68, 0xCA, 0x8C, 0xB2, 0x00, 0x00, 0x01, 0x06, 0x05, 0xFF, 0xFF, 0x66, 0xDC, 0x45,
		                                      0xE9, 0xBD, 0xE6, 0xD9, 0x48, 0xB7, 0x96, 0x2C, 0xD8, 0x20, 0xD9, 0x23, 0xEE, 0xEF, 0x78, 0x32,
		                                      0x36, 0x34, 0x20, 0x2D, 0x20, 0x63, 0x6F, 0x72, 0x65, 0x20, 0x31, 0x32, 0x30, 0x20, 0x72, 0x32,
		                                      0x31, 0x35, 0x31, 0x20, 0x61, 0x33, 0x66, 0x34, 0x34, 0x30, 0x37, 0x20, 0x2D, 0x20, 0x48, 0x2E,
		                                      0x32, 0x36, 0x34, 0x2F, 0x4D, 0x50, 0x45, 0x47, 0x2D, 0x34, 0x20, 0x41, 0x56, 0x43, 0x20, 0x63,
		                                      0x6F, 0x64, 0x65, 0x63, 0x20, 0x2D, 0x20, 0x43, 0x6F, 0x70, 0x79, 0x6C, 0x65, 0x66, 0x74, 0x20,
		                                      0x32, 0x30, 0x30, 0x33, 0x2D, 0x32, 0x30, 0x31, 0x31, 0x20, 0x2D, 0x20, 0x68, 0x74, 0x74, 0x70,
		                                      0x3A, 0x2F, 0x2F, 0x77, 0x77, 0x77, 0x2E, 0x76, 0x69, 0x64, 0x65, 0x6F, 0x6C, 0x61, 0x6E, 0x2E,
		                                      0x6F, 0x72 };

	const std::vector<uint8_t> videoPayload2{ 0x67, 0x2F, 0x78, 0x32, 0x36, 0x34, 0x2E, 0x68, 0x74, 0x6D, 0x6C, 0x20, 0x2D, 0x20, 0x6F, 0x70,
		                                      0x74, 0x69, 0x6F, 0x6E, 0x73, 0x3A, 0x20, 0x63, 0x61, 0x62, 0x61, 0x63, 0x3D, 0x30, 0x20, 0x72,
		                                      0x65, 0x66, 0x3D, 0x32, 0x20, 0x64, 0x65, 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x3D, 0x31, 0x3A, 0x30,
		                                      0x3A, 0x30, 0x20, 0x61, 0x6E, 0x61, 0x6C, 0x79, 0x73, 0x65, 0x3D, 0x30, 0x78, 0x31, 0x3A, 0x30,
		                                      0x78, 0x31, 0x31, 0x31, 0x20, 0x6D, 0x65, 0x3D, 0x68, 0x65, 0x78, 0x20, 0x73, 0x75, 0x62, 0x6D,
		                                      0x65, 0x3D, 0x36, 0x20, 0x70, 0x73, 0x79, 0x3D, 0x31, 0x20, 0x70, 0x73, 0x79, 0x5F, 0x72, 0x64,
		                                      0x3D, 0x31, 0x2E, 0x30, 0x30, 0x3A, 0x30, 0x2E, 0x30, 0x30, 0x20, 0x6D, 0x69, 0x78, 0x65, 0x64,
		                                      0x5F, 0x72, 0x65, 0x66, 0x3D, 0x31, 0x20, 0x6D, 0x65, 0x5F, 0x72, 0x61, 0x6E, 0x67, 0x65, 0x3D,
		                                      0x31, 0x36, 0x20, 0x63, 0x68, 0x72, 0x6F, 0x6D, 0x61, 0x5F, 0x6D, 0x65, 0x3D, 0x31, 0x20, 0x74,
		                                      0x72, 0x65, 0x6C, 0x6C, 0x69, 0x73, 0x3D, 0x31, 0x20, 0x38, 0x78, 0x38, 0x64, 0x63, 0x74, 0x3D,
		                                      0x30, 0x20, 0x63, 0x71, 0x6D, 0x3D, 0x30, 0x20, 0x64, 0x65, 0x61, 0x64, 0x7A, 0x6F, 0x6E, 0x65,
		                                      0x3D, 0x32, 0x31, 0x2C, 0x31, 0x31, 0x20, 0x66 };

	const std::vector<uint8_t> videoRawData2{ 0x67, 0x2F, 0x78, 0x32, 0x36, 0x34, 0x2E, 0x68, 0x74, 0x6D, 0x6C, 0x20, 0x2D, 0x20, 0x6F, 0x70,
		                                      0x74, 0x69, 0x6F, 0x6E, 0x73, 0x3A, 0x20, 0x63, 0x61, 0x62, 0x61, 0x63, 0x3D, 0x30, 0x20, 0x72,
		                                      0x65, 0x66, 0x3D, 0x32, 0x20, 0x64, 0x65, 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x3D, 0x31, 0x3A, 0x30,
		                                      0x3A, 0x30, 0x20, 0x61, 0x6E, 0x61, 0x6C, 0x79, 0x73, 0x65, 0x3D, 0x30, 0x78, 0x31, 0x3A, 0x30,
		                                      0x78, 0x31, 0x31, 0x31, 0x20, 0x6D, 0x65, 0x3D, 0x68, 0x65, 0x78, 0x20, 0x73, 0x75, 0x62, 0x6D,
		                                      0x65, 0x3D, 0x36, 0x20, 0x70, 0x73, 0x79, 0x3D, 0x31, 0x20, 0x70, 0x73, 0x79, 0x5F, 0x72, 0x64,
		                                      0x3D, 0x31, 0x2E, 0x30, 0x30, 0x3A, 0x30, 0x2E, 0x30, 0x30, 0x20, 0x6D, 0x69, 0x78, 0x65, 0x64,
		                                      0x5F, 0x72, 0x65, 0x66, 0x3D, 0x31, 0x20, 0x6D, 0x65, 0x5F, 0x72, 0x61, 0x6E, 0x67, 0x65, 0x3D,
		                                      0x31, 0x36, 0x20, 0x63, 0x68, 0x72, 0x6F, 0x6D, 0x61, 0x5F, 0x6D, 0x65, 0x3D, 0x31, 0x20, 0x74,
		                                      0x72, 0x65, 0x6C, 0x6C, 0x69, 0x73, 0x3D, 0x31, 0x20, 0x38, 0x78, 0x38, 0x64, 0x63, 0x74, 0x3D,
		                                      0x30, 0x20, 0x63, 0x71, 0x6D, 0x3D, 0x30, 0x20, 0x64, 0x65, 0x61, 0x64, 0x7A, 0x6F, 0x6E, 0x65,
		                                      0x3D, 0x32, 0x31, 0x2C, 0x31, 0x31, 0x20, 0x66 };
}

// other payloads
namespace
{
	const uint16_t subsPid = 0x400;

	const std::vector<uint8_t> subsPayload1{ 0x00, 0x00, 0x01, 0xBD, 0x59, 0xD5, 0x84, 0x80, 0x05, 0x21, 0x00, 0x3B, 0x76, 0x85, 0x20, 0x00,
		                                     0x0F, 0x14, 0x00, 0x02, 0x00, 0x08, 0x10, 0x07, 0x7F, 0x04, 0x37, 0x00, 0x00, 0x00, 0x0F, 0x10,
		                                     0x00, 0x02, 0x00, 0x0E, 0x1E, 0x08, 0x00, 0xFF, 0x00, 0x00, 0x03, 0x8A, 0x01, 0xFF, 0x00, 0x00,
		                                     0x03, 0xC8, 0x0F, 0x11, 0x00, 0x02, 0x00, 0x10, 0x00, 0x08, 0x07, 0x80, 0x00, 0x3E, 0x48, 0x00,
		                                     0x00, 0x00, 0x00, 0x00, 0x02, 0x38, 0x00, 0x00, 0x0F, 0x11, 0x00, 0x02, 0x00, 0x10, 0x01, 0x08,
		                                     0x07, 0x80, 0x00, 0x3E, 0x48, 0x01, 0x00, 0x00, 0x00, 0x01, 0x02, 0x78, 0x00, 0x00, 0x0F, 0x11,
		                                     0x00, 0x02, 0x00, 0x0A, 0x02, 0x18, 0x07, 0x80, 0x00, 0x3E, 0x48, 0x02, 0x00, 0x00, 0x0F, 0x11,
		                                     0x00, 0x02, 0x00, 0x0A, 0x03, 0x18, 0x07, 0x80, 0x00, 0x3E, 0x48, 0x03, 0x00, 0x00, 0x0F, 0x12,
		                                     0x00, 0x02, 0x00, 0x62, 0x00, 0x0F, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x01, 0x41, 0xDC, 0x00,
		                                     0x00, 0x00, 0x02, 0x41, 0x10, 0x80, 0x80, 0xFF, 0x03, 0x41, 0x10, 0x80, 0x80, 0xD5, 0x04, 0x41,
		                                     0x10, 0x80, 0x80, 0xAA, 0x05, 0x41, 0x10, 0x80, 0x80, 0x80, 0x06, 0x41, 0x10, 0x80, 0x80, 0x55,
		                                     0x07, 0x41, 0x10, 0x80, 0x80, 0x2B, 0x08, 0x41 };
}

namespace
{
	/// @brief Expected result for PayloadParser test.
	struct ExpectedResult
	{
		/// @brief Error code. If OK - no error expected.
		uint16_t errorCode;

		/// @brief Number of audio streams in output.
		uint16_t audioStreams;

		/// @brief Number of video streams in output.
		uint16_t videoStreams;

		/// @brief Raw audio output.
		std::string audioRawData;

		/// @brief Raw audio output.
		std::string videoRawData;
	};

	/// @brief Run one PayloadParser unit test.
	/// @returns true if test passed, false otherwise.
	bool runTest(const std::string& testName,
		         const std::vector<TsPayload>& input,
				 const ExpectedResult& expected)
	{
		std::cout << "Running PayloadParser." << testName << " ... ";

		bool result = true;
		Error error{ Error::OK, "" };
		std::set<uint16_t> audioStreams;
		std::set<uint16_t> videoStreams;
		std::ostringstream audioRawData;
		std::ostringstream videoRawData;
		std::ostringstream log;
		auto handler = [&audioStreams, &videoStreams, &audioRawData, &videoRawData](const EsRawData& rd)
		{
			if (rd.type == EsType::AUDIO)
			{
				audioStreams.insert(rd.esNumber);
				audioRawData.write(reinterpret_cast<const char*>(rd.data), rd.size);
			}
			else if (rd.type == EsType::VIDEO)
			{
				videoStreams.insert(rd.esNumber);
				videoRawData.write(reinterpret_cast<const char*>(rd.data), rd.size);
			}
		};

		try
		{
			PayloadParser parser(log, handler);
			for (const auto& payload : input)
				parser.parse(payload);
		}
		catch (const Error& err)
		{
			error = err;
		}
		catch (const std::exception& e)
		{
			result = false;
			log << "Unexpected exception caught: " << e.what() << std::endl;
		}

		if (error.code() != expected.errorCode)
		{
			result = false;
			if (expected.errorCode == Error::OK)
				log << "Unexpected exception caught: " << error.message() << std::endl;
			else
				log << "No expected exception caught" << std::endl;
		}
		if (audioStreams.size() != expected.audioStreams)
		{
			result = false;
			log << "Got " << audioStreams.size() << " audio streams instead of " << expected.audioStreams << std::endl;
		}
		if (videoStreams.size() != expected.videoStreams)
		{
			result = false;
			log << "Got " << videoStreams.size() << " video streams instead of " << expected.videoStreams << std::endl;
		}
		if (audioRawData.str() != expected.audioRawData)
		{
			result = false;
			log << "Produced audio raw data differs from expected" << std::endl;
		}
		if (videoRawData.str() != expected.videoRawData)
		{
			result = false;
			log << "Produced video raw data differs from expected" << std::endl;
		}

		std::cout << (result ? "OK" : "FAIL") << std::endl;
		if (!result)
			std::cout << log.str();
		return result;
	}
}

/// @brief Run all PayloadParser unit tests.
/// @returns Number of failed tests.
uint16_t testPayloadParser()
{
	uint16_t failures = 0;

	// 1 video payload with header
	std::vector<TsPayload> payloads;
	payloads.push_back({ videoPayload1.data(), static_cast<uint16_t>(videoPayload1.size()), videoPid });
	std::ostringstream videoRawData;
	videoRawData.write(reinterpret_cast<const char*>(videoRawData1.data()), videoRawData1.size());
	ExpectedResult expected = { Error::OK, 0, 1, "", videoRawData.str() };
	failures += 1 - runTest("parse_Video1PayloadWithHeader_OK", payloads, expected);

	// 1 video payload without header
	payloads.clear();
	payloads.push_back({ videoPayload2.data(), static_cast<uint16_t>(videoPayload2.size()), videoPid });
	expected = { Error::OK, 0, 0, "", "" };
	failures += 1 - runTest("parse_Video1PayloadWithoutHeader_OK", payloads, expected);

	// 2 video payloads with header
	payloads.clear();
	payloads.push_back({ videoPayload1.data(), static_cast<uint16_t>(videoPayload1.size()), videoPid });
	payloads.push_back({ videoPayload2.data(), static_cast<uint16_t>(videoPayload2.size()), videoPid });
	videoRawData.swap(std::ostringstream());
	videoRawData.write(reinterpret_cast<const char*>(videoRawData1.data()), videoRawData1.size());
	videoRawData.write(reinterpret_cast<const char*>(videoRawData2.data()), videoRawData2.size());
	expected = { Error::OK, 0, 1, "", videoRawData.str() };
	failures += 1 - runTest("parse_Video2PayloadsWithHeader_OK", payloads, expected);

	// 2 video payloads without header
	payloads.clear();
	payloads.push_back({ videoPayload2.data(), static_cast<uint16_t>(videoPayload2.size()), videoPid });
	payloads.push_back({ videoPayload1.data(), static_cast<uint16_t>(videoPayload1.size()), videoPid });
	videoRawData.swap(std::ostringstream());
	videoRawData.write(reinterpret_cast<const char*>(videoRawData1.data()), videoRawData1.size());
	expected = { Error::OK, 0, 1, "", videoRawData.str() };
	failures += 1 - runTest("parse_Video2PayloadsWithoutHeader_OK", payloads, expected);

	// 1 audio payload with header
	payloads.clear();
	payloads.push_back({ audioPayload1.data(), static_cast<uint16_t>(audioPayload1.size()), audioPid });
	std::ostringstream audioRawData;
	audioRawData.write(reinterpret_cast<const char*>(audioRawData1.data()), audioRawData1.size());
	expected = { Error::OK, 1, 0, audioRawData.str(), "" };
	failures += 1 - runTest("parse_Audio1PayloadWithHeader_OK", payloads, expected);

	// audio and video payloads with header
	payloads.clear();
	payloads.push_back({ videoPayload1.data(), static_cast<uint16_t>(videoPayload1.size()), videoPid });
	payloads.push_back({ audioPayload1.data(), static_cast<uint16_t>(audioPayload1.size()), audioPid });
	payloads.push_back({ videoPayload2.data(), static_cast<uint16_t>(videoPayload2.size()), videoPid });
	payloads.push_back({ audioPayload2.data(), static_cast<uint16_t>(audioPayload2.size()), audioPid });
	videoRawData.swap(std::ostringstream());
	videoRawData.write(reinterpret_cast<const char*>(videoRawData1.data()), videoRawData1.size());
	videoRawData.write(reinterpret_cast<const char*>(videoRawData2.data()), videoRawData2.size());
	audioRawData.swap(std::ostringstream());
	audioRawData.write(reinterpret_cast<const char*>(audioRawData1.data()), audioRawData1.size());
	audioRawData.write(reinterpret_cast<const char*>(audioRawData2.data()), audioRawData2.size());
	expected = { Error::OK, 1, 1, audioRawData.str(), videoRawData.str() };
	failures += 1 - runTest("parse_AudioAndVideoPayloadsWithHeader_OK", payloads, expected);

	// 2 stream ids in 1 pid
	payloads.clear();
	payloads.push_back({ videoPayload1.data(), static_cast<uint16_t>(videoPayload1.size()), videoPid });
	payloads.push_back({ videoPayload2.data(), static_cast<uint16_t>(videoPayload2.size()), audioPid });
	videoRawData.swap(std::ostringstream());
	videoRawData.write(reinterpret_cast<const char*>(videoRawData1.data()), videoRawData1.size());
	expected = { Error::OK, 0, 1, "", videoRawData.str() };
	failures += 1 - runTest("parse_TwoStreamIdsInOnePid_OK", payloads, expected);

	// video and subtitles payloads with header
	payloads.clear();
	payloads.push_back({ videoPayload1.data(), static_cast<uint16_t>(videoPayload1.size()), videoPid });
	payloads.push_back({ subsPayload1.data(), static_cast<uint16_t>(subsPayload1.size()), audioPid });
	payloads.push_back({ videoPayload2.data(), static_cast<uint16_t>(videoPayload2.size()), videoPid });
	videoRawData.swap(std::ostringstream());
	videoRawData.write(reinterpret_cast<const char*>(videoRawData1.data()), videoRawData1.size());
	videoRawData.write(reinterpret_cast<const char*>(videoRawData2.data()), videoRawData2.size());
	expected = { Error::OK, 0, 1, "", videoRawData.str() };
	failures += 1 - runTest("parse_VideoAndSubsPayloadsWithHeader_OK", payloads, expected);

	return failures;
}
