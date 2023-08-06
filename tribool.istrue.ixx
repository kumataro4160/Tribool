export module tribool.istrue;

export import tribool.tribool;

export namespace tribool
{
	constexpr bool isTrue(tribool x)noexcept
	{
		return x.x == tribool::true_value;
	}
}