#include <iostream>
#include <ap_int.h>

using namespace std;

typedef ap_uint<8> 	color_array;
#define IMAGE_LENGTH 255960

void average_screen (
		color_array *result,
		volatile color_array* input_array
  );

int main()
{
	int ret;

    // Call any preliminary functions required to prepare input for the test.
    color_array input_arr[255] = {0,242,245,246,249,250,249,250,240,249,253,253,246,236,235,242,242,234,227,
    		230,
    		230,
    		222,
    		207,
    		194,
    		147,
    		164,
    		166,
    		153,
    		161,
    		181,
    		168,
    		136,
    		148,
    		153,
    		162,
    		177,
    		129,
    		175,
    		191,
    		178,
    		139,
    		148,
    		171,
    		167,
    		155,
    		170,
    		178,
    		206,
    		167,
    		133,
    		171,
    		191,
    		146,
    		60,
    		169,
    		243,
    		255,
    		254,
    		252,
    		254,
    		255,
    		253,
    		254,
    		255,
    		255,
    		255,
    		255,
    		255,
    		255,
    		253,
    		252,
    		251,
    		250,
    		254,
    		255,
    		251,
    		246,
    		243,
    		246,
    		250,
    		244,
    		233,
    		232,
    		242,
    		249,
    		245,
    		244,
    		251,
    		233,
    		248,
    		235,
    		223,
    		236,
    		234,
    		211,
    		195,
    		193,
    		197,
    		194,
    		187,
    		177,
    		149,
    		108,
    		82,
    		64,
    		61,
    		51,
    		43,
    		37,
    		29,
    		27,
    		32,
    		31,
    		37,
    		40,
    		30,
    		33,
    		40,
    		37,
    		46,
    		28,
    		32,
    		72,
    		157,
    		220,
    		231,
    		230,
    		226,
    		202,
    		203,
    		196,
    		212,
    		218,
    		207,
    		212,
    		207,
    		223,
    		232,
    		234,
    		228,
    		230,
    		240,
    		235,
    		225,
    		228,
    		237,
    		238,
    		238,
    		238,
    		255,
    		252,
    		248,
    		244,
    		235,
    		241,
    		247,
    		243,
    		244,
    		250,
    		247,
    		251,
    		195,
    		44,
    		44,
    		82,
    		64,
    		86,
    		116,
    		110,
    		121,
    		141,
    		114,
    		101,
    		99,
    		59,
    		134,
    		143,
    		147,
    		161,
    		163,
    		156,
    		166,
    		186,
    		194,
    		199,
    		197,
    		187,
    		147,
    		138,
    		82,
    		142,
    		187,
    		210,
    		207,
    		199,
    		184,
    		168,
    		156,
    		151,
    		149,
    		149,
    		152,
    		157,
    		163,
    		168,
    		169,
    		168,
    		165,
    		162,
    		143,
    		143,
    		141,
    		139,
    		136,
    		122,
    		133,
    		115,
    		129,
    		139,
    		141,
    		138,
    		130,
    		106,
    		82,
    		76,
    		78,
    		79,
    		76,
    		61,
    		29,
    		51,
    		77,
    		55,
    		37,
    		45,
    		34,
    		30,
    		25,
    		23,
    		29,
    		63,
    		63,
    		21,
    		71,
    		88,
    		56,
    		54,
    		53,
    		63,
    		73,
    		79,
    		79,
    		81,
    		81,
    		82};

    // Call the top-level function multiple times, passing input stimuli as needed.
    // for (i = 0; i < NUM_TRANS; i++)
    // {
    //     top_func(input, output);
    // }
    color_array output;
    average_screen(&output, input_arr);

    // Capture the output results of the function, write to a file

    // Compare the results of the function against expected results
    // ret = system("diff --brief  -w output.dat output.golden.dat");

    if (output != 255)
    {
        cout << "Test failed  !!!\n" << output << "\n";
        cout << output;
        ret = 1;
    }
    else
    {
    	cout << "Test success  !\n";
        ret = 0;
    }

    return ret;
}