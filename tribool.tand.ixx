module;

#include <cstdint>

export module tribool.tand;

export import tribool.tribool;

export namespace tribool
{
	constexpr tribool operator&&(tribool l, tribool r)noexcept
	{
		//return tribool((l.x | r.x) & tribool::false_value | (l.x >> 1) & l.x | (r.x >> 1) & r.x | l.x & r.x & tribool::true_value);
		constexpr std::uint32_t magic = 0b11111111'11101010'11100100'11100000UL;
		return tribool(static_cast<tribool::tribool_t>((magic >> (((l.x << 2) | r.x) * 2)) & 0b11UL));
	}
}