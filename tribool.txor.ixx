module;

#include <cstdint>

export module tribool.txor;

export import tribool.tribool;

export namespace tribool
{
	//xor, xnand
	constexpr tribool operator!=(tribool l, tribool r)noexcept
	{
		constexpr std::uint32_t magic = 0b11111111'11100100'11011000'11000000UL;
		return tribool(static_cast<tribool::tribool_t>((magic >> (((l.x << 2) | r.x) * 2)) & 0b11UL));
	}
}