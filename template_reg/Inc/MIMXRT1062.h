#ifndef MIMXRT1062_H_
#define MIMXRT1062_H_

/* CCM */
#define CCM_BASE    (unsigned int)(0x400FC000)
#define CCM_CCGR1   *(unsigned int*)(CCM_BASE + 0x6C)

/* IOMUCX */
#define IOMUXC_BASE (unsigned int)(0x401F8000)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_00 *(unsigned int*)(IOMUXC_BASE + 0xBC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_00 *(unsigned int*)(IOMUXC_BASE + 0x2AC)

/* GPIO1 */
#define GPIO1_BASE  (unsigned int)(0x401B8000)
#define GPIO1_DR    *(unsigned int*)(GPIO1_BASE + 0x00)
#define GPIO1_GDIR  *(unsigned int*)(GPIO1_BASE + 0x04)

#endif /* MIMXRT1062_H_ */
