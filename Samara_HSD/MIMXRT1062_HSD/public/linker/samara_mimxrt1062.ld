MEMORY
{
/*
    NOTE:
    The following three memory regions share the same
    512K memory space and this allocation is decided
    by the FLEXRAM unit.
*/
    /* Instruction Tightly Coupled Memory (ITCM)*/
    ITCM  (rwx): ORIGIN = 0x00000000, LENGTH = 0x80000

    /* Data Tightly Coupled Memory (DTCM)       */
    DTCM  (rwx): ORIGIN = 0x20000000, LENGTH = 0x80000

    /* On Chip RAM 1 (OCRAM2)                   */
    OCRAM (rwx): ORIGIN = 0x20280000, LENGTH = 0x80000
/*
    NOTE:
    End of shared memory
*/

    /* On Chip RAM 2 (OCRAM2)                   */
    OCRAM2(rwx): ORIGIN = 0x20200000, LENGTH = 0x80000

    /* Instruction Tightly Coupled Memory*/
    FLASH (rwx): ORIGIN = 0x00000000, LENGTH = 0x7c0000
}

ENTRY(ResetISR)

SECTIONS
{

    .boot : ALIGN(4)
    {
        FILL(0x00)
        (*.boot.conf)
        . = 0x1000
        (*.boot.ivt)
        (*.boot.data)
    }
}