//#include "average_screen2.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "average_screen2.h"

using namespace std;


void example(hls::stream< ap_axis<32,2,5,6> > &A,
	     hls::stream< ap_axis<32,2,5,6> > &B)
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE mode=axis port=A
#pragma HLS INTERFACE mode=axis port=B

	static int i;
	static int num;
	static int max = 0;

	ap_axis<32,2,5,6> tmp;

    while(1)
    {
	A.read(tmp);

	num = tmp.data.to_int();
	color255[num] += 1;
	// cout << "added value: " << num << " " << color255[num] << endl;

    if(tmp.last)
    	{
        	break;
    	}

	}
	 for(i = 0; i < 256; i++) {
		 if(color255[i] > color255[max]) {
			 max = i;
		 	 }

	 	 }
	   	tmp.data = max;
	    B.write(tmp);


}
