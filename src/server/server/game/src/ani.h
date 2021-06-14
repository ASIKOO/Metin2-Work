/*********************************************************************
 * date        : 2007.11.16
 * file        : ani.h
 * author      : mhh
 * description : 
 */

#ifndef _ani_h_
#define _ani_h_


void ani_init();
uint32_t ani_attack_speed(LPCHARACTER ch);
void ani_print_attack_speed();
uint32_t ani_combo_speed(LPCHARACTER ch, uint8_t combo);

#endif	/* _ani_h_ */


