module;

#include <cstdint>

export module tribool;

export namespace tribool
{
	class tribool
	{
	public:
		enum tribool_t
		{
			indetermine_value,
			true_value,
			false_value,
			meaningless_value
		};

	private:
		tribool_t x;

	public:
		constexpr tribool()noexcept :
			x(indetermine_value)
		{

		}
		constexpr tribool(tribool_t x)noexcept :
			x(x)
		{

		}
		constexpr explicit tribool(bool boolean)noexcept :
			x(boolean ? true_value : false_value)
		{

		}

	private:
		friend constexpr tribool operator!(tribool x)noexcept;
		friend constexpr tribool operator&&(tribool l, tribool r)noexcept;
		friend constexpr tribool operator||(tribool l, tribool r)noexcept;
		friend constexpr tribool operator==(tribool l, tribool r)noexcept;
		friend constexpr tribool operator!=(tribool l, tribool r)noexcept;
		friend constexpr bool isIndetermine(tribool x)noexcept;
		friend constexpr bool isTrue(tribool x)noexcept;
		friend constexpr bool isFalse(tribool x)noexcept;
		friend constexpr bool isMeaningless(tribool x)noexcept;
	};

	//not
	constexpr tribool operator!(tribool x)noexcept
	{
		return tribool(static_cast<tribool::tribool_t>(((x.x << 1) | (x.x >> 1)) & 0b11));
		//constexpr bitarr8_t magic = 0b11011000;
		//return tribool((magic << (x.x * 2)) & 0b11);
	}

	//and
	constexpr tribool operator&&(tribool l, tribool r)noexcept
	{
		//return tribool((l.x | r.x) & tribool::false_value | (l.x >> 1) & l.x | (r.x >> 1) & r.x | l.x & r.x & tribool::true_value);
		constexpr std::uint32_t magic = 0b11111111'11101010'11100100'11100000UL;
		return tribool(static_cast<tribool::tribool_t>((magic >> (((l.x << 2) | r.x) * 2)) & 0b11UL));
	}

	//or
	constexpr tribool operator||(tribool l, tribool r)noexcept
	{
		//return tribool(l.x & (l.x << 1) | r.x & (r.x << 1) | l.x & r.x & tribool::false_value | (l.x | r.x) & tribool::true_value);
		constexpr std::uint32_t magic = 0b11111111'11100100'11010101'11000100UL;
		return tribool(static_cast<tribool::tribool_t>((magic >> (((l.x << 2) | r.x) * 2)) & 0b11UL));
	}

	//xor, xnand
	constexpr tribool operator!=(tribool l, tribool r)noexcept
	{
		constexpr std::uint32_t magic = 0b11111111'11100100'11011000'11000000UL;
		return tribool(static_cast<tribool::tribool_t>((magic >> (((l.x << 2) | r.x) * 2)) & 0b11UL));
	}

	//xand, xnor
	constexpr tribool operator==(tribool l, tribool r)noexcept
	{
		//return tribool((l.x | r.x) & tribool::false_value & (((l.x | r.x) & tribool::true_value) << 1) | (((l.x & r.x) >> 1) | r.x & tribool::true_value) & (l.x & r.x | ((r.x & tribool::false_value) >> 1)));
		constexpr std::uint32_t magic = 0b11111111'11011000'11100100'11000000UL;
		return tribool(static_cast<tribool::tribool_t>((magic >> (((l.x << 2) | r.x) * 2)) & 0b11UL));
	}

	constexpr bool isIndetermine(tribool x)noexcept
	{
		return x.x == tribool::indetermine_value;
	}

	constexpr bool isTrue(tribool x)noexcept
	{
		return x.x == tribool::true_value;
	}

	constexpr bool isFalse(tribool x)noexcept
	{
		return x.x == tribool::false_value;
	}

	constexpr bool isMeaningless(tribool x)noexcept
	{
		return x.x == tribool::meaningless_value;
	}
}