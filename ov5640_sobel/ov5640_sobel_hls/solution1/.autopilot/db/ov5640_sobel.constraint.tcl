set clock_constraint { \
    name clk \
    module ov5640_sobel \
    port ap_clk \
    period 20 \
    uncertainty 2.5 \
}

set all_path {}

set false_path {}
