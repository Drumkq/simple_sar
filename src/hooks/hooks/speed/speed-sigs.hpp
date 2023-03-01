#pragma once

namespace signatures {
    constexpr auto speed_1_sig = "\xc6\x80\x00\x00\x00\x00\x00\xe9\x00\x00\x00\x00\x48\x8b\x0d";
    constexpr auto speed_1_mask = "xx?????x????xxx";

    constexpr auto speed_2_sig = "\xc6\x87\x00\x00\x00\x00\x00\x0f\xb6\x87\x00\x00\x00\x00\x2c";
    constexpr auto speed_2_mask = "xx?????xxx????x";
}
