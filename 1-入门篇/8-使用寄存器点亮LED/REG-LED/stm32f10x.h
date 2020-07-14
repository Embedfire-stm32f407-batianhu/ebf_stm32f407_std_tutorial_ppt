/* 用于存放寄存器映射的代码，相当于51单片机中的 reg52.h */

// peripheral   外设

/* 所有的外设的基地址 */
#define PERIPH_BASE    ((unsigned int)0X40000000)

/* 总线基地址 */
#define APB1PERIPH_BASE    PERIPH_BASE
#define APB2PERIPH_BASE    (PERIPH_BASE+0X00010000)
#define AHBPERIPH_BASE     (PERIPH_BASE+0X00018000)


#define GPIOA_BASE         (APB2PERIPH_BASE+0X0800)
#define GPIOB_BASE         (APB2PERIPH_BASE+0X0C00)
#define GPIOC_BASE         (APB2PERIPH_BASE+0X1000)
#define GPIOD_BASE         (APB2PERIPH_BASE+0X1400)

#define GPIOB_CRL          *(unsigned int *)(GPIOB_BASE+0X00)
#define GPIOB_CRH          *(unsigned int *)(GPIOB_BASE+0X04)
#define GPIOB_IDR          *(unsigned int *)(GPIOB_BASE+0X08)
#define GPIOB_ODR          *(unsigned int *)(GPIOB_BASE+0X0C)
#define GPIOB_BSRR         *(unsigned int *)(GPIOB_BASE+0X10)
#define GPIOB_BRR          *(unsigned int *)(GPIOB_BASE+0X14)
#define GPIOB_LCKR         *(unsigned int *)(GPIOB_BASE+0X18)

#define GPIOC_CRL          *(unsigned int *)(GPIOC_BASE+0X00)
#define GPIOC_CRH          *(unsigned int *)(GPIOC_BASE+0X04)
#define GPIOC_IDR          *(unsigned int *)(GPIOC_BASE+0X08)
#define GPIOC_ODR          *(unsigned int *)(GPIOC_BASE+0X0C)
#define GPIOC_BSRR         *(unsigned int *)(GPIOC_BASE+0X10)
#define GPIOC_BRR          *(unsigned int *)(GPIOC_BASE+0X14)
#define GPIOC_LCKR         *(unsigned int *)(GPIOC_BASE+0X18)




























