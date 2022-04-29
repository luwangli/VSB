#include "hyperloglogplus_counting.h"
#include <iostream>
#include <stdio.h>
using namespace std;
int main(){

    int rc;
    int64_t i, esti;
    hllp_cnt_ctx_t *ctx = hllp_cnt_raw_init(NULL, 8);
    //EXPECT_NE(ctx, (hllp_cnt_ctx_t *)NULL);

    printf("HyperloglogPlus Counting:\n");
    for (i = 1; i <= 500000L; i++) {
        rc = hllp_cnt_offer(ctx, &i, sizeof(int64_t));
      //  EXPECT_GE(rc, 0);

        if (i % 50000 == 0) {
            esti = hllp_cnt_card(ctx);
        //    EXPECT_GT(esti, 0);

            printf("actual: %9lu, estimated: %9lu, error: %+7.2f%%\n",
                   (long unsigned int)i, (long unsigned int)esti, (double)(esti - i) / i * 100);
        }
    }

 }
