/*
 * Copyright 2022 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
using namespace std;

void example(hls::stream<ap_axis<32,2,5,6> > &A, hls::stream<ap_axis<32,2,5,6> > &B);

int main()
{
  hls::stream<ap_axis<32,2,5,6> > A, B;
  ap_axis<32,2,5,6> tmp1, tmp2;
  int inputs[] = {0,
  		242 ,
  		245 ,
  		246 ,
  		249 ,
  		100 ,
  		100 ,
  		100 ,
  		240 ,
  		249};
  int expected[] = {1, 0, 1, 1, 1, 0, 0, 1};
  int result = 100;

 for(int j=0;j<11;j++)
{
  tmp1.data = inputs[j];
  tmp1.keep = 1;
  tmp1.strb = 1;
  tmp1.user = 1;
 if(j==10)
{
  tmp1.last = 1;

}
else
{
  tmp1.last = 0;
}
  tmp1.id = 0;
  tmp1.dest = 1;

  A.write(tmp1);

}

 example(A,B);

	  B.read(tmp2);
	  cout << tmp2.data.to_int() << endl;

	  if (tmp2.data.to_int() != result)
	  {
	    cout << "ERROR: results mismatch" << endl;
	    return 1;
	  }
	    cout << "Success: results match" << endl;

  return 0;

}
