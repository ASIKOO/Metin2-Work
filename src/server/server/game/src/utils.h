
#ifndef __INC_METIN_II_UTILS_H__
#define __INC_METIN_II_UTILS_H__

#include <math.h>

#define IS_SET(flag, bit)		((flag) & (bit))
#define SET_BIT(var, bit)		((var) |= (bit))
#define REMOVE_BIT(var, bit)	((var) &= ~(bit))
#define TOGGLE_BIT(var, bit)	((var) = (var) ^ (bit))

inline float DISTANCE_SQRT(int32_t dx, int32_t dy)
{
    return ::sqrt((float)dx * dx + (float)dy * dy);
}

inline int32_t DISTANCE_APPROX(int32_t dx, int32_t dy)
{
	int32_t min, max;

	if (dx < 0)
		dx = -dx;

	if (dy < 0)
		dy = -dy;

	if (dx < dy)
	{
		min = dx;
		max = dy;
	}
	else
	{
		min = dy;
		max = dx;
	}

    // coefficients equivalent to ( 123/128 * max ) and ( 51/128 * min )
    return ((( max << 8 ) + ( max << 3 ) - ( max << 4 ) - ( max << 1 ) +
		( min << 7 ) - ( min << 5 ) + ( min << 3 ) - ( min << 1 )) >> 8 );
}

#ifndef __WIN32__
inline uint16_t MAKEWORD(uint8_t a, uint8_t b)
{
	return static_cast<uint16_t>(a) | (static_cast<uint16_t>(b) << 8);
}
#endif

extern void set_global_time(int32_t t);
extern int32_t get_global_time();

extern int32_t	dice(int32_t number, int32_t size);
extern uint32_t str_lower(const char * src, char * dest, uint32_t dest_size);

extern void	skip_spaces(char **string);

extern const char *	one_argument(const char *argument, char *first_arg, uint32_t first_size);
extern const char *	two_arguments(const char *argument, char *first_arg, uint32_t first_size, char *second_arg, uint32_t second_size);
extern const char *	first_cmd(const char *argument, char *first_arg, uint32_t first_arg_size, uint32_t *first_arg_len_result);

extern int32_t CalculateDuration(int32_t iSpd, int32_t iDur);

extern float gauss_random(float avg = 0, float sigma = 1);

extern int32_t parse_time_str(const char* str);

extern bool WildCaseCmp(const char *w, const char *s);

#endif /* __INC_METIN_II_UTILS_H__ */

