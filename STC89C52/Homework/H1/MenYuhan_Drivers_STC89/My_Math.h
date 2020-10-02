uint low_pow(uchar x, uchar y)
{
	uint result = 1;
	while (y--)
		result *= x;
	return result;
}