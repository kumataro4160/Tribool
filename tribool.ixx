module;

#include <cstdint>

export module tribool;

export namespace kuma
{
	//U = Unknown
	//T = True
	//F = False
	//M = Meaningless
	class tribool
	{
	public:
		enum class value_t : std::uint8_t
		{
			Unknown = 0b00,
			True = 0b01,
			False = 0b10,
			Meaningless = 0b11
		};

	private:
		value_t value;

	public:
		constexpr tribool()noexcept :
			value(value_t::Unknown)
		{}
		constexpr tribool(value_t x)noexcept
		{
			switch(x)
			{
			case value_t::Unknown:
			case value_t::True:
			case value_t::False:
			case value_t::Meaningless:
				this->value = x;
				return;

			default:
				this->value = value_t::Meaningless;
				return;
			}
		}
		constexpr explicit tribool(bool boolean)noexcept :
			value(boolean ? value_t::True : value_t::False)
		{}

	private:
		friend constexpr tribool operator!(tribool t)noexcept;
		friend constexpr tribool operator&&(tribool tl, tribool tr)noexcept;
		friend constexpr tribool operator||(tribool tl, tribool tr)noexcept;
		friend constexpr tribool operator==(tribool tl, tribool tr)noexcept;
		friend constexpr tribool operator!=(tribool tl, tribool tr)noexcept;
		friend constexpr bool isUnknown(tribool t)noexcept;
		friend constexpr bool isTrue(tribool t)noexcept;
		friend constexpr bool isFalse(tribool t)noexcept;
		friend constexpr bool isMeaningless(tribool t)noexcept;
	};

	//not
	//!U == U
	//!M == M
	constexpr tribool operator!(tribool t)noexcept
	{
		const std::uint8_t b = static_cast<std::uint8_t>(t.value);
		const std::uint8_t result = ((b << 1) | (b >> 1)) & 0b11;
		return tribool(static_cast<tribool::value_t>(result));
	}

	//and
	//U && U == U
	//U && T == U
	//U && F == F
	//U && M == M
	//M && T == M
	//M && F == M
	//M && M == M
	constexpr tribool operator&&(tribool tl, tribool tr)noexcept
	{
		constexpr std::uint32_t magic = 0b11111111'11101010'11100100'11100000UL;
		const std::uint8_t bl = static_cast<std::uint8_t>(tl.value);
		const std::uint8_t br = static_cast<std::uint8_t>(tr.value);
		const std::uint8_t result = (magic >> (((bl << 2) | br) * 2)) & 0b11;
		return tribool(static_cast<tribool::value_t>(result));
	}

	//or
	//U || U == U
	//U || T == T
	//U || F == U
	//U || M == M
	//M || T == M
	//M || F == M
	//M || M == M
	constexpr tribool operator||(tribool tl, tribool tr)noexcept
	{
		constexpr std::uint32_t magic = 0b11111111'11100100'11010101'11000100UL;
		const std::uint8_t bl = static_cast<std::uint8_t>(tl.value);
		const std::uint8_t br = static_cast<std::uint8_t>(tr.value);
		const std::uint8_t result = (magic >> (((bl << 2) | br) * 2)) & 0b11;
		return tribool(static_cast<tribool::value_t>(result));
	}

	//xor, xnand
	//U != U == U
	//U != T == U
	//U != F == U
	//U != M == M
	//M != T == M
	//M != F == M
	//M != M == M
	constexpr tribool operator!=(tribool tl, tribool tr)noexcept
	{
		constexpr std::uint32_t magic = 0b11111111'11100100'11011000'11000000UL;
		const std::uint8_t bl = static_cast<std::uint8_t>(tl.value);
		const std::uint8_t br = static_cast<std::uint8_t>(tr.value);
		const std::uint8_t result = (magic >> (((bl << 2) | br) * 2)) & 0b11;
		return tribool(static_cast<tribool::value_t>(result));
	}

	//xand, xnor
	//U == U == U
	//U == T == U
	//U == F == U
	//U == M == M
	//M == T == M
	//M == F == M
	//M == M == M
	constexpr tribool operator==(tribool tl, tribool tr)noexcept
	{
		constexpr std::uint32_t magic = 0b11111111'11011000'11100100'11000000UL;
		const std::uint8_t bl = static_cast<std::uint8_t>(tl.value);
		const std::uint8_t br = static_cast<std::uint8_t>(tr.value);
		const std::uint8_t result = (magic >> (((bl << 2) | br) * 2)) & 0b11;
		return tribool(static_cast<tribool::value_t>(result));
	}

	constexpr bool isUnknown(tribool t)noexcept
	{
		return t.value == tribool::value_t::Unknown;
	}

	constexpr bool isTrue(tribool t)noexcept
	{
		return t.value == tribool::value_t::True;
	}

	constexpr bool isFalse(tribool t)noexcept
	{
		return t.value == tribool::value_t::False;
	}

	constexpr bool isMeaningless(tribool t)noexcept
	{
		return t.value == tribool::value_t::Meaningless;
	}
}