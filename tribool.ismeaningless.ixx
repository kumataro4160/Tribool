export module tribool.ismeaningless;

export import tribool.tribool;

export namespace tribool
{
	constexpr bool isMeaningless(tribool x)noexcept
	{
		return x.x == tribool::meaningless_value;
	}
}