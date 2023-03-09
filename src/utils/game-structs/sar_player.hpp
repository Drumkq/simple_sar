#pragma once

#include <cstdint>
#include <string>

#define DEREF(T, Ex) *(T*)(Ex)

namespace game_structs {
	enum class floor_type
	{
		grass = 0,
		default_floor = 1,
		snow = 2,
		metal = 3,
		ice = 4,
	};

	class sar_player {
	public:
		sar_player(uint64_t address) : address(address) {

		}

		bool is_valid() const {
			auto addr = address;

			for (int i = 0; i < 3; i++)
			{
				if ((void*)addr == nullptr)
				{
					return false;
				}

				addr = *(uintptr_t*)addr;
			}

			if ((void*)addr != nullptr)
			{
				return memcmp((void*)addr, "\x41\x73\x73\x65\x6D\x62\x6C\x79\x2D\x43\x53\x68\x61\x72\x70\x2E\x64\x6C\x6C\x00\x67\x65\x74\x5F\x64\x6E\x61\x00\x64\x6E", 30) == 0;
			}
			else
			{
				return false;
			}
		}

		int* get_move_state() {
			return (int*)(address + 0x310);
		}

		floor_type get_floor_type() {
			return floor_type::grass;
		}

		float get_health() {
			return *(float*)(address + 0x118);
		}

		float get_armor() {
			return *(float*)(address + 0x11C);
		}

		int get_x_position() {
			return DEREF(int, address + 0x2C4);
		}

		int get_y_position() {
			return DEREF(int, address + 0x2C8);
		}

		int get_current_slot_id() {
			return DEREF(int, address + 0x180);
		}

		__int64 get_weapon_address() {
			return DEREF(__int64, address + 0x208);
		}

	private:
		uint64_t address;
	};
}
