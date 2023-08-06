export module tribool.isfalse;

export import tribool.tribool;

export namespace tribool
{
	constexpr bool isFalse(tribool x)noexcept
	{
		return x.x == tribool::false_value;
	}
}