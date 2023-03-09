#pragma once

namespace signatures {
    constexpr auto warfog_1_sig = "\x80\xb8\x00\x00\x00\x00\x00\x0f\x85\x00\x00\x00\x00\x80\xb8\x00\x00\x00\x00\x00\x0f\x85\x00\x00\x00\x00\x48\x8b\x8d";
    constexpr auto warfog_2_sig = "\x80\xbb\x00\x00\x00\x00\x00\x75\x00\x80\xbb\x00\x00\x00\x00\x00\x75\x00\x4c\x8b\xad";
    constexpr auto warfog_1_mask = "xx?????xx????xx?????xx????xxx";
    constexpr auto warfog_2_mask = "xx?????x?xx?????x?xxx";
}
