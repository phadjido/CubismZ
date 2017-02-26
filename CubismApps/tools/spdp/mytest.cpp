#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#include "myspdp.h"

#ifndef dtype
#define dtype double
#endif

#ifndef SZ
#define SZ1	19
#define SZ	(SZ1*SZ1*SZ1)
#endif

static dtype indat[SZ];
static dtype indat_copy[SZ];
static dtype outdat[SZ+1024];
static dtype outdat2[SZ];

char buf[186]=
{
0,
1,
0,
0,
0,
0,
0,
0,
186,
0,
0,
0,
0,
0,
0,
0,
224,
110,
199,
137,
87,
145,
209,
248,
58,
208,
19,
16,
246,
164,
232,
48,
168,
198,
210,
26,
86,
209,
188,
230,
40,
63,
200,
102,
38,
179,
110,
183,
171,
93,
142,
123,
145,
119,
140,
130,
238,
254,
126,
158,
101,
171,
78,
189,
161,
36,
146,
135,
114,
175,
57,
223,
110,
63,
152,
132,
107,
193,
32,
0,
59,
105,
2,
254,
2,
254,
2,
255,
2,
253,
2,
255,
1,
255,
1,
255,
2,
253,
2,
255,
1,
255,
10,
67,
189,
1,
255,
1,
255,
1,
255,
1,
255,
1,
21,
145,
154,
156,
96,
118,
199,
216,
177,
41,
16,
73,
88,
50,
188,
78,
32,
170,
84,
132,
186,
132,
201,
109,
60,
250,
84,
127,
207,
189,
197,
126,
250,
14,
22,
74,
192,
89,
160,
114,
142,
204,
50,
98,
163,
116,
144,
108,
161,
141,
80,
129,
156,
91,
196,
35,
237,
53,
138,
104,
202,
28,
2,
241,
11,
59,
107,
1,
255,
1,
255,
1,
};
int main(int argc, char *argv[])
{
        size_t outs;
        size_t outs2;

        int i;
	//for (i = 0; i < SZ; i++) indat[i] = exp(-i);
	srand48(1);
	for (i = 0; i < SZ; i++) indat[i] = -1+2*drand48();
	for (i = 0; i < SZ; i++) indat_copy[i] = indat[i];

	double t0 = omp_get_wtime();
	outs = spdp_compress_data( (const char*)indat, SZ*sizeof(dtype), (char *) outdat, SZ*sizeof(dtype)+1024);
	double t1 = omp_get_wtime();
	
        printf("outs = %ld\n", outs);
        printf("rate = %.2lf\n", (1.0*SZ*sizeof(dtype))/outs);
        printf("time = %.2lf s\n", t1-t0);

	outs2 = spdp_uncompress_data((const char*)outdat, outs, (char *) outdat2, SZ*sizeof(dtype));
        printf("outs2 = %ld\n", outs2);

//        for (i = 0; i < SZ; i+=(SZ/4)) printf("%d : %lf vs %lf\n", i, indat_copy[i], outdat2[i]);
//        for (i = SZ-3; i < SZ; i+=1) printf("%d : %lf vs %lf\n", i, indat_copy[i], outdat2[i]);


	for (i = 0; i < SZ; i++)
		if (outdat2[i] != indat_copy[i])
			printf("%d : %lf vs %lf\n", i, indat_copy[i], outdat2[i]);
		

	float fff[4096];
	int outs3 = spdp_uncompress_data((const char*)buf, 186, (char *) fff, 4096);

	printf("outs3 = %d\n", outs3);

	for (i = 0 ; i < outs3/4; i++)
		printf("f[%d] = %f\n", i, fff[i]);

	return 0;
}
