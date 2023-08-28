//
// Created by rozhin on 21.08.2023.
// Copyright (c) 2021-2023 xsdnn. All rights reserved.
//

#include "xsdnn.h"
#include <gtest/gtest.h>
#include <sys/mman.h>
#include "test_utils.h"
using namespace xsdnn;

TEST(conv, _2D_params_check_1) {
    shape3d in(12, 255, 255);
    conv c(in, /*out_channel=*/ 6, /*kernel_shape=*/ {3, 3},
           /*group_count=*/ 3, /*has_bias=*/ true,
           /*stride_shape=*/ {1, 1}, /*dilation_shape=*/ {1, 1},
           /*pad_type=*/padding_mode::notset, /*pads=*/ {1, 1, 1, 1});

    params::conv P = c.get_params();

    ASSERT_EQ(P._.Dimensions, 2);
    ASSERT_EQ(P._.GroupCount, 3);
    ASSERT_EQ(P._.InChannel, 4);
    ASSERT_EQ(P._.InShape[0], 255);
    ASSERT_EQ(P._.InShape[1], 255);
    ASSERT_EQ(P._.InSize, 255 * 255);
    ASSERT_EQ(P._.OutShape[0], 255);
    ASSERT_EQ(P._.OutShape[1], 255);
    ASSERT_EQ(P._.OutSize, 255 * 255);
    ASSERT_EQ(P._.K, 4 * 3 * 3);
    ASSERT_EQ(P._.Padding[0], 1);
    ASSERT_EQ(P._.Padding[1], 1);
    ASSERT_EQ(P._.Padding[2], 1);
    ASSERT_EQ(P._.Padding[3], 1);
    ASSERT_EQ(P._.KernelShape[0], 3);
    ASSERT_EQ(P._.KernelShape[1], 3);
    ASSERT_EQ(P._.DilationShape[0], 1);
    ASSERT_EQ(P._.DilationShape[1], 1);
    ASSERT_EQ(P._.StrideShape[0], 1);
    ASSERT_EQ(P._.StrideShape[1], 1);
    ASSERT_EQ(P._.FilterCount, 2);
    ASSERT_EQ(P._.Algorithm, P._.Im2ColThenGemm);
    ASSERT_EQ(P._.Bias, true);
    ASSERT_EQ(P._.TemproraryBufferSize, 16384);
}

TEST(conv, simple_forward_without_bias) {
    const mat_t Input = {
            -0.8597232699394226,
            -0.016536127775907516,
            -1.067084789276123,
            -1.2771207094192505,
            0.5289744138717651,
            0.4591456353664398,
            -0.6136614680290222,
            -0.3110077679157257,
            -1.003212809562683,
            -0.25640687346458435,
            -0.34296318888664246,
            0.3661316931247711,
            1.96624755859375,
            0.12085486948490143,
            0.28439822793006897,
            -0.9817278385162354,
            1.723364233970642,
            1.11757230758667,
            -0.8552507758140564,
            -0.3802138864994049,
            0.791811466217041,
            0.450124055147171,
            0.1003960445523262,
            -0.6282744407653809,
            -0.10524702817201614,
            0.5840324759483337,
            -0.05916932225227356,
            1.0429607629776,
            -0.4981708824634552,
            1.1234641075134277,
            -0.5341346263885498,
            0.13873034715652466,
            -0.11888983845710754,
            -1.597569465637207,
            -1.7347184419631958,
            0.6859488487243652,
            0.27496105432510376,
            1.2040894031524658,
            0.4182891249656677,
            -0.04522772505879402,
            0.8157641887664795,
            -0.9951342940330505,
            -0.8859978914260864,
            0.6702648401260376,
            -0.1707228422164917,
            -1.0781022310256958,
            0.36826708912849426,
            -0.6138019561767578,
    };

    std::vector<float> Output = {
            -0.4404990077018738,
            0.12277835607528687,
            -0.21373416483402252,
            0.3472598195075989,
            0.21447788178920746,
            -0.31341293454170227,
            -0.44802138209342957,
            -0.22438563406467438,
            0.349630743265152,
            0.9372735619544983,
            0.01971816085278988,
            -0.26863399147987366,
            0.27968576550483704,
            0.28655096888542175,
            -0.17447705566883087,
            0.08845566213130951,
            0.39708858728408813,
            0.19920746982097626,
            0.044415123760700226,
            -0.07635539025068283,
            -0.6138955354690552,
            -0.44105473160743713,
            0.7539032697677612,
            0.1517699509859085,
            1.07393217086792,
            0.6412769556045532,
            -0.2617749273777008,
    };

    shape3d in(3, 4, 4);

    conv c(in, 3, {2, 2}, 3, false);

    c.set_parallelize(false);
    c.setup(false);

    c.prev()[1]->get_data()->at(0) = {
            0.2444877028465271,
            0.09724676609039307,
            -0.0643761157989502,
            -0.42393046617507935,
            0.15800708532333374,
            0.3538004755973816,
            0.3129462003707886,
            0.0483817458152771,
            0.07881486415863037,
            -0.4501446485519409,
            -0.4511941075325012,
            -0.44954395294189453
    };

    c.set_in_data({{ Input }});
    c.forward();

    mat_t out = c.output()[0][0];

    ASSERT_EQ(out.size(), Output.size());
    for (size_t i = 0; i < out.size(); ++i) {
        EXPECT_NEAR(out[i], Output[i], 1e-5);
    }
}