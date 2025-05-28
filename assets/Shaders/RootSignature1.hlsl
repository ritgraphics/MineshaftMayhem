
#define RS1 "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT), " \
            "RootConstants(num32BitConstants=2, b1), " \
              "DescriptorTable(SRV(t1), visibility=SHADER_VISIBILITY_PIXEL), " \
              "CBV(b0, visibility=SHADER_VISIBILITY_VERTEX), " \
              "DescriptorTable(SRV(t0), visibility=SHADER_VISIBILITY_VERTEX), " \
              "StaticSampler(s0, " \
                             "addressU = TEXTURE_ADDRESS_WRAP, " \
                             "addressV = TEXTURE_ADDRESS_WRAP, " \
                             "addressW = TEXTURE_ADDRESS_WRAP, " \
                             "filter = FILTER_MIN_MAG_MIP_LINEAR )"