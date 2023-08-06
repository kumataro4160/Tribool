export module tribool.isindetermine;

export import tribool.tribool;

export namespace tribool
{
	constexpr bool isIndetermine(tribool x)noexcept
	{
		return x.x == tribool::indetermine_value;
	}
}