#include <xinu.h>

byte bbb_macs[84][6] = {{0x6c, 0xec, 0xeb, 0xab, 0x0a, 0xce} , {0x6c, 0xec, 0xeb, 0xbb, 0x4a, 0x27},
	                     {0x6c, 0xec, 0xeb, 0xad, 0x9c, 0x6f} , {0x6c, 0xec, 0xeb, 0xaf, 0x13, 0x9f},
                             {0x6c, 0xec, 0xeb, 0xad, 0x68, 0xf2} , {0x6c, 0xec, 0xeb, 0xac, 0x73, 0xa3},
			     {0x6c, 0xec, 0xeb, 0xaf, 0xdb, 0xa4} , {0x6c, 0xec, 0xeb, 0xab, 0x0a, 0xbc},
			     {0xd0, 0x5f, 0xb8, 0xe7, 0xa5, 0xb6} , {0x6c, 0xec, 0xeb, 0xab, 0x07, 0xcd},
			     {0x6c, 0xec, 0xeb, 0xa5, 0xb3, 0x80} , {0x6c, 0xec, 0xeb, 0xaf, 0x39, 0x60},
			     {0x6c, 0xec, 0xeb, 0xab, 0x03, 0xde} , {0x6c, 0xec, 0xeb, 0xab, 0x07, 0xd3},
			     {0x6c, 0xec, 0xeb, 0xab, 0x0a, 0x98} , {0x6c, 0xec, 0xeb, 0xab, 0x36, 0x1a},
		             {0x6c, 0xec, 0xeb, 0xac, 0x51, 0x11} , {0x6c, 0xec, 0xeb, 0xab, 0x36, 0x11},
			     {0x6c, 0xec, 0xeb, 0xac, 0x54, 0x36} , {0x6c, 0xec, 0xeb, 0xab, 0x03, 0xbd},
			     {0xd0, 0x5f, 0xb8, 0xe7, 0xa8, 0x2b} , {0x6c, 0xec, 0xeb, 0xb9, 0xff, 0x2c},
			     {0x6c, 0xec, 0xeb, 0xae, 0xb5, 0xfd} , {0x6c, 0xec, 0xeb, 0xae, 0xbc, 0xbd},
			     {0x6c, 0xec, 0xeb, 0xab, 0x5a, 0xa2} , {0x6c, 0xec, 0xeb, 0xac, 0x54, 0x45},
			     {0x6c, 0xec, 0xeb, 0xac, 0x63, 0x1c} , {0x6c, 0xec, 0xeb, 0xae, 0xe9, 0xff},
			     {0x6c, 0xec, 0xeb, 0xad, 0x94, 0x99} , {0x6c, 0xec, 0xeb, 0xad, 0xcc, 0x02},
			     {0x6c, 0xec, 0xeb, 0xac, 0x78, 0x78} , {0x6c, 0xec, 0xeb, 0xae, 0xf7, 0x5c},
			     {0x6c, 0xec, 0xeb, 0xbb, 0x59, 0xb7} , {0x6c, 0xec, 0xeb, 0xab, 0x12, 0x91},
			     {0x6c, 0xec, 0xeb, 0xac, 0x63, 0x5b} , {0x6c, 0xec, 0xeb, 0xab, 0x0d, 0x5e},
			     {0x6c, 0xec, 0xeb, 0xae, 0xf7, 0x3e} , {0x6c, 0xec, 0xeb, 0xab, 0x07, 0xd0},
			     {0x6c, 0xec, 0xeb, 0xac, 0x26, 0xe7} , {0x6c, 0xec, 0xeb, 0xab, 0x3f, 0x97},
			     {0x6c, 0xec, 0xeb, 0xab, 0x58, 0xa4} , {0x6c, 0xec, 0xeb, 0xb0, 0x24, 0x64},
			     {0x6c, 0xec, 0xeb, 0xab, 0x07, 0xf4} , {0x6c, 0xec, 0xeb, 0xba, 0x15, 0x53},
			     {0x6c, 0xec, 0xeb, 0xad, 0x9c, 0x3f} , {0x6c, 0xec, 0xeb, 0xab, 0x3f, 0xb8},
			     {0x6c, 0xec, 0xeb, 0xbb, 0x5c, 0x02} , {0x6c, 0xec, 0xeb, 0xad, 0x9a, 0xec},
			     {0x6c, 0xec, 0xeb, 0xab, 0x03, 0xd8} , {0x6c, 0xec, 0xeb, 0xab, 0x36, 0x29},
			     {0x6c, 0xec, 0xeb, 0xba, 0x09, 0x12} , {0x6c, 0xec, 0xeb, 0xba, 0x05, 0x25},
			     {0x6c, 0xec, 0xeb, 0xab, 0x32, 0x43} , {0x6c, 0xec, 0xeb, 0xab, 0xed, 0x0f},
			     {0x6c, 0xec, 0xeb, 0xab, 0x6a, 0x92} , {0x6c, 0xec, 0xeb, 0xad, 0x68, 0x49},
			     {0x6c, 0xec, 0xeb, 0xb9, 0xd2, 0xb0} , {0x6c, 0xec, 0xeb, 0xbb, 0x4a, 0x5a},
			     {0x78, 0xa5, 0x04, 0xef, 0x72, 0x00} , {0x6c, 0xec, 0xeb, 0xac, 0x58, 0xea},
			     {0x6c, 0xec, 0xeb, 0xba, 0x1a, 0xb7} , {0x6c, 0xec, 0xeb, 0xab, 0x07, 0x8b},
			     {0x54, 0x4a, 0x16, 0xc1, 0x65, 0x18} , {0x6c, 0xec, 0xeb, 0xbb, 0x59, 0xe1},
			     {0x78, 0xa5, 0x04, 0xed, 0xd9, 0x95} , {0x6c, 0xec, 0xeb, 0xaf, 0x09, 0x70},
			     {0x78, 0xa5, 0x04, 0xfd, 0xac, 0xca} , {0x6c, 0xec, 0xeb, 0xab, 0x62, 0x4b},
			     {0x6c, 0xec, 0xeb, 0xaf, 0xf2, 0x74} , {0x6c, 0xec, 0xeb, 0xa5, 0x9d, 0x45},
			     {0x78, 0xa5, 0x04, 0xfd, 0xb3, 0xb7} , {0x78, 0xa5, 0x04, 0xef, 0x3c, 0xef},
			     {0x6c, 0xec, 0xeb, 0xaf, 0x37, 0xc4} , {0x6c, 0xec, 0xeb, 0xab, 0x12, 0xca},
			     {0xd0, 0x5f, 0xb8, 0xe8, 0xd8, 0xf7} , {0x6c, 0xec, 0xeb, 0xab, 0x12, 0x82},
			     {0x6c, 0xec, 0xeb, 0xad, 0xc2, 0xf5} , {0x6c, 0xec, 0xeb, 0xab, 0x0a, 0xe9},
			     {0xd0, 0x5f, 0xb8, 0xe7, 0xc0, 0x34} , {0x6c, 0xec, 0xeb, 0xab, 0x07, 0xc1},
			     {0xd0, 0x5f, 0xb8, 0xe7, 0xbc, 0x7a} , {0x6c, 0xec, 0xeb, 0xae, 0x84, 0x81},
			     {0x6c, 0xec, 0xeb, 0xab, 0x0a, 0xe6} , {0x6c, 0xec, 0xeb, 0xae, 0xf0, 0x7e}};
