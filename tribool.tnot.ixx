export module tribool.tnot;

export import tribool.tribool;

export namespace tribool
{
	constexpr tribool operator!(tribool x)noexcept
	{
		return tribool(static_cast<tribool::tribool_t>(((x.x << 1) | (x.x >> 1)) & 0b11UL));
		//constexpr bitarr8_t magic = 0b11011000;
		//return tribool((magic << (x.x * 2)) & 0b11);
	}
}