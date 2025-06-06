
//
// Active linker CMD configuration selected by 
// the CMD Tool global settings
//
#define CMD0
#ifdef CMD0

MEMORY
{

    RAMM0                     : origin = 0x000128, length = 0x0002D8
    RAMM1                     : origin = 0x000400, length = 0x000400
    CLATOCPURAM               : origin = 0x001480, length = 0x000080
    CPUTOCLARAM               : origin = 0x001500, length = 0x000080
    CLATODMARAM               : origin = 0x001680, length = 0x000080
    DMATOCLARAM               : origin = 0x001700, length = 0x000080
    RAMLS8_CLA                : origin = 0x004000, length = 0x002000
    RAMLS9_CLA                : origin = 0x006000, length = 0x002000
    RAMLS0                    : origin = 0x008000, length = 0x000800
    RAMLS1                    : origin = 0x008800, length = 0x000800
    RAMLS2                    : origin = 0x009000, length = 0x000800
    RAMLS3                    : origin = 0x009800, length = 0x000800
    RAMLS4                    : origin = 0x00A000, length = 0x000800
    RAMLS5                    : origin = 0x00A800, length = 0x000800
    RAMLS6                    : origin = 0x00B000, length = 0x000800
    RAMLS7                    : origin = 0x00B800, length = 0x000800
    RAMGS0                    : origin = 0x00C000, length = 0x002000
    RAMGS1                    : origin = 0x00E000, length = 0x002000
    RAMGS2                    : origin = 0x010000, length = 0x002000
    RAMGS3                    : origin = 0x012000, length = 0x002000
    RAMLS8                    : origin = 0x014000, length = 0x002000
    RAMLS9                    : origin = 0x016000, length = 0x002000
    FLASH_BANK0               : origin = 0x080000, length = 0x020000
    FLASH_BANK1               : origin = 0x0A0000, length = 0x020000
    FLASH_BANK2               : origin = 0x0C0000, length = 0x020000
    FLASH_BANK3               : origin = 0x0E0000, length = 0x020000
    FLASH_BANK4               : origin = 0x100000, length = 0x007FFF
    RESET                     : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
    //
    // C28x Sections
    //
    .reset               : >  RESET, TYPE = DSECT /* not used, */
    codestart            : >  0x080000
    .text                : >  FLASH_BANK0,
                              ALIGN(8)
    .TI.ramfunc          :    LOAD >  FLASH_BANK0,
                              RUN  >  RAMLS0,
                              TABLE(BINIT),
                              ALIGN(8)
    .binit               : >  FLASH_BANK0,
                              ALIGN(8)
    .ovly                : >  FLASH_BANK0,
                              ALIGN(8)
    .cinit               : >  FLASH_BANK0,
                              ALIGN(8)
    .stack               : >  RAMM1
    .init_array          : >  FLASH_BANK0,
                              ALIGN(8)
    .bss                 : >> RAMLS5 | RAMLS6
    .const               : >  FLASH_BANK0,
                              ALIGN(8)
    .data                : >> RAMLS5 | RAMLS6 | RAMLS7
    .switch              : >  FLASH_BANK0,
                              ALIGN(8)
    .sysmem              : >  RAMLS5

    //
    // User Sections
    //
    dclfuncs { *(dclfuncs) }       LOAD >  FLASH_BANK1,
                              RUN  >  RAMGS1,
                              TABLE(BINIT),
                              ALIGN(8)
    FPUmathTables { *(FPUmathTables) }       LOAD >  FLASH_BANK0,
                              RUN  >  RAMGS1,
                              TABLE(BINIT),
                              ALIGN(8)

}

#endif

/*
//===========================================================================
// End of file.
//===========================================================================
*/
