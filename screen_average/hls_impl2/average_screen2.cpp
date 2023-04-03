//#include "average_screen2.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "average_screen2.h"

using namespace std;


void example(hls::stream< ap_axis<32,2,5,6> > &A,
	     hls::stream< ap_axis<32,2,5,6> > &B)
{
#pragma HLS INTERFACE axis port=A
#pragma HLS INTERFACE axis port=B
#pragma HLS INTERFACE s_axilite port=return

	int i;
	int num;
	int max = 0;

	ap_axis<32,2,5,6> tmp;
    while(1)
    {
	A.read(tmp);

	Find_Color_Loop:
		for(i = 0; i < IMAGE_LENGTH; i++) {
			num = tmp.data.to_int();
			color255[num] += 1;
		}

		Find_Max_Loop:
			for(i = 0; i < 256; i++) {
				if(color255[i] > color255[max]) {
					max = i;
				}
			}

     if(tmp.last)
     {
    	 tmp.data = max;
    	 B.write(tmp);
         break;
     }
    }


}
