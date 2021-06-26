#include "MIMXRT1062.h"

int main(void)
{	
	/* Enable GPIO1 Clock */
	CCM_CCGR1 &= ~(unsigned int)(3<<26);    // bit27 = 0, bit 26 = 0
	CCM_CCGR1 |= (unsigned int)(1<<26);     // bit26 = 1
		
	/* Set GPIO_AD_B0_00 as GPIO1.0 */
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_00 = (unsigned int)0x05;
	
	/* Set pad parameters of GPIO1.0 */
	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_00 = (unsigned int)0x000B0;
    
	/* set output mode */
	GPIO1_GDIR |= (unsigned int)(1<<0);

	/* output low level */
	GPIO1_DR &= ~(unsigned int)(1<<0);
	
	while(1);
}

void SystemInit(void)
{	
}