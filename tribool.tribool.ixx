export module tribool.tribool;

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
}