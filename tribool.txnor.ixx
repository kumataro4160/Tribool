module;

#include <cstdint>

export module tribool.txnor;

export import tribool.tribool;

export namespace tribool
{
	//xnor, xand
	constexpr tribool operator==(tribool l, tribool r)noexcept
	{
		//return tribool((l.x | r.x) & tribool::false_value & (((l.x | r.x) & tribool::true_value) << 1) | (((l.x & r.x) >> 1) | r.x & tribool::true_value) & (l.x & r.x | ((r.x & tribool::false_value) >> 1)));
		constexpr std::uint32_t magic = 0b11111111'11011000'11100100'11000000UL;
		return tribool(static_cast<tribool::tribool_t>((magic >> (((l.x << 2) | r.x) * 2)) & 0b11UL));
	}
}